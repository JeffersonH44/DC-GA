//
// Created by jefferson on 29/11/16.
//

#include "GaussianMutator.h"

double** gaussianmutator::apply(double **individuals, double **toReturn, int dimension, double prob,
                                double mean, double std,
                                double *randoms, int size, int &current) {
    double *ind = individuals[0];
    double rand;
    #pragma acc loop vector
    for(int i = 0; i < dimension; ++i) {
        rand = rd::random(0.0, 1.0, randoms, size, current);
        toReturn[0][i] = rand < prob ?
                         ind[i] + rd::gaussianRandom(mean, std, randoms, size, current) :
                         ind[i];
    }

    return toReturn;
}