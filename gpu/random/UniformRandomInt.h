//
// Created by jefferson on 21/09/16.
//

#ifndef GPU_HOLA_UNIFORMRANDOMINT_H
#define GPU_HOLA_UNIFORMRANDOMINT_H

#include <thrust/random.h>
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/iterator/counting_iterator.h>
#include "BaseRandom.h"

namespace gpu {
    struct prg_int
    {
        thrust::uniform_int_distribution<int> dist;
        unsigned int seed;

        __host__ __device__
        prg_int(unsigned int seed, int _a=0, int _b=1) :
                dist(_a, _b),
                seed(seed)
        {};

        __host__ __device__
        double operator()(const unsigned int n)
        {
            thrust::default_random_engine rng(seed);
            rng.discard(n);
            return dist(rng);
        }
    };

    class UniformRandomInt : public BaseRandom {
    public:
        UniformRandomInt(int a, int b);
        thrust::device_vector<double> generate(int n);

    private:
        int a, b;
    };
}


#endif //HOLA_UNIFORMRANDOMINT_H
