//
// Created by jefferson on 29/11/16.
//

#ifndef DC_GA_GAUSSIANMUTATOR_H
#define DC_GA_GAUSSIANMUTATOR_H

#include "Random.h"

namespace gaussianmutator {
    #pragma acc routine vector
    double** apply(double **individuals, double **toReturn, int dimension, double prob,
                   double mean, double std,
                   double *randoms, int size, int &current);
}


#endif //DC_GA_GAUSSIANMUTATOR_H
