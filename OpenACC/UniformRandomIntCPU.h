//
// Created by jefferson on 6/09/16.
//

#ifndef HOLA_UNIFORMRANDOMINT_H
#define HOLA_UNIFORMRANDOMINT_H


#include "BaseRandomCPU.h"
#include <random>

class UniformRandomIntCPU : public BaseRandom<std::mt19937, std::uniform_int_distribution<>> {
public:
    UniformRandomIntCPU(std::mt19937 &eng, int a, int b);
};




#endif //HOLA_UNIFORMRANDOMINT_H
