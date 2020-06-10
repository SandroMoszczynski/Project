/*
The MIT License (MIT)

Copyright (c) <2016> <Nicolas Delfosse, Pavithran Iyer>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/



#ifndef RGENS_H
#define RGENS_H

/*
  Generate a radom number according to a given distribution
  Inputs:
          distribution: char*
          specifications: double array (size of the array depens on the "distribution")

              distribution                specification                                       algorithm
          1.    "uniform"                 "NULL"                                              Built-in "double rand(..)" function.
          2.    "poisson"                 double array of size 1: [mean]                      https://en.wikipedia.org/wiki/Poisson_distribution#Generating_Poisson-distributed_random_variables
          3.    "exponential"             double array of size 1: [mean]                      Inverse sampling transform. CDF of the exponential distributio is F(v) = 1 - exp( - 1/avg * v). So, output x = - log(1 - u) * avg, where u is a uniform random variate.
          4.    "normal"                  double array of size 2: [mean, variance]            https://en.wikipedia.org/wiki/Marsaglia_polar_method
  Output:
          (double) real number
*/
extern double Random(const char *distribution, double *specifications);

/*
  Produce a n-bit string where the value of each bit is sampled according to a binomial distribution with given parameters.
  For each bit:
  1. Pick a real number in the range [0,1] according to the unform distribution
  2. If the number is less than prob, the bit value is 1
  3. Otherwise, the bit value is 0.
*/
extern void BinomialBitString(int *result, int nbits, int *frozen, double prob);

#endif /* RGENS_H */
