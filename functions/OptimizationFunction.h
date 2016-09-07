//
// Created by jefferson on 3/09/16.
//

#ifndef HOLA_OPTIMIZATIONFUNCTION_H
#define HOLA_OPTIMIZATIONFUNCTION_H

template <class T>
class OptimizationFunction {
public:
    virtual double apply(T ind) = 0;
};


#endif //HOLA_OPTIMIZATIONFUNCTION_H
