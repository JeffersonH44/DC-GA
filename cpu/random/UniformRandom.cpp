//
// Created by jefferson on 5/09/16.
//

#include "UniformRandom.h"

UniformRandom::UniformRandom(std::mt19937 &eng, double a, double b) :
BaseRandom(eng, std::uniform_real_distribution<>(a, b))
{
}
