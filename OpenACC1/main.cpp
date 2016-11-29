//
// Created by jefferson on 22/11/16.
//
#include "Random.h"

using namespace std;

#include <random>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <iostream>

namespace rd {
    void init(double *randoms, int size) {
        for(int i = 0 ; i < size; ++i) {
            randoms[i] = rand();
        }
        #pragma acc enter data copyin(randoms[0:size])
    }

    #pragma acc routine seq
    double generateRandom(double *randoms, int size, int &current) {

        current = (current + 1) % size;
        return randoms[current];
    }

    #pragma acc routine seq
    double random(double fMin, double fMax, double *randoms, int size, int &current) {
        double f = (double)generateRandom(randoms, size, current) / RAND_MAX;
        return fMin + f * (fMax - fMin);
    }

    double gaussianRandom(double mean, double std, double *randoms, int size, int &current) {
        double u = ((double) generateRandom(randoms, size, current) / (RAND_MAX)) * 2 - 1;
        double v = ((double) generateRandom(randoms, size, current) / (RAND_MAX)) * 2 - 1;
        double r = u * u + v * v;
        if (r == 0 || r > 1) return gaussianRandom(mean, std, randoms, size, current);
        double c = sqrt(-2 * log(r) / r);
        return ((u * c) * std) + mean;
    }
}

int main() {
    double *arr = new double[1000];

    // random related stuff
    int size = 200000;
    int current = 0;
    double *randoms = new double[size];
    rd::init(randoms, size);

    #pragma acc data copy(arr[0:1000]) present(randoms)
    {
        #pragma acc parallel loop
        for(int i = 0; i < 1000; ++i) {
            arr[i] = rd::gaussianRandom(10, 3, randoms, size, current);
            arr[i] = i % 2 ? rd::gaussianRandom(10, 3, randoms, size, current) : arr[i];
        }
    }
    for(int i = 0; i < 1000; ++i) {
        std::cout << arr[i] << std::endl;
    }
    return 0;
}
