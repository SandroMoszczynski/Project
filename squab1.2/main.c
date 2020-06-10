#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "memory.h"
#include "tiling.h"
#include "holes.h"
#include "draw.h"
#include "dual.h"
#include "weights.h"
#include "cell.h"
#include "grid.h"
#include "regulartilings.h"
#include "components.h"
#include "simulation.h"
#include "rgens.h"
#include "arrays.h"
#include "save.h"
#include "load.h"
#include "notations.h"
#include "mcresult.h"
#include "noise.h"
#include "homological.h"
#include "performance.h"
#include "help.h"



int main(int argc, char **argv)
{
	//initialize rand()
	srand((unsigned)(time(0)));

	char function[100];
	function[0] = 0;
	int *input = malloc(2*sizeof(int));
	input[0] = 0;
	input[1] = 0;
	int *size = malloc(sizeof(int));
	size[0] = 0;
	
	//tiling inputs
	struct tiling G; 
	InitTiling(&G);
	struct tiling Gtemp; 
	InitTiling(&Gtemp);

	int *H;
	int i;
	int *OpenE;
	int *CloseE;

	//perf inputs
	struct storePerformance perf;
	InitStorage(&perf);

	PrintHelpMin();

	while (strncmp(function, "Quit", 4) != 0)
	{
//=========================
//HELP
//=========================
		
//HelpMin
		if (strncmp(function, "HelpMin", 7) == 0)
		{
			PrintHelpMin();
			function[0] = 0;
		}

//Help
		if (strncmp(function, "Help", 4) == 0)
		{
			PrintHelp();
			function[0] = 0;
		}
		

//=========================
//TILING CONSTRUCTION
//=========================

//Tiling
		if (strncmp(function, "Tiling", 6) == 0)
		{
			scanf("%d %d %d", input, &(input[1]), &(input[2]));			
			//test inputs
			if ( (input[0] != 3) && (input[0] != 4) && (input[0] != 6))
				printf("    Error: The degree must be 3, 4 or 6\n");
			else if ( (input[1]<= 0) || (input[2]<= 0))
				printf("    Error: The lengths must be positive\n");						
			//construct tiling
			else
			{
				FreeTiling(&G);
				InitTiling(&G);
				if (input[0] == 3)
				{
					printf("Creation of a %dx%d hexagonal tiling\n", input[1], input[2]);
					FreeTiling(&G);
					G = HexagonalTiling(input[1], input[2]);
				}
				else if (input[0] == 6)
				{
					printf("Creation of a %dx%d triangular tiling\n", input[1], input[2]);
					FreeTiling(&G);
					G = TriangularTiling(input[1], input[2]);
				}
				else if (input[0] == 4)
				{
					printf("Creation of a %dx%d square tiling\n", input[1], input[2]);				
					FreeTiling(&G);
					G = SquareTiling(input[1], input[2]);
				}
				printf("Done\n");
			}
			function[0] = 0;
			input[0] = 0;
			input[1] = 0;
		}

//Grid
		if (strncmp(function, "Grid", 4) == 0)
		{
			//test input
			scanf(" %d %d", input, &(input[1]));
			if ( (input[0]<= 0) || (input[1]<= 0))
				printf("    Error: The lengths must be positive\n");
			else
			{
				FreeTiling(&G);
				InitTiling(&G);				
				// printf("Creation a %dx%d grid of vertices\n", input[0], input[1]);
				G = Grid(input[0], input[1]);
				printf("Done\n");
			}
			function[0] = 0;
			input[0] = 0;
			input[1] = 0;			
		}

//AddFace
		if (strncmp(function, "AddFace", 7) == 0)
		{
			scanf(" %d", size);
			int *vertexList = malloc(size[0]*sizeof(int));
			for (i=0; i<size[0]; i++)
					scanf(" %d", &(vertexList[i]));

			//test inputs
			int check = 0;
			for (i=0; i<size[0]; i++)
				if ((vertexList[i] > G.v-1) || (vertexList[i] < 0))
					check = 1;		
			
			if (size[0] < 3)
				printf("    Error: The length of a face must be at least  3\n");

			else if (check == 1)
				printf("    Error: These numbers must be vertex indices\n");			

			else
			{
				// printf("Create a face from the list of vertices on its boundary\n");
				AddFace(&G, vertexList, size[0]);			
				printf("Done\n");
			}
			free(vertexList);
			function[0] = 0;
		}
		
//Translate		
		if (strncmp(function, "Translate", 9) == 0)
		{
			float *t = malloc(2*sizeof(float *));
			int *n = malloc(1*sizeof(int *));
			scanf(" %d", n);
			scanf(" %f %f", &(t[0]), &(t[1]));

			if (n[0] <= 0)
				printf("    Error: The number of translations must be positive\n");
			else
			{
				// printf("Create %d translated copies of the tiling in the direction (%f,%f)\n", n[0], t[0], t[1]);
				FreeTiling(&Gtemp);
				Gtemp = G;
				G = PeriodicTiling(G, t, n[0]);
			
				free(n);
				free(t);

				printf("Done\n");
			}
			function[0] = 0;
		}

//CleanV
		if (strncmp(function, "CleanV", 5) == 0)
		{
			// printf("Remove isolated vertices\n");
			RemoveIsolatedVertices(&G);
			function[0] = 0;
			printf("Done\n");
		}

//=========================
//DISPLAY TILINGS
//=========================

//Print
		if (strncmp(function, "Print", 5) == 0)
		{
			if (G.v == 0)
				printf("    Error: Empty tiling\n");
			else
			{
				// printf("Print the tiling in the terminal\n");
				PrintTiling(G);
				printf("Done\n");
			}
			function[0] = 0;
		}

		
//DrawDualMin
		if (strncmp(function, "DrawDualMin", 11) == 0)
		{
			if (G.Coord == NULL)
				printf("    Error: No Coordinate\n");
			else
			{
				// printf("Draw dual tiling\n");
				RemoveIsolatedVertices(&G);
				struct tiling H = DualTiling(G);
				DrawMin(H, "figure", 'r');
				FreeTiling(&H);
				printf("Done\n");
			}
			function[0] = 0;
		}

//DrawDual
		if (strncmp(function, "DrawDual", 8) == 0)
		{
			if (G.Coord == NULL)
				printf("    Error: No Coordinate\n");
			else
			{
				// printf("Draw indexed dual tiling\n");
				RemoveIsolatedVertices(&G);
				struct tiling H = DualTiling(G);
				Draw(H, "figure", 'r');
				FreeTiling(&H);
				printf("Done\n");
			}
			function[0] = 0;
		}


//DrawMin
		if (strncmp(function, "DrawMin", 7) == 0)
		{
			if (G.Coord == NULL)
				printf("    Error: No Coordinate\n");
			else
			{			
				// printf("Draw tiling\n");
				DrawMin(G, "figure", 'b');
				printf("Done\n");
			}
			function[0] = 0;			
		}

//Draw
		if (strncmp(function, "Draw", 4) == 0)
		{
			if (G.Coord == NULL)
				printf("    Error: No Coordinate\n");
			else
			{			
				// printf("Draw indexed tiling\n");
				Draw(G, "figure", 'b');
				printf("Done\n");
			}
			function[0] = 0;
		}


//=========================
//TILING SURGERY
//=========================

//HoleRectangleOpen
		if (strncmp(function, "HoleRectOpen", 12) == 0)
		{
			scanf(" %d %d", input, &(input[1]));
			if ( (input[0] > G.v-1) || (input[0] < 0) || (input[1] > G.v-1) || (input[1] < 0) )
				printf("    Error: These numbers must be vertex indices\n");			
			
			else
			{
				// printf("Create a rectangle hole\n");
				CreateOpenRectangleHole(&G, input[0], input[1]);
			}
			printf("Done\n");
			function[0] = 0;			
			input[0] = 0;
			input[1] = 0;
		}



//HoleRectangle
		if (strncmp(function, "HoleRect", 8) == 0)
		{
			scanf(" %d %d", input, &(input[1]));
			if ( (input[0] > G.v-1) || (input[0] < 0) || (input[1] > G.v-1) || (input[1] < 0) )
				printf("    Error: These numbers must be vertex indices\n");			
			
			else
			{
				// printf("Create a rectangle hole\n");
				CreateRectangleHole(&G, input[0], input[1]);
			}
			printf("Done\n");
			function[0] = 0;			
			input[0] = 0;
			input[1] = 0;
		}

//HoleList
		if (strncmp(function, "HoleList", 8) == 0)
		{
			//store inputs
			scanf(" %d", size);
			int *faceList = malloc(size[0]*sizeof(int));
			for (i=0; i<size[0]; i++)
					scanf(" %d", &(faceList[i]));

			//test inputs
			int check = 0;
			for (i=0; i<size[0]; i++)
				if ((faceList[i] > G.f-1) || (faceList[i] < 0))
					check = 1;	
			
			if (size[0] <= 0)
				printf("    Error: The length of a face must be a positive integer\n");

			else if (check == 1)
				printf("    Error: These numbers must be face indices\n");			

			//apply function
			else
			{
				// printf("Remove a list of faces\n");	
				H = malloc(G.f*sizeof(int));
				for (int i=0; i<G.f; i++) H[i]=0;
				for (i=0; i<size[0]; i++)
				{
					H[faceList[i]] = 1;
				}
				CreateHole(&G, H);
				free(H);
				printf("Done\n");
			}
			free(faceList);			
			function[0] = 0;
			size[0] = 0;
		}

//Hole
		if (strncmp(function, "Hole", 4) == 0)
		{
			scanf(" %d", input);
			if ((input[0] > G.f-1) || (input[0] < 0))
				printf("    Error: The input must be a face index\n");			

			else
			{
				// printf("Remove a face\n");		
				H = malloc(G.f*sizeof(int));
				for (int i=0; i<G.f; i++) H[i]=0;
				H[input[0]] = 1;
				CreateHole(&G, H);
				free(H);
				printf("Done\n");
			}
			function[0] = 0;			
			input[0] = 0;
		}

//=========================
//OPERATION ON BOUNDARY EDGES
//=========================		
		
//OpenList
		if (strncmp(function, "OpenList", 8) == 0)
		{
			//store inputs
			scanf(" %d", size);
			int *edgeList = malloc(size[0]*sizeof(int));
			for (i=0; i<size[0]; i++)
					scanf(" %d", &(edgeList[i]));

			//test inputs
			int check = 0;
			for (i=0; i<size[0]; i++)
				if ((edgeList[i] > G.e-1) || (edgeList[i] < 0))
					check = 1;
			
			if (size[0] <= 0)
				printf("    Error: The length of a face must be a positive integer\n");

			else if (check == 1)
				printf("    Error: These numbers must be edge indices\n");			

			//apply function
			else
			{
				// printf("Open a list of edges\n");
				OpenE = malloc(G.e*sizeof(int));
				for (int i=0; i<G.e; i++) OpenE[i]=0;
				for (i=0; i<size[0]; i++)
					OpenE[edgeList[i]] = 1;

				OpenBoundary(&G, OpenE);
				free(OpenE);
				printf("Done\n");
			}
			free(edgeList);
			function[0] = 0;
			input[0] = 0;
		}

//Open
		if (strncmp(function, "Open", 4) == 0)
		{
			//store inputs
			scanf(" %d", input);

			//test inputs
			if ((input[0] > G.e-1) || (input[0] < 0))
				printf("    Error: The input must be an edge index\n");

			//apply function
			else
			{
				// printf("Open an edge\n");

				OpenE = malloc(G.e*sizeof(int));
				for (i=0; i<G.e; i++) OpenE[i] = 0;
				OpenE[input[0]] = 1;
				OpenBoundary(&G, OpenE);
				free(OpenE);
				printf("Done\n");
			}
			function[0] = 0;			
			input[0] = 0;
		}

//CloseList
		if (strncmp(function, "CloseList", 9) == 0)
		{
			//store inputs
			scanf(" %d", size);
			int *edgeList = malloc(size[0]*sizeof(int));
			for (i=0; i<size[0]; i++)
					scanf(" %d", &(edgeList[i]));

			//test inputs
			int check = 0;
			for (i=0; i<size[0]; i++)
				if ((edgeList[i] > G.e-1) || (edgeList[i] < 0))
					check = 1;
			
			if (size[0] <= 0)
				printf("    Error: The length of a face must be a positive integer\n");

			else if (check == 1)
				printf("    Error: These numbers must be edge indices\n");			

			//apply function
			else
			{
				// printf("Close a list of edges\n");
				CloseE = malloc(G.e*sizeof(int));
				for (int i=0; i<G.e; i++) CloseE[i]=0;
				for (i=0; i<size[0]; i++)
					CloseE[edgeList[i]] = 1;

				CloseBoundary(&G, CloseE);
				free(CloseE);
				printf("Done\n");
			}
			free(edgeList);			
			function[0] = 0;
			input[0] = 0;
		}

//Close
		if (strncmp(function, "Close", 5) == 0)
		{
			//store inputs
			scanf(" %d", input);

			//test inputs
			if ((input[0] > G.e-1) || (input[0] < 0))
				printf("    Error: The input must be an edge index\n");

			//apply function
			else
			{
				// printf("Close an edge\n");
				CloseE = malloc(G.e*sizeof(int));
				for (i=0; i<G.e; i++) CloseE[i] = 0;
				CloseE[input[0]] = 1;
				CloseBoundary(&G, CloseE);
				free(CloseE);
				printf("Done\n");
			}
			function[0] = 0;			
			input[0] = 0;
		}


//=========================
//BENCHMARKING
//=========================

//Code
		if (strncmp(function, "Code", 4) == 0)
		{
			printf("Code parameters\n");
			int n = G.e;
			int k = HomDim(G);
			printf("    number of physical qubits: n=%d\n", n);
			printf("    number of logical qubits: k=%d\n", k);
			printf("    overhead: n/k=%.2f\n", ((float) n)/((float) k));
			function[0] = 0;
			printf("Done\n");
		}


//Report
		if (strncmp(function, "Report", 5) == 0)
		{
			if (G.v == 0)
				printf("    Error: Empty tiling\n");
			else
			{
				RemoveIsolatedVertices(&G);
			
				//store tiling name
				perf.tilingName = malloc(100*sizeof(char));
				strcpy(perf.tilingName, G.type);

				//store code inputs
				perf.n = G.e;
				perf.k = HomDim(G);

				//store measurement weights
				struct tiling H = DualTiling(G);
				perf.maxWeight = MaxWeight(G, H);
				perf.ZWeight = FaceMeasurementWeights(G, perf.maxWeight);
				perf.XWeight = FaceMeasurementWeights(H, perf.maxWeight);

				//store performance file name
				perf.noiseRange = malloc(3*sizeof(double));
				long stats;
				scanf("%lf %lf %lf %ld", &(perf.noiseRange[0]), &(perf.noiseRange[1]), &(perf.noiseRange[2]), &stats);
				
	            //The noise model is assumed to be of type 1 (see noise.h), 
    	        //that is the uncorrelated erasure model.
        	    double **noiseparams = malloc(sizeof(double) * 2);
            	noiseparams[0] = malloc(sizeof(double));
	            noiseparams[0][0] = 1;
    	        noiseparams[1] = malloc(sizeof(double) * 3);
        	    noiseparams[1][0] = perf.noiseRange[0];
            	noiseparams[1][1] = perf.noiseRange[1];
	            noiseparams[1][2] = perf.noiseRange[2];
    	        char *timestamp = malloc(sizeof(char) * 100);
    	        printf("Simulation for tiling %s in progress...\n", perf.tilingName);	
        	    sprintf(timestamp, "%s", Performance(G, 1, noiseparams, stats));
				printf("Simulation done\n");	

				//report
				perf.dataFile = malloc(sizeof(char) * 400);
				sprintf(perf.dataFile, "perf_%s.txt", timestamp);
				printf("Compilation of the report in progress...\n");	
				Report(G, H, &perf, timestamp);
				printf("Report generated in folder reports/\n");
				printf("Done\n");

				free(timestamp);
				FreeTiling(&H);
			}			
			function[0] = 0;						
		}

//=========================
//SAVE TILINGS
//=========================

//Save
		if (strncmp(function, "Save", 4) == 0)
		{
			char *tilingName = malloc(sizeof(char) * 100);
			scanf("%s", tilingName);
			Save(G, tilingName);
			function[0] = 0;
			printf("Done\n");
		}

//Load
		if (strncmp(function, "ListTilings", 4) == 0)
		{
			ListTilings("saved_tilings");
		}

		if (strncmp(function, "Load", 4) == 0)
		{
			char *tilingName = malloc(sizeof(char) * 100);
			scanf("%s", tilingName);
			if (G.v != 0)
				FreeTiling(&G);
			G = Load(tilingName);
			function[0] = 0;
			printf("Done\n");
		}
			
		printf(">>");
		scanf("%s", function);
	}
}



