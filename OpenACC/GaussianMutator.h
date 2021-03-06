//
// Created by jefferson on 3/09/16.
//

#ifndef HOLA_GAUSSIANMUTATOR_H
#define HOLA_GAUSSIANMUTATOR_H

#include <vector>

#include "Operator.h"
#include "GaussianRandom.h"
#include "UniformRandomCPU.h"


class GaussianMutator : public Operator<double*> {
public:
    GaussianMutator(double mean, double std, double prob, size_t dimension);

    #pragma acc routine seq
    double** apply(double **individuals, double **toReturn);
private:
    void copy(double *from, double *to);
    double prob;
    size_t dimension;
    std::random_device rd;
    std::mt19937 eng;
    UniformRandomCPU ur;
    GaussianRandom gr;
};


#endif //HOLA_GAUSSIANMUTATOR_H
