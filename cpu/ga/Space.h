//
// Created by jefferson on 3/09/16.
//

#ifndef HOLA_SPACE_H
#define HOLA_SPACE_H

#include <vector>

template <class T>
class Space {
public:
    virtual T repair(T val) = 0;
    virtual T getRandomIndividual() = 0;
    std::vector<T> repair(std::vector<T> population);
};


#endif //HOLA_SPACE_H
