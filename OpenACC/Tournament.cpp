//
// Created by jefferson on 15/09/16.
//

#include <thrust/system/cuda/detail/bulk.h>
#include "Rastrigin.h"
#include "Tournament.h"

Tournament::Tournament(OptimizationFunction<double*> &function, int n, size_t dimension, size_t populationSize) :
    eng(rd()),
    randomIndex(eng, 0, static_cast<int>(populationSize) - 1),
    func(dimension)
{
    this->function = &function;
    this->n = n;
    this->dimension = dimension;
}

/*Tournament::Tournament(Tournament tournament, size_t populationSize) :
    Tournament(tournament.function, tournament.n, tournament.dimension, populationSize)
{
}*/


size_t Tournament::chooseOne(double **population) {
    // TODO: machete
    double fitness = std::numeric_limits<double>::max();
    size_t bestIndex = 0;
    for(int i = 0; i < n; ++i) {
        int currIndex = randomIndex.generate();
        double currentFitness = this->func.apply(population[currIndex]);
        if(currentFitness < fitness) {
            fitness = currentFitness;
            bestIndex = currIndex;
        }
    }

    return bestIndex;
}
