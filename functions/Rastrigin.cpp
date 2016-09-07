//
// Created by jefferson on 3/09/16.
//

#include <cstddef>
#include <limits>
#include "Rastrigin.h"

double Rastrigin::apply(double val) {
    return val * val - 10.0 * cos(6.283185307179586 * val);
}

double Rastrigin::apply(std::vector<double> ind) {
    size_t len = ind.size();
    double fitness = 0.0;

    for(size_t i = 0; i < len; ++i) {
        fitness += this->apply(ind[i]);
    }

    fitness = 10.0 * len + fitness;

    return std::abs(this->objective - fitness);
}


// TODO: be careful with the max double
Rastrigin::Rastrigin(bool minimize) {
    this->objective = minimize ? 0.0 : std::numeric_limits<double>::max();
}

Rastrigin::Rastrigin(double objective) {
    this->objective = objective;
}

Rastrigin::Rastrigin() :
Rastrigin(true)
{
}
