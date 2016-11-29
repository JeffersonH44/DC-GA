//
// Created by jefferson on 22/11/16.
//

#include "Random.h"

void rd::init(double *randoms, int size) {
    for(int i = 0 ; i < size; ++i) {
        randoms[i] = rand();
    }
    #pragma acc enter data copyin(randoms[0:size])
}

double rd::generateRandom(double *randoms, int size, int &current) {

    current = (current + 1) % size;
    return randoms[current];
}

double rd::random(double fMin, double fMax, double *randoms, int size, int &current) {
    double f = (double)generateRandom(randoms, size, current) / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

double rd::gaussianRandom(double mean, double std, double *randoms, int size, int &current) {
    double u = ((double) generateRandom(randoms, size, current) / (RAND_MAX)) * 2 - 1;
    double v = ((double) generateRandom(randoms, size, current) / (RAND_MAX)) * 2 - 1;
    double r = u * u + v * v;
    if (r == 0 || r > 1) return gaussianRandom(mean, std, randoms, size, current);
    double c = sqrt(-2 * log(r) / r);
    return ((u * c) * std) + mean;
}

double rd::randomCPU(double min, double max) {
    double f = (double)rand() / RAND_MAX;
    return min + f * (max - min);
}

int rd::randomInt(int min, int max, double *randoms, int size, int &current) {
    return min + ((int) generateRandom(randoms, size, current) % (max - min + 1));
}
