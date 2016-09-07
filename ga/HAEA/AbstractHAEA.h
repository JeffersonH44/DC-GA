//
// Created by jefferson on 6/09/16.
//

#ifndef HOLA_ABSTRACTHAEA_H
#define HOLA_ABSTRACTHAEA_H


#include <vector>
#include <random>

#include "../../random/UniformRandomInt.h"
#include "../Space.h"
#include "../../functions/OptimizationFunction.h"
#include "../../operators/Operator.h"
#include "../../random/UniformRandom.h"

template <class T>
class AbstractHAEA {
public:
    AbstractHAEA(std::vector<Operator<T> > operators, int populationSize, int maxIters)
protected:
    virtual void iteration() = 0;

    std::random_device rd;
    std::mt19937 eng;

    UniformRandomInt randomOperator, randomIndividual;
    UniformRandom ur;

    Space<T> space;
    OptimizationFunction<T> optimizationFunction;

    int populationSize;
    std::vector<T> population;

    int maxIters;

    std::vector< std::vector<double> > operatorRates;
    std::vector< Operator<T> > operators;

    void ratesNormalize(std::vector<double> operatorRates);
    int operatorSelect(std::vector<double> rates);
    std::vector<T> solve(Space<T> space, OptimizationFunction<T> goal);
private:
    void initPopulation();
};


#endif //HOLA_ABSTRACTHAEA_H
