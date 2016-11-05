//
// Created by jefferson on 3/09/16.
//

#include <cstddef>
#include "Hipercube.h"


Hipercube::Hipercube(double lower, double upper, size_t dimension) :
eng(rd()),
ur(eng, lower, upper)
{
    this->min = new double[dimension];
    this->max = new double[dimension];
    std::fill(this->min, this->min + dimension, lower);
    std::fill(this->max, this->max + dimension, upper);
    this->dimension = dimension;
}

double* Hipercube::repair(double* val) {
    double *ret = new double[this->dimension];
    std::copy(val, val + this->dimension, ret);

    for(size_t i = 0; i < this->dimension; ++i) {
        if(ret[i] < this->min[i]) {
            ret[i] = this->min[i];
        } else if(ret[i] > this->max[i]) {
            ret[i] = this->max[i];
        }
    }

    return ret;
}

size_t Hipercube::getDimension() {
    return this->dimension;
}

double* Hipercube::getRandomIndividual() {
    size_t dimensions = this->dimension;
    double* individual = new double[dimensions];
    for(size_t i = 0 ; i < dimensions; ++i) {
        individual[i] = ur.generate();
    }
    return individual;
}

Hipercube::~Hipercube() {
    delete(min);
    delete(max);
}


