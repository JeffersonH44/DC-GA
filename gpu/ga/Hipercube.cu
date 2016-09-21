//
// Created by jefferson on 21/09/16.
//

#include "Hipercube.h"

Hipercube::Hipercube(double min, double max, int dimension) :
        ur(min, max),
        min(min),
        max(max),
        dimension(dimension)
{
}

thrust::device_vector<double> Hipercube::repair(thrust::device_vector<double> val){
    thrust::device_vector<double> ret(val.size());

    thrust::transform(ret.begin(), ret.end(), ret.begin(), rep(min, max));
    return ret;
}

thrust::device_vector<double> Hipercube::getRandomIndividual() {
    return ur.generate(this->dimension);
}