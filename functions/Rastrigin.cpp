//
// Created by jefferson on 3/09/16.
//

#include <cstddef>
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

    return 10.0 * len + fitness;
}

Rastrigin::Rastrigin() {

}
