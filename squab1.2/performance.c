#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include "tiling.h"
#include "arrays.h"
#include "dual.h"
#include "save.h"
#include "rgens.h"
#include "simulation.h"
#include "mcresult.h"
#include "noise.h"
#include "correlations.h"
#include "homological.h"
#include "noise.h"
#include "performance.h"

void FormDualErasure(struct tiling **pGs, struct simulation* pSim){
	// Compute the subgraph induced by the erasure pattern on the dual graph.
	FillIntArrayWithConstants((pSim->erasure)[2], pGs[1]->e, 0);
	int ei;
	for(ei = 0; ei < (pGs[0]->e); ei ++)
		if((pSim->erasure)[1][ei] == 1)
			if((pSim->edgeOrderings)[0][ei] != -1)
				(pSim->erasure)[2][(pSim->edgeOrderings)[0][ei]] = 1;
}


void GenerateErasure(struct tiling **pGs, struct simulation *pSim, struct noise *pn){
	/*
		Generate an erasure pattern by following a particular error model.
		Types of erasures:
			1. Uncorrelated (independent) (model = 1)
			2. Correlated:
				a). Ball -- Erase a ball around a randomly picked edge (model = 2)
				b). Walk -- Erase a subgraph of a fixed length produced from a Random walk starting from an edge (model = 3)
	*/
	FillIntArrayWithConstants((pSim->erasure)[1], pGs[0]->e, 0);
	if(pn->model == 1)
		BinomialBitString((pSim->erasure)[1], pGs[0]->e, pGs[0]->doE, (pn->params)[pn->current][0]);
	else if(pn->model == 2)
		BallErasure(pSim, pGs[0], (pn->params)[pn->current]);
	else if(pn->model == 3)
		WalkErasure(pSim, pGs[0], (pn->params)[pn->current]);
	else
		fprintf(stderr, "\033[91mUnable to comprehend the noise model (of type '%d'). No qubits will be erased.\033[0m\n", pn->model);
	// Compute the weight of the erasure and the induced erasure pattern on the dual graph.
	(pSim->erasure)[0][0] = Sum((pSim->erasure)[1], pGs[0]->e);
	(pSim->erasure)[0][1] = (pSim->erasure)[0][0];
	FormDualErasure(pGs, pSim);
}


void DecodingTest(struct tiling **pGs, struct simulation* pSim, struct mcresult *pmcr){
	/*
		Determine the type of logical error covered by the erasure pattern.
		Output: 0 <=> no (non-trivial) logical error is covered,
				1 <=> Y
				2 <=> X
				3 <=> Z.
		Note: the return value is not required in general. It is only for a debugging purpose.
	*/
	int ct, logType;
	// Increment the number of trials, only for the type of errors for which the numerics are performed
	for(ct = 0; ct < 3; ct ++)
		if((pSim->type == 0) || (pSim->type == ct))
			(pmcr->trials)[ct] ++;
	// Determine the type of logical operator supported by the erasure pattern
	logType = LogicalType(pGs, pSim);
	if(logType > 0){
		if(pSim->type == 0)
			(pmcr->fails)[0] ++;
		if(logType == 1){
			(pmcr->fails)[1] ++;
			(pmcr->fails)[2] ++;
		}
		else if(logType == 2)
			(pmcr->fails)[1] ++;
		else if(logType == 3)
			(pmcr->fails)[2] ++;
		else;
	}
	for(ct = 0; ct < 3; ct ++)
		if((pSim->type) == 0 || (pSim->type) == ct)
			(pmcr->rates)[ct] = (pmcr->fails)[ct]/(double)((pmcr->trials)[ct]);
}


