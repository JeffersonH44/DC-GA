//
// Created by jefferson on 6/09/16.
//

#ifndef HOLA_ABSTRACTHAEA_H
#define HOLA_ABSTRACTHAEA_H


#include <vector>
#include <random>
#include <memory>
#include <pthread.h>

#include "../../random/UniformRandomIntCPU.h"
#include "../Space.h"
#include "../../functions/OptimizationFunction.h"
#include "../../operators/Operator.h"
#include "../../random/UniformRandomCPU.h"
#include "../../selection/Selection.h"

template <class T>
class AbstractHAEA {
public:
    AbstractHAEA(Selection<T> &selection, std::vector< std::shared_ptr<Operator<T> > > operators, size_t populationSize, size_t maxIters);

    pthread_barrier_t pthreadBarrier;

    std::random_device rd;
    std::mt19937 eng;

    UniformRandomIntCPU randomOperator, randomIndividual;
    UniformRandomCPU ur;

    Space<T> *space;
    OptimizationFunction<T> *optimizationFunction;

    size_t populationSize;
    std::vector<T> population, new_population;

    size_t maxIters;

    std::vector< std::vector<double> > operatorRates;
    std::vector< std::shared_ptr<Operator<T> > > operators;

    Selection<T> *selection;

    void ratesNormalize(std::vector<double> &operatorRates);
    size_t operatorSelect(std::vector<double> rates);
    virtual std::vector<T> solve(Space<T> *space, OptimizationFunction<T> *goal) = 0;

protected:
    void initPopulation();
};

template <class T>
size_t AbstractHAEA<T>::operatorSelect(std::vector<double> rates) {
    size_t size = rates.size();

    std::vector<double> values(size + 1, 0.0);
    double sum = 0.0;
    values[size] = 1.0;
    for(size_t i = 1; i < size; ++i) {
        sum += rates[i - 1];
        values[i] = sum;
    }

    double num = this->ur.generate();
    for(size_t i = 0; i < size; ++i) {
        if(values[i] <= num && num < values[i + 1]) {
            return static_cast<size_t>(i);
        }
    }

    return 2387454937;
}

template <class T>
void AbstractHAEA<T>::ratesNormalize(std::vector<double> &operatorRates) {
    double sum = 0.0;
    size_t size = operatorRates.size();
    for(size_t i = 0; i < size; ++i) {
        sum += operatorRates[i];
    }
    for(size_t i = 0; i < size; ++i) {
        operatorRates[i] /= sum;
    }
}

template <class T>
void AbstractHAEA<T>::initPopulation() {
    for(size_t i = 0; i < this->populationSize; ++i) {
        this->population.push_back(this->space->getRandomIndividual());

        std::vector<double> operRates(this->operators.size(), 0.0);
        for(size_t j = 0; j < this->operators.size(); ++j) {
            operRates[j] = this->ur.generate();
        }

        this->ratesNormalize(operRates);

        this->operatorRates.push_back(operRates);
    }

}

template <class T>
AbstractHAEA<T>::AbstractHAEA(Selection<T> &selection, std::vector< std::shared_ptr<Operator<T> > > operators, size_t populationSize, size_t maxIters) :
        eng(rd()),
        randomOperator(eng, 0, static_cast<int>(operators.size()) - 1),
        randomIndividual(eng, 0, static_cast<int>(populationSize - 1)),
        ur(eng, 0.0, 1.0),
        new_population(populationSize)
{
    this->operators = operators;
    this->maxIters = maxIters;
    this->populationSize = populationSize;
    this->selection = &selection;
}



#endif //HOLA_ABSTRACTHAEA_H
