//
// Created by jefferson on 3/09/16.
//

#ifndef HOLA_RASTRIGIN_H
#define HOLA_RASTRIGIN_H

#include <vector>
#include <cmath>
#include "OptimizationFunction.h"

class Rastrigin : public OptimizationFunction<double*>{
public:
    Rastrigin(size_t dimension, bool minimize);
    Rastrigin(size_t dimension, double objective);
    Rastrigin(size_t dimension);
    double apply(double* ind);
    double apply(double val);

private:
    double objective;
    size_t dimension;
};


#endif //HOLA_RASTRIGIN_H
