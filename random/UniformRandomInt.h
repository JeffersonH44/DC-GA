//
// Created by jefferson on 6/09/16.
//

#ifndef HOLA_UNIFORMRANDOMINT_H
#define HOLA_UNIFORMRANDOMINT_H


#include "BaseRandom.h"
#include <random>

class UniformRandomInt : public BaseRandom<std::mt19937, std::uniform_int_distribution<>> {
public:
    UniformRandomInt(std::mt19937 &eng, int a, int b);
};


#endif //HOLA_UNIFORMRANDOMINT_H
