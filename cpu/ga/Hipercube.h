//
// Created by jefferson on 3/09/16.
//

#ifndef HOLA_HIPERCUBE_H
#define HOLA_HIPERCUBE_H

#include <random>
#include "Space.h"
#include "../random/UniformRandomCPU.h"

class Hipercube : public Space<std::vector<double>> {
public:
    Hipercube(double min, double max, size_t dimension);
    std::vector<double> repair(std::vector<double> val);
    std::vector<double> getRandomIndividual();
private:
    std::random_device rd;
    std::mt19937 eng;
    UniformRandomCPU ur;
    std::vector<double> min, max;
};


#endif //HOLA_HIPERCUBE_H
