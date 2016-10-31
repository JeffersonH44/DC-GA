//
// Created by jefferson on 20/09/16.
//

#ifndef HOLA_RASTRIGIN_H
#define HOLA_RASTRIGIN_H


#include <vector>
#include <cmath>
#include "OptimizationFunction.h"
#include <thrust/device_vector.h>

class Rastrigin : public OptimizationFunction<thrust::device_vector<double> >{
public:
    Rastrigin(bool minimize);
    Rastrigin(double objective);
    Rastrigin();
    double apply(thrust::device_vector<double> ind);
    double apply(double val);

private:
    double objective;
};


#endif //HOLA_RASTRIGIN_H
