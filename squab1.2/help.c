#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void PrintHelp()
{
	printf("\n    LIST OF THE COMMANDS:\n\n");

	printf("*********  Tiling Construction  **********\n");
	
	printf("Tiling d lx ly \n");
	printf("    input: d = 3, 4 or 6, lx, ly = postive integers\n");
	printf("    output: Create a d-regular tiling of size lx x ly\n\n");

	printf("Grid lx ly \n");
	printf("    input: lx, ly = postive integers\n");
	printf("    output: Create a grid of vertices of size lx x ly\n\n");

	printf("AddFace k v1 v2 ... vk\n");
	printf("    input: k = postive integer, v1, v2, ... vk = vertex indices\n");
	printf("    output: Create a face from this ordered list of vertices\n\n");

	printf("Translate k u v\n");
	printf("    input: k = postive integer, u, v = real numbers\n");
	printf("    output: Replicate the tiling k times by translating it in \n      the direction (u,v) \n\n");

	printf("CleanV\n");
	printf("    input: no input\n");
	printf("    output: Remove isolated vertices of the tiling\n\n");
	
	printf("Hole f\n");
	printf("    input: f = a face index\n");
	printf("    output: Remove the face f from the tiling\n\n");

	printf("HoleList k f1 f2 ... fk\n");
	printf("    input: k = postive integer, f1, f2, ... fk = face indices\n");
	printf("    output: Remove the k faces f1, f2, ... fk from the tiling\n\n");

	printf("HoleRect u v\n");
	printf("    input: u, v = vertex indices\n");
	printf("    output: Remove all the face f inside the rectangle whose\n      opposite corners are u and v\n\n");

	printf("HoleRectOpen u v\n");
	printf("    input: u, v = vertex indices\n");
	printf("    output: Remove all the face f and open all the edges\n    inside the rectangle whose opposite corners\n    are u and v\n\n");

	printf("Open e\n");
	printf("    input: e = an edge index\n");
	printf("    output: Open the edge e if it is a boundary\n\n");

	printf("OpenList k e1 e2 ... ek\n");
	printf("    input: k = postive integer, e1, e2, ... ek = edge indices\n");
	printf("    output: Open the k edges e1, e2, ... ek if they are on the boundary\n\n");

	printf("Close e\n");
	printf("    input: e = an edge index\n");
	printf("    output: Close the edge e\n\n");

	printf("CloseList k e1 e2 ... ek\n");
	printf("    input: k = postive integer, e1, e2, ... ek = edge indices\n");
	printf("    output: Close the k edges e1, e2, ... ek\n\n");

	printf("************  Display Tiling  ************\n");

	printf("Print\n");
	printf("    input: no input\n");
	printf("    output: Print the tiling in the terminal\n\n");

	printf("Draw\n");
	printf("    input: no input\n");
	printf("    output: Draw the tiling with indices\n\n");

	printf("DrawMin\n");
	printf("    input: no input\n");
	printf("    output: Draw the tiling\n\n");

	printf("DrawDual\n");
	printf("    input: no input\n");
	printf("    output: Draw the dual tiling with indices\n\n");

	printf("DrawDualMin\n");
	printf("    input: no input\n");
	printf("    output: Draw the dual tiling\n\n");

	printf("**************  Save Tiling  *************\n");

	printf("Save name\n");
	printf("    input: tiling name\n");
	printf("    output: Save the tiling in the folder saved_tilings\n\n");

	printf("Load name\n");
	printf("    input: tiling name\n");
	printf("    output: Load a tiling from the folder saved_tilings.\nYou can use ListTilings before to see all the saved tilings\n\n");

	printf("ListTilings\n");
	printf("    input: no input\n");
	printf("    output: List all the saved tilings in the folder saved_tilings\n\n");

	printf("*************  Benchmarking  *************\n");

	printf("Code\n");
	printf("    input: no input\n");
	printf("    output: Return the parameters of the surface code based\n      on the tiling\n\n");

	printf("Report pmin pmax step numtrial\n");
	printf("    input:\n      pmin, pmax = real numbers such that 0 <= pmin <= pmax <= 1\n      step = real number in [0,1]\n      numtrial = non-negative integer\n");
	printf("    output:\n      Generate a report on the performance of the code\n      in the folder reports by testing the performance\n      for erasure rate from pmin to pmax with step size\n      given by step. Up to numtrial decoding trials are ran for\n      each data point\n\n");

	printf("*****************  Help  *****************\n");

	printf("Help\n");
	printf("    input: no input\n");
	printf("    output: Print the documented list of all the commands\n\n");

	printf("HelpMin\n");
	printf("    input: no input\n");
	printf("    output: Print the list of all the commands\n\n");

	printf("******************************************\n\n");

	printf("Website:\n");
	printf("Check out our website for more documentation\n");
	printf("http://quantum-squab.com\n\n");
	}




//print the list of all the functions
void PrintHelpMin()
{
	printf("\n    LIST OF THE COMMANDS:\n\n");

	printf("*********  Tiling Construction  **********\n");
	
	printf("Tiling d lx ly \n");
	printf("Grid lx ly \n");
	printf("AddFace k v1 v2 ... vk\n");
	printf("Translate k u v\n");
	printf("CleanV\n");
	printf("Hole f\n");
	printf("HoleList k f1 f2 ... fk\n");
	printf("HoleRect u v\n");
	printf("HoleRectOpen u v\n");
	printf("Open e\n");
	printf("OpenList k e1 e2 ... ek\n");
	printf("Close e\n");
	printf("CloseList k e1 e2 ... ek\n");

	printf("************  Display Tiling  ************\n");

	printf("Print\n");
	printf("Draw\n");
	printf("DrawMin\n");
	printf("DrawDual\n");
	printf("DrawDualMin\n");

	printf("**************  Save Tiling  *************\n");

	printf("Save\n");
	printf("Load\n");
	printf("ListTilings\n");

	printf("*************  Benchmarking  *************\n");

	printf("Code\n");
	printf("Report pmin pmax step numtrial\n");

	printf("*****************  Help  *****************\n");

	printf("Help\n");
	printf("HelpMin\n");
	
	printf("******************************************\n\n");

	printf("Website:\n");
	printf("Check out our website for more documentation\n");
	printf("http://quantum-squab.com\n\n");

}



