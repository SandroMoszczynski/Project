/*
The MIT License (MIT)

Copyright (c) <2016> <Nicolas Delfosse, Pavithran Iyer>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/



#ifndef ARRAYS_H
#define ARRAYS_H

/*
	Given a pointer-to-pointer, return a pointer to a list of number that are formed by taking a particular (col-th) column of the input (jagged) array.
	The col input indicates the column index which must be fetched from each row. This must be given keeping in mind any segmentation faults coming from accessing an unallocated memory location.
*/
extern double* Slice(double **arr, int rows, int col);

// Copy the contents of an array into another
extern void Copy(int* original, int nelems, int *duplicate);

// Determine if a given element esists in an integer array. Return 1 if yes and 0 otherwise.
extern int Element(int elem, int *arr, int size);

// Given a range, compute all the numbers in that range.
extern void Expand(double *range, double *expanded);

// Fill an integer array with constants
extern void FillIntArrayWithConstants(int* arr, int arrSize, int constant);

// Fill a long array with constants
extern void FillLongArrayWithConstants(long* arr, int arrSize, long constant);

// Fill a float array with constants
extern void FillFloatArrayWithConstants(float* arr, int arrSize, float constant);

// Fill a double array with constants
extern void FillDoubleArrayWithConstants(double* arr, int arrSize, double constant);

// Print the contents of an inteeger array
extern void PrintIntArray(int* arr, int arrSize);

// Compute the number of subsets of a given size, in a superset of another given size.
extern long Combination(int total, int size);

// Convert an integer to binary
extern void IntToBinary(int deci, int nbits, int *bseq);

// Compute the sum of elements in an integer array
extern int Sum(int *arr, int nelems);

// Find the product of all the elements in an integer array
extern double Prod(double *arr, int nelems);

// Compute the number of subsets of a given size, in a superset of another given size.
extern long Combination(int total, int size);

/* 
	Generate all possible collection of a set, all of which have a given number of elements.
	Every subset corresponds to a number from 0 to 2^(size of the superset)

*/
extern void GenSubsets(int *superset, int length, int **collection);

/*
	Compute the cartesian product of a list of list of numbers
	
	The input must be formatted as follows.
		arr[0][0] = number of lists described in arr
		arr[j][0] = (for j > 0) number of elements in the j-th list
		arr[j][1..] = elements of the set j.

	Output: A such that
		A[0][0] contains the number of multiples in the cartesian product
		A[0][1] contains the number of elements in each multiple of the cartesian product (equal to the number of lists in the input)
		A[j] contains the j-th element of the cartesian product.	

	Algorithm:
		Let there be M sets, arr[j][0] = aj and N = a1 * a2 ... aM.
		Every element of the cartesian product can be associated to a number between 1 and total number of elements in the cartesian product, in the following way.
			1. Take a number X between 0 and N. We will derive an element of the cartesian product, SX, from X.
			2. For k = 0 to M-1, do
				A. Divide X by ak, the remainder is the k-th element of SX.
				B. X -> X/ak
*/
extern void CartesianProduct(double **arr, double **cartProd);

#endif /* ARRAYS_H */
