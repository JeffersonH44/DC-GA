//
// Created by jefferson on 5/09/16.
//

#ifndef HOLA_UNIFORMRANDOM_H
#define HOLA_UNIFORMRANDOM_H


#include "BaseRandomCPU.h"


class UniformRandomCPU : public BaseRandom<std::mt19937, std::uniform_real_distribution<>> {
public:
    UniformRandomCPU(std::mt19937 &eng, double a, double b);
};



#endif //HOLA_UNIFORMRANDOM_H
