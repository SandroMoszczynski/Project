/*
The MIT License (MIT)

Copyright (c) <2016> <Nicolas Delfosse, Pavithran Iyer>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/



#ifndef PERFORMANCE_H
#define PERFORMANCE_H

extern char* Performance(struct tiling G, int model, double **noiseParams, long stats);
/*
	Analyze the performance of a code (defined with a tiling) with montecarlo simulation of specific number of decoding trails
		Inputs: 
				struct tiling -- Tiling specifying the code
				
				int model -- Integer to specify a type of noise model (See noise.h)
					value 		Description of the model
					0 			i.i.d erasure channel
					1 			Every qubit is picked to represent the center of a ball. All qubits in a radius around the ball are erased.
					2 			A cluster of erased edges formed by taking a random walk from some edge

				double **noiseParams -- array of (M+1) double-pointers, where M is the number of parameters to specify the noise model.
					noiseParams[0] = array of size 1.
					noiseParams[0][0] = number of parameters used to specify the noise model
						noise model 	number of parameters
							0 					1
							1 					3
							2					3

					For all j = 1 to M,
					noiseParams[j] = array of 3 double-numbers to specify the range of parameter j -- [lower limit, upper limit, step size]
				
				long stats -- maximum number of Montecarlo trials for estimating a failure rate.
				
		Output: char* -- string containing the local-time-stamp associated with the simulation.
						The names of the file containing the performance results and the runtimes can be derived from this timestamp, as
						performance output file = perf_<timestamp>.txt, selected_perf_<timestamp>.txt
						runtimes file = runtimes_<timestamp>.txt
*/
#endif	/* PERFORMANCE_H */
