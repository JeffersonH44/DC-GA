//
// Created by jefferson on 21/09/16.
//

#ifndef HOLA_HIPERCUBE_H
#define HOLA_HIPERCUBE_H


#include <random>
#include "Space.h"
#include "UniformRandom.h"

struct rep
{
    double max, min;

    __host__ __device__
    rep(double min, double max) :
            min(min),
            max(max)
    {
    };

    __host__ __device__
    double operator()(const double n)
    {
        if(n > max) {
            return max;
        } else if(n < min) {
            return min;
        }

        return n;
    }
};

class Hipercube : public Space<thrust::device_vector<double>> {
public:
    Hipercube(double min, double max, int dimension);
    thrust::device_vector<double> repair(thrust::device_vector<double> val);
    thrust::device_vector<double> getRandomIndividual();
private:
    UniformRandom ur;
    double min, max;
    int dimension;
};


#endif //HOLA_HIPERCUBE_H
