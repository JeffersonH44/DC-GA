//
// Created by jefferson on 6/09/16.
//

#include "UniformRandomInt.h"

UniformRandomInt::UniformRandomInt(std::mt19937 &eng, int a, int b) :
BaseRandom(eng, std::uniform_int_distribution<>(a, b))
{ }
