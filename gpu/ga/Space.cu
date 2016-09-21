//
// Created by jefferson on 21/09/16.
//

#include "Space.h"

template <class T>
thrust::host_vector<T> Space<T>::repair(thrust::host_vector<T> population) {
    thrust::host_vector<T> pop(population.size());
    for(int i = 0; i < population.size(); ++i) {
        pop[i] = this->repair(population[i]);
    }

    return pop;
}