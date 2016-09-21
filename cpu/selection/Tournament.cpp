//
// Created by jefferson on 15/09/16.
//

#include "Tournament.h"
#include "../random/UniformRandomInt.h"

Tournament::Tournament(OptimizationFunction<std::vector<double> > &function, int n) :
    eng(rd())
{
    this->function = &function;
    this->n = n;
}

size_t Tournament::chooseOne(std::vector<std::vector<double>> population) {
    UniformRandomInt index(this->eng, 0, static_cast<int>(population.size()) - 1);

    double fitness = std::numeric_limits<double>::max();
    size_t bestIndex = 0;
    for(int i = 0; i < n; ++i) {
        size_t currIndex = static_cast<size_t>(index.generate());
        double currentFitness = function->apply(population[currIndex]);
        if(currentFitness < fitness) {
            fitness = currentFitness;
            bestIndex = currIndex;
        }
    }

    return bestIndex;
}