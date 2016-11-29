//
// Created by jefferson on 29/11/16.
//

#include "Tournament.h"

int Tournament::chooseOne(int n, double **population, int populationSize, int dimension,
                          double *randoms, int size, int &current) {
    double fitness = std::numeric_limits<double>::max();
    int bestIndex = 0;
    for(int i = 0; i < n; ++i) {
        int currentIndex = rd::randomInt(0, populationSize - 1, randoms, size, current);
        double currentFitness = rastrigin::apply(population[currentIndex], dimension);
        if(currentFitness < fitness) {
            fitness = currentFitness;
            bestIndex = currentIndex;
        }
    }

    return bestIndex;
}
