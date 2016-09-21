//
// Created by jefferson on 21/09/16.
//

#ifndef HOLA_UNIFORMRANDOM_H
#define HOLA_UNIFORMRANDOM_H

#define CUDA_CALL(x) do { if((x)!=cudaSuccess) { \
    printf("Error at %s:%d\n",__FILE__,__LINE__);\
    return EXIT_FAILURE;}} while(0)
#define CURAND_CALL(x) do { if((x)!=CURAND_STATUS_SUCCESS) { \
    printf("Error at %s:%d\n",__FILE__,__LINE__);\
    return EXIT_FAILURE;}} while(0)

#include <thrust/random.h>
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/iterator/counting_iterator.h>

#include "BaseRandom.h"

struct prg_real
{
    double a, b;

    __host__ __device__
    prg_real(double _a=0.0, double _b=1.0) : a(_a), b(_b) {};

    __host__ __device__
    double operator()(const unsigned int n) const
    {
        thrust::default_random_engine rng;
        thrust::uniform_real_distribution<double> dist(a, b);
        rng.discard(n);

        return dist(rng);
    }
};

class UniformRandom : public BaseRandom {
public:
    UniformRandom(double a, double b);
    thrust::device_vector<double> generate(int n);

private:
    prg_real rand;
};


#endif //HOLA_UNIFORMRANDOM_H