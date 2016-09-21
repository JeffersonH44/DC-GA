//
// Created by jefferson on 21/09/16.
//

#include "UniformRandomInt.h"



UniformRandomInt::UniformRandomInt(int a, int b) :
        rand(a, b)
{
}

thrust::device_vector<double> UniformRandomInt::generate(int n) {
    thrust::device_vector<double> result(static_cast<unsigned long>(n));
    thrust::counting_iterator<unsigned int> index_sequence_begin(0);

    thrust::transform(index_sequence_begin,
                      index_sequence_begin + n,
                      result.begin(),
                      this->rand);

    return result;
}
