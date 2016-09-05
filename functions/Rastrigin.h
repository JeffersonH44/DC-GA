//
// Created by jefferson on 3/09/16.
//

#ifndef HOLA_RASTRIGIN_H
#define HOLA_RASTRIGIN_H

#include <vector>
#include <cmath>
#include "../ga/OptimizationFunction.h"

class Rastrigin : public OptimizationFunction<std::vector<double>>{
public:
    Rastrigin();
    double apply(std::vector<double> ind);
    double apply(double val);

private:
};


#endif //HOLA_RASTRIGIN_H
