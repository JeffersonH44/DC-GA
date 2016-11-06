//
// Created by jefferson on 4/09/16.
//

#ifndef HOLA_BASERANDOM_H
#define HOLA_BASERANDOM_H

#include <random>
#include <iostream>


template <class RandomGenerator, class Distribution>
class BaseRandom {
public:
    BaseRandom(RandomGenerator &randomGenerator, Distribution distribution);
    #pragma acc routine seq
    double generate();
protected:
    Distribution distribution;
    RandomGenerator randomGenerator;
};


template <class RandomGenerator, class Distribution>
BaseRandom<RandomGenerator,Distribution>::BaseRandom(RandomGenerator &randomGenerator, Distribution distribution) :
        distribution(distribution){
    this->randomGenerator = randomGenerator;
}

template <class RandomGenerator, class Distribution>
double BaseRandom<RandomGenerator,Distribution>::generate() {
    double num = distribution(this->randomGenerator);
    return num;
}

#endif //HOLA_BASERANDOM_H
