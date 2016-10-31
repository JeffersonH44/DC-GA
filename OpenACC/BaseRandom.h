//
// Created by jefferson on 4/09/16.
//

#ifndef GPU_HOLA_BASERANDOM_H
#define GPU_HOLA_BASERANDOM_H

#include <cuda.h>
#include <thrust/device_vector.h>


class BaseRandom {
public:
    virtual thrust::device_vector<double> generate(int n) = 0;
};


#endif //HOLA_BASERANDOM_H
