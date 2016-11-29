//
// Created by jefferson on 22/11/16.
//

#include <limits>
#include <iostream>

#include "Tournament.h"
#include "Rastrigin.h"
#include "GaussianMutator.h"
#include "Hipercube.h"

using namespace std;

int main() {
    int dimension = 1000, inds = 1000;
    double low = -5.12, high = 5.12;
    double **individuals = hipercube::getRandomIndividuals(inds, dimension, -100, 100);
    double **operatorResult = hipercube::getRandomIndividuals(2, dimension, -1, 1);

    // gaussian random parameters
    double mean = 0.0, std = 0.1;

    // random related stuff
    int size = 4000000;
    int current = 0;
    double *randoms = new double[size];
    rd::init(randoms, size);
    double fitness;

    // tournament related stuff
    int bestIndex, n = 4;

    #pragma acc data copy(individuals[0:inds][0:dimension], operatorResult[0:2][0:dimension]) present(randoms)
    {
        bestIndex = Tournament::chooseOne(n, individuals, inds, dimension, randoms, size, current);
        operatorResult = gaussianmutator::apply(individuals, operatorResult, dimension, 0.1,
                                                mean, std,
                                                randoms, size, current);
        #pragma acc parallel loop
        for(int i = 0; i < dimension; ++i) {
            hipercube::repair(individuals[0], low, high, dimension);
        }
        fitness = rastrigin::apply(individuals[0], dimension);
    }

    for(int i = 0; i < dimension; ++i) {
        cout << individuals[0][i] << " " << operatorResult[0][i] << endl;
    }
    cout << fitness << endl;
    cout << bestIndex << endl;
    return 0;
}
