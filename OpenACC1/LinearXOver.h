//
// Created by jefferson on 29/11/16.
//

#ifndef DC_GA_LINEARXOVER_H
#define DC_GA_LINEARXOVER_H

#include "Random.h"

namespace linearxover {
    #pragma acc routine vector
    double** apply(double **individuals, double **toReturn, int dimension, double *randoms, int size, int &current);
}


#endif //DC_GA_LINEARXOVER_H
