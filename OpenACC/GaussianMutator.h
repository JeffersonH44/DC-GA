//
// Created by jefferson on 21/09/16.
//

#ifndef HOLA_GAUSSIANMUTATOR_H
#define HOLA_GAUSSIANMUTATOR_H


#include "Operator.h"
#include "GaussianRandom.h"
#include "UniformRandom.h"

struct allow_mut {
    const double prob;

    allow_mut(double prob) : prob(prob) {}

    __host__ __device__
    double operator()(const double& x, const double& y) {
        return x < prob ? y : 0.0;
    }
};

class GaussianMutator : public Operator<thrust::device_vector<double>> {
public:
    GaussianMutator(double mean, double std, double prob);
    std::vector<thrust::device_vector<double>> apply(std::vector<thrust::device_vector<double>> &individuals);
private:
    double prob;
    UniformRandom ur;
    GaussianRandom gr;
};


#endif //HOLA_GAUSSIANMUTATOR_H
