#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "memory.h"
#include "arrays.h"

double* Slice(double **arr, int rows, int col){
	// Given a pointer-to-pointer, return a pointer to a list of number that are formed by taking a particular (col-th) column of the input (jagged) array.
	int ri;
	double *column = malloc(sizeof(double) * rows);
	for (ri = 0; ri < rows; ri ++)
		column[ri] = arr[ri][col];
	return column;
}

void Copy(int* original, int nelems, int *duplicate){
	// Copy the contents of an array into another
	int ei;
	for (ei = 0; ei < nelems; ei ++)
		duplicate[ei] = original[ei];
}


int Element(int elem, int *arr, int size){
	// Determine if a given element esists in an integer array. Return 1 if yes and 0 otherwise.
	int ei, exists = 0;
	for (ei = 0; ei < size; ei ++)
		if (arr[ei] == elem)
			exists = 1;
	return exists;
}


void Expand(double *range, double *expanded){
	// Given a range, compute all the numbers in that range.
	// There is a subtle issue with looping over floats, which is why the loop has to be over integers while to quantity of interest is obtained by scaling the loop variable appropriately.
	// See http://stackoverflow.com/questions/40134984/looping-over-a-range-of-floats-in-c
	long scale, ivar;
	scale = (int) pow(10, ceil(abs(log(range[2]))) + 1);
	int ri = 1;
	for (ivar = (long) (range[1] * scale); ivar >= (long) (range[0] * scale); ivar -= (long) (range[2] * scale))
		expanded[ri ++] = (double) (ivar/(double) scale);
}

void FillIntArrayWithConstants(int* arr, int arrSize, int constant){
	// Fill an integer array with constants
	int ai = 0;
	for(ai = 0; ai < arrSize; ai ++){
		arr[ai] = constant;
	}
}

void FillLongArrayWithConstants(long* arr, int arrSize, long constant){
	// Fill an integer array with constants
	int ai = 0;
	for(ai = 0; ai < arrSize; ai ++){
		arr[ai] = constant;
	}
}

void FillFloatArrayWithConstants(float* arr, int arrSize, float constant){
	// Fill an integer array with constants
	int ai = 0;
	for(ai = 0; ai < arrSize; ai ++){
		arr[ai] = constant;
	}
}

void FillDoubleArrayWithConstants(double* arr, int arrSize, double constant){
	// Fill an integer array with constants
	int ai = 0;
	for(ai = 0; ai < arrSize; ai ++){
		arr[ai] = constant;
	}
}

void PrintIntArray(int* arr, int arrSize){
	// Print the contents of an inteeger array
	int ai;
	for(ai = 0; ai < arrSize; ai ++)
		printf(" %d", arr[ai]);
	printf(".\n");
}

void IntToBinary(int deci, int nbits, int *bseq){
	// Convert an integer to binary
	int bi;
	for (bi = 0; bi < nbits; bi ++){
		bseq[nbits - bi - 1] = (deci % 2);
		deci = (int) (deci/2);
	}
}

int Sum(int *arr, int nelems){
	// Compute the sum of elements in an integer array
	int ei, sum = 0;
	for (ei = 0; ei < nelems; ei ++)
		sum += arr[ei];
	return sum;
}

double Prod(double *arr, int nelems){
	// Find the product of all the elements in an integer array
	int ei;
	double prod = 1;
	for (ei = 0 ; ei < nelems; ei ++)
		prod = prod * arr[ei];
	return prod;
}

long Combination(int total, int size){
	// Compute the number of subsets of a given size, in a superset of another given size.
	int ei;
	long nfact = 1, kfact = 1, diffFact = 1, nsubsets;
	// compute the binomial coefficient -- size of superset choose size of subset
	for (ei = 1; ei <= total; ei ++)
		nfact *= ei;
	for (ei = 1; ei <= size; ei ++)
		kfact *= ei;
	for (ei = 1; ei <= (total - size); ei ++)
		diffFact *= ei;
	nsubsets = (long) (nfact/(kfact * diffFact));
	return nsubsets;
}

void GenSubsets(int *superset, int length, int **collection){
	// Generate all possible collection of a set, all of which have a given number of elements.
	int ei, bi, idx;
	int *bseq = malloc(sizeof(int) * superset[0]);
	collection[0][0] = 1;
	collection[0][1] = length;
	for (bi = 0; bi < pow(2, superset[0]); bi ++){
		IntToBinary(bi, superset[0], bseq);
		if (Sum(bseq, superset[0]) == length){
			idx = 0;
			collection[collection[0][0]] = malloc(sizeof(int) * length);
			for (ei = 1; ei <= superset[0]; ei ++){
				if (bseq[ei - 1] == 1){
					collection[collection[0][0]][idx] = superset[ei];
					idx ++;
				}
			}
			collection[0][0] ++;
		}
	}
	collection[0][0] --;
	free(bseq);
}


void CartesianProduct(double **arr, double **cartProd){
	// Compute the cartersian product of a list of list of numbers.
	int si, id, prod = 1;
	cartProd[0][0] = Prod(Slice(arr + 1, (int) arr[0][0], 0), (int) arr[0][0]);
	cartProd[0][1] = arr[0][0];
	for (id = 0; id < cartProd[0][0]; id ++){
		prod = 1;
		for (si = 1; si <= arr[0][0]; si ++){
			cartProd[id + 1][si - 1] = arr[si][1 + ((id/prod) % (int) arr[si][0])];
			prod = prod * (int) arr[si][0];
		}
	}
}
