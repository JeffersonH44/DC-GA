//
// Created by jefferson on 5/09/16.
//

#include "UniformRandomCPU.h"

UniformRandomCPU::UniformRandomCPU(std::mt19937 &eng, double a, double b) :
        BaseRandomCPU(eng, std::uniform_real_distribution<>(a, b))
{
}
