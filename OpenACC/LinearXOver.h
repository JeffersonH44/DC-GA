//
// Created by jefferson on 5/09/16.
//

#ifndef HOLA_LINEARXOVER_H
#define HOLA_LINEARXOVER_H


#include <random>
#include "Operator.h"
#include "UniformRandomCPU.h"

class LinearXOver : public Operator<double*> {
public:
    LinearXOver(size_t dimension);
    double** apply(double **individuals);
private:
    std::random_device rd;
    std::mt19937 eng;
    UniformRandomCPU ur;
    size_t dimension;
};


#endif //HOLA_LINEARXOVER_H
