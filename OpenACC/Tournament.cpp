//
// Created by jefferson on 15/09/16.
//

#include <thrust/system/cuda/detail/bulk.h>
#include "Tournament.h"

Tournament::Tournament(OptimizationFunction<double*> &function, int n, size_t dimension, size_t populationSize) :
    eng(rd()),
    randomIndex(eng, 0, static_cast<int>(populationSize) - 1)
{
    this->function = &function;
    this->n = n;
    this->dimension = dimension;
}

size_t Tournament::chooseOne(double **population) {
    double fitness = std::numeric_limits<double>::max();
    size_t bestIndex = 0;
    for(int i = 0; i < n; ++i) {
        int currIndex = randomIndex.generate();
        std::cout << currIndex << " ";
        double currentFitness = function->apply(population[currIndex]);
        if(currentFitness < fitness) {
            fitness = currentFitness;
            bestIndex = currIndex;
        }
    }
    std::cout << std::endl;

    return bestIndex;
}
