//
// Created by jefferson on 21/09/16.
//

#include "UniformRandomInt.h"


namespace gpu {
    UniformRandomInt::UniformRandomInt(int a, int b) :
            a(a), b(b)
    {
    }

    thrust::device_vector<double> UniformRandomInt::generate(int n) {
        thrust::device_vector<double> result(static_cast<unsigned long>(n));
        thrust::counting_iterator<unsigned int> index_sequence_begin(0);

        thrust::transform(index_sequence_begin,
                          index_sequence_begin + n,
                          result.begin(),
                          prg_int(static_cast<unsigned int>(rand()), a, b));

        return result;
    }
}
