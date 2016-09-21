//
// Created by jefferson on 21/09/16.
//

#ifndef HOLA_GAUSSIANRANDOM_H
#define HOLA_GAUSSIANRANDOM_H

#include <thrust/random.h>
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/iterator/counting_iterator.h>
#include <random>
#include "BaseRandom.h"

struct prg_gaussian
{
    thrust::normal_distribution<double> dist;
    unsigned int seed;

    __host__ __device__
    prg_gaussian(unsigned int seed, double _mean=0.0, double _std=1.0) :
        dist(_mean, _std),
        seed(seed)
    {
    };

    __host__ __device__
    double operator()(const unsigned int n)
    {
        thrust::default_random_engine rng(seed);
        rng.discard(n);
        return dist(rng);
    }
};

class GaussianRandom : public BaseRandom {
public:
    GaussianRandom(double mean, double std);
    thrust::device_vector<double> generate(int n);

private:
    double mean, std;
};


#endif //HOLA_GAUSSIANRANDOM_H
