//
// Created by jefferson on 3/09/16.
//

#include "GaussianMutator.h"
#include "GaussianRandom.h"
#include <iostream>

GaussianMutator::GaussianMutator(double mean, double std, double prob, size_t dimension) :
    eng(rd()),
    ur(eng, 0.0, 1.0),
    gr(eng, mean, std)
{
    this->prob = prob;
    this->arguments = 1;
    this->dimension = dimension;
}

void GaussianMutator::copy(double *from, double *to) {
    size_t dim = this->dimension;
    for(int i = 0; i < dim; ++i) {
        to[i] = from[i];
    }
}

double** GaussianMutator::apply(double **individuals, double **toReturn) {
    double *ind = individuals[0];
    //double *newInd = new double[this->dimension];
    this->copy(ind, toReturn[0]);
    //std::vector<double> newInd(ind);
    double rand;
    #pragma acc loop vector
    for(size_t i = 0; i < this->dimension; ++i) {
        rand = ur.generate();
        if(rand < this->prob) {
            toReturn[0][i] = ind[i] + gr.generate();
        }
    }

    //double **toReturn = new double*[1];
    //toReturn[0] = newInd;

    return toReturn;
}
