//
// Created by jefferson on 6/09/16.
//

#include "UniformRandomIntCPU.h"

UniformRandomIntCPU::UniformRandomIntCPU(std::mt19937 &eng, int a, int b) :
        BaseRandom(eng, std::uniform_int_distribution<>(a, b), 1000000)
{ }
