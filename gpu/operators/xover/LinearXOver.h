//
// Created by jefferson on 21/09/16.
//

#ifndef GPU_HOLA_LINEARXOVER_H
#define GPU_HOLA_LINEARXOVER_H

#include <random>

#include "../Operator.h"

struct linear_xover {
    const double c;

    linear_xover(double c) : c(c) {}

    __host__ __device__
    double operator()(const double& x, const double& y) {
        return x * c + y * (1.0 - c);
    }
};

class LinearXOver : public Operator<thrust::device_vector<double> > {
public:
    LinearXOver();
    thrust::host_vector<thrust::device_vector<double>> apply(thrust::host_vector<thrust::device_vector<double>> &individuals);
};


#endif //HOLA_LINEARXOVER_H
