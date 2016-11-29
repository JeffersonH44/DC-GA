//
// Created by jefferson on 29/11/16.
//

#include "Rastrigin.h"

#include <cstddef>
#include <limits>

double rastrigin::apply(double *ind, int dimension) {
    double fitness = 0.0;

    #pragma acc loop vector
    for(int i = 0; i < dimension; ++i) {
        fitness += apply(ind[i]);
    }

    return 10.0 * dimension + fitness;
}

double rastrigin::apply(double val) {
    return val * val - 10.0 * cos(6.283185307179586 * val);
}
