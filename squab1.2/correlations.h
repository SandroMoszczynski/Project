/*
The MIT License (MIT)

Copyright (c) <2016> <Nicolas Delfosse, Pavithran Iyer>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/




#ifndef CORRELATIONS_H
#define CORRELATIONS_H

/* 
	Design a correlated erasure pattern on n-bits in the following way.
	At every edge of the lattice, erase the edge with probability p and if the edge is erased, erase all the edges in a radius r around the erased edge.
	Algorithm:
		Function BubbleGrow(...) -- Erasing edges inside a ball of fixed radius around an edge
		Start from a vertex v0
		Recursion:
			1. For every neighbour of v0 that is not visited, erase the corresponding outgoing edge
			2. Call BubbleGrow on the endpoint of the erased edge, to explore erased edges that lie in a ball of a given radius.

*/
extern void BallErasure(struct simulation *pSim, struct tiling *pG, double *specs);

/*
	Design a correlated model of erasure where a random path originating from an erased edge, is also erased.
	The length of the random walk as well as the probability of choosing a root edge for the walk, are provided in "specs".
	Algorithm:
		Function Walk(...) -- Starting from a given edge, walk in any random direction, on unerased edges, for a fixed number of steps.
*/
extern void WalkErasure(struct simulation *pSim, struct tiling *pG, double *specs);

#endif /* CORRELATIONS_H */
