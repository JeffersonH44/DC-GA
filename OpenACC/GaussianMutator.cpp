//
// Created by jefferson on 3/09/16.
//

#include "GaussianMutator.h"
#include "GaussianRandom.h"

GaussianMutator::GaussianMutator(double mean, double std, double prob, size_t dimension) :
    eng(rd()),
    ur(eng, 0.0, 1.0),
    gr(eng, mean, std)
{
    this->prob = prob;
    this->arguments = 1;
    this->dimension = dimension;
}

double** GaussianMutator::apply(double **individuals) {
    double *ind = individuals[0];
    double *newInd = new double[this->dimension];
    std::copy(ind, ind + this->dimension, newInd);
    //std::vector<double> newInd(ind);
    double rand;
    for(size_t i = 0; i < this->dimension; ++i) {
        rand = ur.generate();
        if(rand < this->prob) {
            newInd[i] = ind[i] + gr.generate();
        }
    }

    double **toReturn = new double*[1];
    toReturn[0] = newInd;

    return toReturn;
}
