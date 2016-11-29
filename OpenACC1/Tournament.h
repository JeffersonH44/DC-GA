//
// Created by jefferson on 29/11/16.
//

#ifndef DC_GA_TOURNAMENT_H
#define DC_GA_TOURNAMENT_H

#include <limits>

#include "Random.h"
#include "Rastrigin.h"

namespace Tournament {
    #pragma acc routine vector
    int chooseOne(int n, double **population, int populationSize, int dimension,
              double *randoms, int size, int &current);
}


#endif //DC_GA_TOURNAMENT_H
