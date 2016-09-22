//
// Created by jefferson on 5/09/16.
//

#ifndef HOLA_LINEARXOVER_H
#define HOLA_LINEARXOVER_H


#include <random>
#include "../Operator.h"
#include "../../random/UniformRandomCPU.h"

class LinearXOver : public Operator<std::vector<double>> {
public:
    LinearXOver();
    std::vector<std::vector<double>> apply(std::vector<std::vector<double>> individuals);
private:
    std::random_device rd;
    std::mt19937 eng;
    UniformRandomCPU ur;
};


#endif //HOLA_LINEARXOVER_H
