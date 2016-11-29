//
// Created by jefferson on 3/09/16.
//

#ifndef HOLA_OPERATOR_H
#define HOLA_OPERATOR_H

#include <vector>

template <class T>
class Operator {
public:
    virtual T* apply(T *individuals, T *toReturn) = 0;
    #pragma acc routine
    int getArguments();
protected:
    int arguments;
};

template <class T>
int Operator<T>::getArguments() {
    return this->arguments;
}

#endif //HOLA_OPERATOR_H
