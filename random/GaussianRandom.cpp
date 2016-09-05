//
// Created by jefferson on 3/09/16.
//

#include "GaussianRandom.h"

GaussianRandom::GaussianRandom(std::mt19937 &eng, double mean, double std) :
BaseRandom(eng, std::normal_distribution<>(mean, std))
{
}
