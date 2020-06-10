/*
The MIT License (MIT)

Copyright (c) <2016> <Nicolas Delfosse, Pavithran Iyer>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/



#ifndef HOLES_H
#define HOLES_H

//create a hole by replacing a faces by holes
//the second input is the indicator vector of the set of faces
extern void CreateHole(struct tiling *, int *);

//create a rectangle hole
//input: the tiling and the indices of 2 vertices i and j
//output: create a rectangle hole in the rectangle having
//vi and vj as opposite corners.
extern void CreateRectangleHole(struct tiling *, int, int);

//create a rectangle hole with open boundaries
//input: the tiling and the indices of 2 vertices i and j
//output: create a rectangle hole in the rectangle having
//vi and vj as opposite corners.
//Open the edges of the rectangle
extern void CreateOpenRectangleHole(struct tiling *, int, int);

//Open a subset of edges
//These egdes are given by their indicator vector
extern void OpenBoundary(struct tiling *, int *);

//Close a subset of edges
//These egdes are given by their indicator vector
extern void CloseBoundary(struct tiling *, int *);

#endif	/* HOLES_H */
