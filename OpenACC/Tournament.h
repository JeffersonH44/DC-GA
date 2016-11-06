//
// Created by jefferson on 15/09/16.
//

#ifndef HOLA_TOURNAMENT_H
#define HOLA_TOURNAMENT_H


#include <random>
#include "Selection.h"
#include "UniformRandomIntCPU.h"

class Tournament : public Selection<double*>{
public:
    Tournament(OptimizationFunction<double*> &function, int n, size_t dimension, size_t populationSize);
    Tournament(Tournament tournament, size_t populationSize);
    size_t chooseOne(double **population);

private:
    std::random_device rd;
    std::mt19937 eng;
    UniformRandomIntCPU randomIndex;
    int n;
    size_t dimension;
};


#endif //HOLA_TOURNAMENT_H
