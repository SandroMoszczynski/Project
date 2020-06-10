#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "string.h"
#include <time.h>
#include "rgens.h"

double Random(const char *distribution, double *specifications){
  // Sample according to a given distribution
  double urand = ((double)rand()/(double)RAND_MAX);
  double randnum = urand;
  if (strncmp(distribution, "uniform", 7) == 0)
    randnum = urand;
  else if (strncmp(distribution, "poisson", 7) == 0){
    double thresh = exp((-1) * specifications[0]), psv = 1;
    randnum = 0;
    do{
      randnum ++;
      urand = ((double)rand()/(double)RAND_MAX);
      psv *= urand;
    }while(psv > thresh);
    randnum --;
  }
  else if (strncmp(distribution, "exponential", 11) == 0)
    randnum = (-1) * (log(1 - urand)) * specifications[0];
  else if (strncmp(distribution, "normal", 6) == 0){
    double sum = 0, normrand, *urands = malloc(sizeof(double) * 2);
    do{
      urands[0] = ((double)rand()/(double)RAND_MAX);
      urands[1] = ((double)rand()/(double)RAND_MAX);
      sum = pow(urands[0], 2) + pow(urands[1], 2);
    }while (sum >= 1);
    normrand = urands[0] * sqrt((-2) * log(sum)/sum);
    randnum = normrand * specifications[1] + specifications[0];
    free(urands);
  }
  else
    fprintf(stderr, "\033[2mDistribution type '%s' is unknown. Assuming a uniform distrubution instead.\033[0m\n", distribution);
  return randnum;
}


void BinomialBitString(int *result, int nbits, int *frozen, double prob){
  // Produce a n-bit string where the value of each bit is sampled according to a binomial distribution with given parameters.
  int bi;
  // fprintf(stderr, "Random number: %g\n", Random("uniform", NULL));
  for (bi = 0; bi < nbits; bi ++)
    if (frozen[bi] == 0)
      if (Random("uniform", NULL) < prob)
        result[bi] = 1;
}
