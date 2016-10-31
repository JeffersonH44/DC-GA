//
// Created by jefferson on 20/09/16.
//

#include "Rastrigin.h"

struct saxpy_rastrigin {
    __host__ __device__
    double operator() (const double& val) const {
        return val * val - 10.0 * cos(6.283185307179586 * val);
    }
};

double Rastrigin::apply(double val) {
    return val * val - 10.0 * cos(6.283185307179586 * val);
}

double Rastrigin::apply(thrust::device_vector<double> ind) {
    size_t len = ind.size();
    thrust::device_vector<double> partial_result(len);

    thrust::transform(ind.begin(), ind.end(), partial_result.begin(), saxpy_rastrigin());
    double fitness = thrust::reduce(partial_result.begin(), partial_result.end());
    /*for(size_t i = 0; i < len; ++i) {
        fitness += this->apply(ind[i]);
    }*/

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