//
// Created by jefferson on 3/09/16.
//

#ifndef HOLA_SPACE_H
#define HOLA_SPACE_H

#include <vector>
#include <cstddef>

template <class T>
class Space {
public:
    virtual T repair(T val) = 0;
    virtual T getRandomIndividual() = 0;
    virtual size_t getDimension() = 0;
};


#endif //HOLA_SPACE_H
