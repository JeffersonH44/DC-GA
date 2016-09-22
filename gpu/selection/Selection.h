//
// Created by jefferson on 21/09/16.
//

#ifndef HOLA_SELECTION_H
#define HOLA_SELECTION_H


#include <cstddef>
#include <thrust/host_vector.h>
#include "../../cpu/functions/OptimizationFunction.h"

template <class T>
class Selection {
public:
    virtual size_t chooseOne(thrust::host_vector<T> population) = 0;

protected:
    OptimizationFunction<T> *function;
};


#endif //HOLA_SELECTION_H
