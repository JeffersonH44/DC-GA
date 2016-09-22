//
// Created by jefferson on 21/09/16.
//

#include "GaussianRandom.h"
#include <random>

namespace gpu {
    GaussianRandom::GaussianRandom(double mean, double std) :
            mean(mean),
            std(std)
    {
    }

    thrust::device_vector<double> GaussianRandom::generate(int n) {

        thrust::device_vector<double> result(static_cast<unsigned long>(n));
        thrust::counting_iterator<unsigned int> index_sequence_begin(0);
        unsigned int seed = static_cast<unsigned int>(rand());

        thrust::transform(index_sequence_begin,
                          index_sequence_begin + n,
                          result.begin(),
                          prg_gaussian(seed, mean, std));

        return result;
    }
}
