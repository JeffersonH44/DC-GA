//
// Created by jefferson on 21/09/16.
//

#ifndef HOLA_OPERATOR_H
#define HOLA_OPERATOR_H

#include <thrust/device_vector.h>

template <class T>
class Operator {
public:
    virtual std::vector<T> apply(std::vector<T> &individuals) = 0;
    int getArguments();
protected:
    int arguments;
};

template <class T>
int Operator<T>::getArguments() {
    return this->arguments;
}


#endif //HOLA_OPERATOR_H
