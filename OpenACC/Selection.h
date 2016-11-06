//
// Created by jefferson on 8/09/16.
//

#ifndef HOLA_SELECTION_H
#define HOLA_SELECTION_H

#include <vector>
#include <cstddef>
#include "OptimizationFunction.h"

template <class T>
class Selection {
public:
    #pragma acc routine seq
    virtual size_t chooseOne(T *population) = 0;

protected:
    OptimizationFunction<T> *function;
};


#endif //HOLA_SELECTION_H
