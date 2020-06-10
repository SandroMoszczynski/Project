#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "memory.h"
#include "arrays.h"
#include "notations.h"
#include "tiling.h"
#include "mcresult.h"
#include "noise.h"

void InitializeNoise(struct noise *pn, struct tiling *pG, int model, double **prange){
	// Initialize the parameters of a noise model
	int pi, nvals, nparams;
	pn->model = model;
	// Part 2,3
	double **expanded = malloc(sizeof(double *) * (1 + (int) prange[0][0]));
	expanded[0] = malloc(sizeof(double));
	expanded[0][0] = prange[0][0];
	for(pi = 1; pi <= (int) prange[0][0]; pi ++){
		nvals = 1 + (int)((prange[pi][1] - prange[pi][0])/prange[pi][2]);
		expanded[pi] = malloc(sizeof(double) * (nvals + 1));
		expanded[pi][0] = (double) nvals;
		Expand(prange[pi], expanded[pi]);
	}
	// Part 4,5
	nparams = (int)(1 + Prod(Slice(expanded + 1, (int) expanded[0][0], 0), (int) expanded[0][0]));
	pn->params = malloc(sizeof(double *) * nparams);
	(pn->params)[0] = malloc(sizeof(double) * 2);
	for (pi = 1; pi < nparams; pi ++)
		(pn->params)[pi] = malloc(sizeof(double) * (int) ceil(prange[0][0]));
	CartesianProduct(expanded, pn->params);
	pn->current = 0;
	// Free local memory
	FreeDoubleArray(expanded, (1 + (int) prange[0][0]));
}

void FreeNoise(struct noise *pn){
	// Free a noise structre
	FreeDoubleArray(pn->params, 1 + (pn->params)[0][0]);
}

void PrintNoise(struct noise *pn){
	// Print the values of the noise parameters, that correspond to the current simulation when the function is called.
	// "Current" noise parameters are in (pn->params)[pn->current]
	int vi;
	struct representation *repr = malloc(sizeof(struct representation));
	FixRepresentation(repr, pn->model);
	fprintf(stderr, "%s = %g", (repr->varnames)[0], (pn->params)[pn->current][0]);
	for (vi = 1; vi < (pn->params)[0][1]; vi ++)
		fprintf(stderr, ", %s = %g", (repr->varnames)[vi], (pn->params)[pn->current][vi]);
	fprintf(stderr, ".\n");
	FreeRep(repr);
}
