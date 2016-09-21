//
// Created by jefferson on 3/09/16.
//

#include "Space.h"

template <class T>
std::vector<T> Space<T>::repair(std::vector<T> population) {
    std::vector<T> pop(population.size());
    for(int i = 0; i < population.size(); ++i) {
        pop[i] = this->repair(population[i]);
    }

    return pop;
}
