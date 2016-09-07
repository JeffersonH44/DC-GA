//
// Created by jefferson on 3/09/16.
//

#include <cstddef>
#include "Hipercube.h"


Hipercube::Hipercube(double min, double max, size_t dimension) :
eng(rd()),
ur(eng, min, max),
min(dimension, min),
max(dimension, max)
{
}

std::vector<double> Hipercube::repair(std::vector<double> val) {
    std::vector<double> ret(val);

    for(size_t i = 0; i < ret.size(); ++i) {
        if(ret[i] < this->min[i]) {
            ret[i] = this->min[i];
        } else if(ret[i] > this->max[i]) {
            ret[i] = this->max[i];
        }
    }

    return ret;
}

std::vector<double> Hipercube::getRandomIndividual() {
    size_t dimensions = min.size();
    std::vector individual(dimensions, 0.0);
    for(size_t i = 0 ; i < dimensions; ++i) {
        individual[i] = ur.generate();
    }
    return individual;
}


