//
// Created by jefferson on 3/09/16.
//

#ifndef HOLA_GAUSSIANMUTATOR_H
#define HOLA_GAUSSIANMUTATOR_H

#include <vector>

#include "../Operator.h"
#include "../../random/GaussianRandom.h"
#include "../../random/UniformRandomCPU.h"


class GaussianMutator : public Operator<std::vector<double>> {
public:
    GaussianMutator(double mean, double std, double prob);
    std::vector<std::vector<double>> apply(std::vector<std::vector<double>> individuals);
private:
    double prob;
    std::random_device rd;
    std::mt19937 eng;
    UniformRandomCPU ur;
    GaussianRandom gr;
};


#endif //HOLA_GAUSSIANMUTATOR_H
