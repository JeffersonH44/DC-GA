//
// Created by jefferson on 3/09/16.
//

#ifndef HOLA_GAUSSIANRANDOM_H
#define HOLA_GAUSSIANRANDOM_H

#include <random>
#include "BaseRandom.h"

class GaussianRandom : public BaseRandom<std::mt19937, std::normal_distribution<>> {
public:
    GaussianRandom(std::mt19937 &eng, double mean, double std);
};


#endif //HOLA_GAUSSIANRANDOM_H
