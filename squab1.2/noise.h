/*
The MIT License (MIT)

Copyright (c) <2016> <Nicolas Delfosse, Pavithran Iyer>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/



#ifndef NOISE_H
#define NOISE_H

struct noise
{
	// All the parameters of a noise model
	/*
		Description of a noise model.
		model: integer
			value 		Description of the model
			0 			i.i.d erasure channel
			1 			Every qubit is picked to be the root according to a binomial distribution. A cluster formed by taking a ball centered at the root, is erased.
			2 			Every qubit is picked to be the root according to a binomial distribution. A cluster formed by taking a random walk from the root, is erased.
	*/
	int model;
	
	/*
		Parameters that specify a noise. 
		params: array of M+1 double pointers, where M is the total number of noise rates in the simulation.
		The array is formatted as follows.
			params[0][0] = number of noise rates. A simulation must be performed for every noise rate.
			params[0][1] = number of parameters specifying a noise rate
			params[j] = list of noise rates that specify a noise process
						uncorrelated erasures: param[j] = qubit erasure rate
						ball erasure: params[j] = qubit erasure rate, ball radius
						walk erasure: params[j] = qubit erasure rate, steps in the walk
	*/
	double **params;

	// index of the current noise rate that is being simulated. This will be overwritten after every noise rate simulation.
	int current;
};

/*
	Initialize the parameters of a noise model
	1. A noise process can be described by one or more parameters, depending on the type of noise model chosen.
	2. The values of every parameter must be obtained by scanning a range associated to that parameter. 
	3. First we must expand all the ranges to obtain all the values of every parameter. 
	
	This is important for noise models where a noise process is described by more than one parameter.
	4. Then, we must compute all possible noise rates -- that is all possible conbinations of the expanded sets (Cartesian Product).
	5. Each such combination specifies one noise process.
*/
extern void InitializeNoise(struct noise *pn, struct tiling *pG, int model, double **prange);

// Update the parameters of a noise model and assign new filenames for the results of the various montecarlo runs.
extern void UpdateNoise(struct noise *pn, struct mcresult *pmcr, char *tileName);

// Free a noise structre
extern void FreeNoise(struct noise *pn);

/* 
	Print the values of the noise parameters, that correspond to the current simulation when the function is called.
	"Current" noise parameters are in (pn->params)[pn->current]
*/
extern void PrintNoise(struct noise *pn);

#endif /* NOISE_H */