int IsBreakPoint(struct simulation *pSim, struct mcresult *pmcr){
	/*
	Decide if the Monte carlo rounds sampling over the erasures must be continued, based on the error bars on the current failure rate estimates.
	Stopping rules
		1. If the error bars (for X, Z failures) are below the maximum allowed size, stop numerics.
		2. Or else
			A. If both Z as well as X error bars are larger than the maximum, continue testing for both
			B. If the error bar corresponding to the estimation of the failure rates for Z-types errors is above the tolerated error, while those corresponding to X-type errors are within the tolerance, then continue sampling only Z-type errors.
			C. If the case is the opposite of the one described above, i.e, X-error bars are within tolerance while Z-error bars aren't, then sample only X-type errors.
	*/
	int ct, stop;
	for(ct = 0; ct < 3; ct ++){	
		if((pSim->type == 0) || (pSim->type == ct))
			(pmcr->bars)[pSim->type] = ErrorBar((pmcr->rates)[pSim->type], (pmcr->trials)[pSim->type]);
		if ((pmcr->bars)[ct] <= (pSim->accuracy) * (pmcr->rates)[ct])
			(pmcr->pass)[ct] = 1;
	}
	stop = 0;
	if(((pmcr->bars)[1] > (pSim->accuracy * (pmcr->rates)[1])) && ((pmcr->bars)[2] > (pSim->accuracy * (pmcr->rates)[2])))
		// Case 2A
		pSim->type = 0;
	else if((pmcr->bars)[1] > (pSim->accuracy * (pmcr->rates)[1]))
		// Case 2B
		pSim->type = 1;
	else if((pmcr->bars)[2] > (pSim->accuracy * (pmcr->rates)[2]))
		// Case 2C
		pSim->type = 2;
	else
		// Case 1
		stop = 1;

	// fprintf(stderr, "Currently checking for errors of type %d\n", pSim->type);
	// PrintResult(pmcr);
	return stop;
}


int MCStop(struct simulation* pSim, struct mcresult *pmcr, long running){
	/*
		Determine if the estimates are good enough to test if any of the Montecarlo stopping rules in IsBreakPoint(...) apply.
			1. If the number of failures encountered in X and Z are less than the minimum, continue numerics.
			2. If after 25% of the total trials, there is not a single failure, pause numerics, test for stopping conditions. This is because even if there was a failure later on, the error bars would be too big.
			3. Otherwise, continue numerics for type of error whose failures have not yet met the minimum number of failures.
			4. Once both X as well as Z failures are more than the minimum number of failures, test for stopping conditions, once every 10% of the trials.
			5. Finally, stop numerics if the conditions are suitable. Or else continue numerics for the type of errors whose error bars are not up to the mark.
	*/
	int isCheckPoint = 0;
	// Part 1.
	if(((pmcr->fails)[0] < pSim->minfails) || (((pmcr->fails)[1] < (pSim->minfails)) && ((pmcr->fails)[2] < (pSim->minfails)))){
		pSim->type = 0;
		isCheckPoint = 0;
	}
	else{
		// Part 2.
		if(((pmcr->trials)[pSim->type] > (int)((pSim->stats)/4)) && ((pmcr->fails)[pSim->type] == 0))
			isCheckPoint = 1;
		// Part 3
		else if((pmcr->fails)[1] < pSim->minfails){
			pSim->type = 1;
			isCheckPoint = 0;
		}
		else if((pmcr->fails)[2] < pSim->minfails){
			pSim->type = 2;
			isCheckPoint = 0;
		}
		else
			// Part 4.
			if(((pmcr->trials)[pSim->type] % ((long)((pSim->stats)/10))) == 0)
				isCheckPoint = 1;
	}
	if(running == (pSim->stats))
		isCheckPoint = 1;
	if (isCheckPoint == 1)
		return IsBreakPoint(pSim, pmcr);
	return 0;
}


void MCEstimate(struct tiling **pGs, struct simulation *pSim, struct noise *pn, struct mcresult *pmcr){
	// Run decoding trials to estimate the decoding failure probability
	long si;
	pSim->type = 0;
	for(si = 0; si < pSim->stats; si ++){
		GenerateErasure(pGs, pSim, pn);
		DecodingTest(pGs, pSim, pmcr);
		if(MCStop(pSim, pmcr, (si + 1)) == 1)
			break;
	}
	pSim->totaltrials = si;
}


