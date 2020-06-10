/*
The MIT License (MIT)

Copyright (c) <2016> <Nicolas Delfosse, Pavithran Iyer>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/



#ifndef NOTATIONS_H
#define NOTATIONS_H

struct representation
{
	/* Data required to verbally express a noise model. See noise.h for details. */
	// Index for the noise model.
	int model;
	// Name of the noise model.
	char *mname;
	// Number of parameters to describe a noise process.
	int nvars;
	// Names/symbols of the parameters.
	char **varnames;
};

// Initialize the representation data structure
extern void FixRepresentation(struct representation *repr, int model);

// Assign names for the different noise parameters
extern void NoiseParameters(struct representation *repr);

// Free a representation structure
extern void FreeRep(struct representation *repr);

// Return the name of the file that must contain the simulation results for a particular noise model
extern void FileNames(char *fname, char *tileName, int model, double *values);

/*
	Assign a name to a tiling, that is derived from an index for a family and the length of the tiling.
	For a few standard families of tilings, we have the given names.
	The edges, faces, open edges and vertex-coordinates are stored in the files
			./../saved_tilings/tiling_folder/<tilingName>_edges.txt,
			./../saved_tilings/tiling_folder/<tilingName>_faces.txt,
			./../saved_tilings/tiling_folder/<tilingName>_open_edges.txt,
			./../saved_tilings/tiling_folder/<tilingName>_coordinates.txt,
	respectively.
*/
extern void TilingFile(char* tilingFile, int family, int length);

#endif /* NOTATIONS_H */
