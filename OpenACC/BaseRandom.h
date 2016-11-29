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
    BaseRandom(RandomGenerator &randomGenerator, Distribution distribution, int cycle);
    #pragma acc routine seq
    double generate();
protected:
    Distribution distribution;
    RandomGenerator randomGenerator;
    double *generated;
    int i;
    int cycle;
};


template <class RandomGenerator, class Distribution>
BaseRandom<RandomGenerator,Distribution>::BaseRandom(RandomGenerator &randomGenerator, Distribution distribution, int cycle) :
        distribution(distribution){
    this->randomGenerator = randomGenerator;
    this->cycle = cycle;
    this->i = 0;
    this->generated = new double[cycle];
    for(int j = 0; j < cycle; ++j) {
        this->generated[j] = distribution(this->randomGenerator);
    }
}

template <class RandomGenerator, class Distribution>
double BaseRandom<RandomGenerator,Distribution>::generate() {
    double num = this->generated[this->i];
    this->i = (this->i + 1) % this->cycle;
    return num;
}

#endif //HOLA_BASERANDOM_H
