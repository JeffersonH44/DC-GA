//
// Created by jefferson on 21/09/16.
//

#include "UniformRandom.h"

#include <thrust/random.h>
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/iterator/counting_iterator.h>

namespace gpu {
    UniformRandom::UniformRandom(double a, double b) :
            a(a), b(b)
    {
    }

    thrust::device_vector<double> UniformRandom::generate(int n) {
        thrust::device_vector<double> result(static_cast<unsigned long>(n));
        thrust::counting_iterator<unsigned int> index_sequence_begin(0);

        thrust::transform(index_sequence_begin,
                          index_sequence_begin + n,
                          result.begin(),
                          prg_real(static_cast<unsigned int>(rand()), a, b));

        return result;
    }
}