/*
The MIT License (MIT)

Copyright (c) <2016> <Nicolas Delfosse, Pavithran Iyer>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/



#ifndef SAVE_H
#define SAVE_H

extern void DeleteFile(char* fname);
/*
	Function to delete a file, if it exists and is allowed to be deleted.
	
	Input: name of a file (fname)
	Output: Nothing -- File with name fname is deleted using the system command "rm -f".
	Algorithm: Uses access(fname, R_OK|F_OK) of unistd.h to test various perperties of the file.
*/

extern void Save(struct tiling, char* fname);
/*
	Input: pointer to a Tiling (pG)
		   the name of the file to which the tiling needs to be saved
	Output: Nothing
	Algorithm: Write the edges, faces and the indices of open edges of a tiling, into a file.
			   The file names are: Edges ---  (pG->type)_edges.txt
			   					   Faces ---  (pG->type)_faces.txt
			   					   Open Edges ---  (pG->type)_open_edges.txt
*/

#endif	/* SAVE_H */