void WriteResult(struct simulation *pSim, struct noise *pn, struct mcresult *pmcr, int nqubits){
	// Write results of simulation with a noise rate into a file
	int pi, ct;
	char *datafile, *selectedDataFile;
	datafile = malloc(sizeof(char) * 100);
	sprintf(datafile, "results/perf_%s.txt", pSim->timestamp);
	selectedDataFile = malloc(sizeof(char) * 100);
	sprintf(selectedDataFile, "results/selected_perf_%s.txt", pSim->timestamp);
	if (pn->current == 1){
		DeleteFile(datafile);
		DeleteFile(selectedDataFile);
	}
	FILE *res = fopen(datafile, "a");
	FILE *selectRes = fopen(selectedDataFile, "a");
	fprintf(res, "%lf", (pn->params)[pn->current][0]);
	fprintf(selectRes, "%lf", (pn->params)[pn->current][0]);
	for (pi = 1; pi < (pn->params)[0][1]; pi ++){
		fprintf(res, " %lf", (pn->params)[pn->current][pi]);
		fprintf(selectRes, " %lf", (pn->params)[pn->current][pi]);
	}
	for(ct = 0; ct < 3; ct ++){
		fprintf(res, " %.4e %ld %ld %.4e", (pmcr->rates)[ct], (pmcr->fails)[ct], (pmcr->trials)[ct], (pmcr->bars)[ct]);
		if ((pmcr->pass)[ct])
			fprintf(selectRes, " %.4e %ld %ld %.4e", (pmcr->rates)[ct], (pmcr->fails)[ct], (pmcr->trials)[ct], (pmcr->bars)[ct]);
		else
			fprintf(selectRes, " 0 0 0 0 0");
	}
	fprintf(res, " %d %lf\n", nqubits, pmcr->runtime);
	fprintf(selectRes, " %d %lf\n", nqubits, pmcr->runtime);
	fclose(res);
	fclose(selectRes);
	free(datafile);
	free(selectedDataFile);

	pSim->runtime += pmcr->runtime;
	if (pn->current == (pn->params)[0][0]){
		char *runfile = malloc(sizeof(char) * 100);
		sprintf(runfile, "results/runtimes_%s.txt", pSim->timestamp);
		FILE *run = fopen(runfile, "w");
		fprintf(run, "%d %ld %g\n", nqubits, pSim->totaltrials, pSim->runtime);
		fclose(run);
		free(runfile);
	}	
}


void DecodingFailureRates(struct tiling **pGs, struct simulation *pSim, struct noise *pn, struct mcresult *pmcr){
	/*
		Run montecarlo simulations to estimate the failure probabilty of the decoder for a specific noise range
		Notes:
			If there is only one noise parameter and there are zero failures corresponding to that, then the number of failures cannot increase for subsequently smaller noise rates.
			So, it would be worth stopping the simulations and skipping over the others.
	*/
	int pi, skip = 0;
	clock_t startTime, endTime;
	for (pi = 1; pi <= (pn->params)[0][0]; pi ++){
		pn->current ++;
		ResetResults(pmcr);
		startTime = clock();
		if (skip == 0)
			MCEstimate(pGs, pSim, pn, pmcr);
		endTime = clock();
		pmcr->runtime = (double)(endTime - startTime)/CLOCKS_PER_SEC;
		WriteResult(pSim, pn, pmcr, pGs[0]->e);
		// See "Notes".
		if (pn->model == 1)
			if ((Sum((int *)(pmcr->fails), 3) == 0) && (skip == 0))
				skip = 1;
	}
}


char* Performance(struct tiling G, int model, double **noiseParams, long stats){
	// Analyze the performance of a code (defined with a tiling) with montecarlo simulation of specific number of decoding trails
	int ti, nrates;
	struct tiling **pGs = malloc(sizeof(struct tiling*) * 3);
	for (ti = 0; ti < 3; ti ++)
		pGs[ti] = malloc(sizeof(struct tiling));
	pGs[0][0] = G;
	pGs[1][0] = DualTiling(pGs[0][0]);
	pGs[2][0] = DualTiling(pGs[1][0]);
	struct mcresult *pmcr = malloc(sizeof(struct mcresult));
	InitializeResult(pmcr);
	struct noise *pn = malloc(sizeof(struct noise));
	InitializeNoise(pn, pGs[0], model, noiseParams);
	nrates = (int) ceil((pn->params)[0][0]);
	struct simulation *pSim = malloc(sizeof(struct simulation));
	InitializeSimulation(pSim, pGs, nrates, stats);
	
	DecodingFailureRates(pGs, pSim, pn, pmcr);
	char *summary = malloc(sizeof(char) * 100);
	sprintf(summary, "%s", pSim->timestamp);
	
	// Free memory
	for (ti = 1; ti < 3; ti ++)
		FreeTiling(pGs[ti]);
	free(pGs);
	FreeSimulation(pSim, (int) ceil((pn->params)[0][0]));
	FreeNoise(pn);
	FreeResult(pmcr);
	return summary;
}
