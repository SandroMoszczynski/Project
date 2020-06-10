/*
The MIT License (MIT)

Copyright (c) <2016> <Nicolas Delfosse, Pavithran Iyer>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/





#ifndef DUAL_H
#define DUAL_H

//return the dual tiling
extern struct tiling DualTiling(struct tiling);

//return the array EToDE of indices of the dual edges.
//EToDE[k] is the index of the dual edge of the k-th
//edge ek of the tiling.
//EToDE[k] = -1, if ek is not an open edge. This indicates
//that ek has no dual edge.
extern int *EToDualE(struct tiling G);

#endif	/* DUAL_H */
