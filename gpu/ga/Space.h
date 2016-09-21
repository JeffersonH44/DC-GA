//
// Created by jefferson on 21/09/16.
//

#ifndef HOLA_SPACE_H
#define HOLA_SPACE_H


#include <thrust/host_vector.h>

template <class T>
class Space {
public:
    virtual T repair(T val) = 0;
    virtual T getRandomIndividual() = 0;
    thrust::host_vector<T> repair(thrust::host_vector<T> population);
};


#endif //HOLA_SPACE_H
