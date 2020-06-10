#include <stdio.h>
#include <stdlib.h>
#include "notations.h"

void NoiseParameters(struct representation *repr){
	// Assign names for the different noise parameters
	int vi, degfreedom[5] = {1, 1, 3, 3, 4};
	repr->nvars = degfreedom[repr->model];
	repr->varnames = malloc(sizeof(char *) * repr->nvars);
	repr->mname = malloc(sizeof(char *) * 100);
	for (vi = 0; vi < repr->nvars; vi ++)
		(repr->varnames)[vi] = malloc(sizeof(char) * 100);

	if (repr->model == 1){
		sprintf(repr->mname, "uncorr");
		sprintf((repr->varnames)[0], "p");
	}
	else if (repr->model == 2){
		sprintf(repr->mname, "ball");
		sprintf((repr->varnames)[0], "p");
		sprintf((repr->varnames)[1], "<r>");
		sprintf((repr->varnames)[2], "<r^2>");
	}
	else if (repr->model == 3){
		sprintf(repr->mname, "walk");
		sprintf((repr->varnames)[0], "p");
		sprintf((repr->varnames)[1], "<d>");
		sprintf((repr->varnames)[2], "<d^2>");
	}
	else{
		sprintf(repr->mname, "unknown");
		sprintf((repr->varnames)[0], "X");
	}
}


void FixRepresentation(struct representation *repr, int model){
	// Initialize the representation data structure
	repr->model = model;
	repr->nvars = 0;
	repr->varnames = NULL;
	repr->mname = NULL;
	NoiseParameters(repr);
}

void FreeRep(struct representation *repr){
	// Free a representation structure
	int vi;
	for (vi = 0; vi < repr->nvars; vi ++)
		free(repr->varnames[vi]);
	free(repr->varnames);
	free(repr->mname);
}


void TilingFile(char* tilingFile, int family, int length){
	if(family == 1)
		sprintf(tilingFile, "%d_toric_square", length);
	else if(family == 2)
		sprintf(tilingFile, "6_6_%d_trivalent_hyp", length);
	else if(family == 3)
		sprintf(tilingFile, "6_%d_selfdual", length);
	else
		sprintf(tilingFile, "family%d_length%d", length, length);
}
