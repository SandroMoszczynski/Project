#include <stdio.h>
#include <stdlib.h>
#include "tiling.h"
#include "arrays.h"
#include "rgens.h"
#include "simulation.h"
#include "correlations.h"

void BubbleGrow(int root, int inEdge, int dist, int target, int *visited, struct simulation *pSim, struct tiling *pG){
	// Explore erased edges that lie in a ball of a given radius around a given edge.
	if (dist == target);
	else{
		if (visited[root] == 1);
		else{
			visited[root] = 1;
			(pSim->erasure)[1][inEdge] = 1;
			int vi;
			for (vi = 1; vi <= (pG->VToN)[root][0]; vi ++){
				if ((pG->doE)[(pG->VToE)[root][vi]] == 0)
					BubbleGrow((pG->VToN)[root][vi], (pG->VToE)[root][vi], dist + 1, target, visited, pSim, pG);
			}
		}
	}
}

void BallErasure(struct simulation *pSim, struct tiling *pG, double *specs){
	// Erasing edges inside a ball of fixed radius around an edge
	int ei, radius;
	int *visited = malloc(sizeof(int) * pG->v);
	radius = (int) Random("normal", specs + 1);
	for (ei = 0; ei < pG->e; ei ++){
		if ((pG->doE)[ei] == 0){
			if (Random("uniform", NULL) < specs[0]){
				FillIntArrayWithConstants(visited, pG->v, 0);
				BubbleGrow((pG->E)[ei][0], ei, 0, radius, visited, pSim, pG);
				BubbleGrow((pG->E)[ei][1], ei, 0, radius, visited, pSim, pG);
			}
		}
	}
}

void Walk(int inEdge, int nsteps, int target, struct simulation *pSim, struct tiling *pG){
	// Starting from a given edge, walk in any random direction, on unerased edges, for a fixed number of steps.
	if (nsteps == target);
	else{
		int pi, ei, nout, endp, next = 0, direction, count;
		(pSim->erasure)[1][inEdge] = 1;
		nout = 0;
		for (pi = 0; pi < 2; pi ++){
			endp = (pG->E)[inEdge][pi];
			for (ei = 1; ei <= (pG->VToE)[endp][0]; ei ++){
				if ((pG->doE)[ei] == 0){
					// fprintf(stderr, "(pSim->erasure)[1][%d] = %d\n", ei, (pSim->erasure)[1][ei]);
					if ((pSim->erasure)[1][ei] == 0)
						nout ++;
				}
			}
		}
		// Pick a random number between 0 and nout. This number will denote the index of the edge that will constitute the next step of the walk.
		direction = (int) (nout * Random("uniform", NULL));
		// fprintf(stderr, "nout = %d, Direction = %d\n", nout, direction);
		count = 0;
		for (pi = 0; pi < 2; pi ++){
			endp = (pG->E)[inEdge][pi];
			for (ei = 1; ei <= (pG->VToE)[endp][0]; ei ++){
				if ((pG->doE)[(pG->VToE)[endp][ei]] == 0){
					if ((pSim->erasure)[1][(pG->VToE)[endp][ei]] == 0){
						if (count == direction){
							next = (pG->VToE)[endp][ei];
						}
						count ++;
					}
				}
			}
		}
		// Proceed to the next step of the random walk
		Walk(next, nsteps + 1, target, pSim, pG);
	}
}


void WalkErasure(struct simulation *pSim, struct tiling *pG, double *specs){
	// Design a correlated model of erasure where a random path originating from an erased edge, is also erased.
	int ei, length;
	length = (int) Random("normal", specs + 1);
	for (ei = 0; ei < pG->e; ei ++)
		if ((pG->doE)[ei] == 0)
			if (Random("uniform", NULL) < specs[0])
				Walk(ei, 0, length, pSim, pG);
}