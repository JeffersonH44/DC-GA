//
// Created by jefferson on 8/09/16.
//

#ifndef HOLA_SELECTION_H
#define HOLA_SELECTION_H

#include <vector>
#include <cstddef>
#include "../functions/OptimizationFunction.h"

template <class T>
class Selection {
public:
    virtual size_t chooseOne(std::vector<T> population) = 0;

protected:
    OptimizationFunction<T> *function;
};


#endif //HOLA_SELECTION_H
