//
// Created by jefferson on 22/11/16.
//

#ifndef DC_GA_RANDOM_H
#define DC_GA_RANDOM_H

#include <random>
#include <cstdlib>
#include <cmath>

namespace rd {
    void init(double *randoms, int size);

    #pragma acc routine seq
    double generateRandom(double *randoms, int size, int &current);

    #pragma acc routine seq
    double random(double fMin, double fMax, double *randoms, int size, int &current);

    #pragma acc routine seq
    int randomInt(int min, int max, double *randoms, int size, int &current);

    #pragma acc routine seq
    double gaussianRandom(double mean, double std, double *randoms, int size, int &current);

    double randomCPU(double min, double max);
}

#endif //DC_GA_RANDOM_H
