//
// Created by jefferson on 22/11/16.
//
#include "Random.h"
#include "Hipercube.h"
#include "Rastrigin.h"

#include <limits>
#include <iostream>

using namespace std;

int main() {
    int dimension = 1000, inds = 1;
    double low = -5.12, high = 5.12;
    double **individuals = hipercube::getRandomIndividuals(inds, dimension, -100, 100);

    // random related stuff
    int size = 200000;
    int current = 0;
    double *randoms = new double[size];
    rd::init(randoms, size);
    double fitness;

    #pragma acc data copy(individuals[0:inds][0:dimension]) present(randoms)
    {
        #pragma acc parallel loop
        for(int i = 0; i < dimension; ++i) {
            hipercube::repair(individuals[0], low, high, dimension);
        }
        fitness = rastrigin::apply(individuals[0], dimension);
    }

    for(int i = 0; i < dimension; ++i) {
        cout << individuals[0][i] << endl;
    }
    cout << fitness << endl;
    return 0;
}
