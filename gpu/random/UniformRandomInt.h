//
// Created by jefferson on 21/09/16.
//

#ifndef HOLA_UNIFORMRANDOMINT_H
#define HOLA_UNIFORMRANDOMINT_H

#include <thrust/random.h>
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/iterator/counting_iterator.h>
#include "BaseRandom.h"

struct prg_int
{
    int a, b;

    __host__ __device__
    prg_int(int _a=0, int _b=1) : a(_a), b(_b) {};

    __host__ __device__
    double operator()(const unsigned int n) const
    {
        thrust::default_random_engine rng;
        thrust::uniform_int_distribution<int> dist(a, b);
        rng.discard(n);

        return dist(rng);
    }
};

class UniformRandomInt : public BaseRandom {
public:
    UniformRandomInt(int a, int b);
    thrust::device_vector<double> generate(int n);

private:
    prg_int rand;
};

#endif //HOLA_UNIFORMRANDOMINT_H
