//
// Created by jefferson on 3/09/16.
//

#ifndef HOLA_HIPERCUBE_H
#define HOLA_HIPERCUBE_H

#include <random>
#include "Space.h"
#include "UniformRandomCPU.h"

class Hipercube : public Space<double*> {
public:
    Hipercube(double lower, double upper, size_t dimension);

    #pragma acc routine seq
    double* repair(double* val);
    double* getRandomIndividual();

    #pragma acc routine seq
    size_t getDimension();
    ~Hipercube();
private:
    std::random_device rd;
    std::mt19937 eng;
    UniformRandomCPU ur;
    double *min, *max;
    size_t dimension;
    std::vector<double*> pointers;
};


#endif //HOLA_HIPERCUBE_H
