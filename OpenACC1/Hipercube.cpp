//
// Created by jefferson on 29/11/16.
//

#include "Hipercube.h"
#include "Random.h"

double** hipercube::getRandomIndividuals(int individuals, int dimension, double low, double high) {
    double **inds = new double*[individuals];
    for(int i = 0; i < individuals; ++i) {
        inds[i] = new double[dimension];
        for(int j = 0; j < dimension; ++j) {
            inds[i][j] = rd::randomCPU(low, high);
        }
    }
    return inds;
}

double* hipercube::repair(double *val, double low, double high, int dimension) {
    double *ret = val;

    #pragma acc loop vector
    for(size_t i = 0; i < dimension; ++i) {
        if(ret[i] < low) {
            ret[i] = low;
        } else if(ret[i] > high) {
            ret[i] = high;
        }
    }

    return ret;
}
