//
// Created by jefferson on 6/09/16.
//

#ifndef HOLA_ABSTRACTHAEA_H
#define HOLA_ABSTRACTHAEA_H


#include <vector>
#include <random>
#include <memory>
#include <pthread.h>
#include "openacc.h"

#include "UniformRandomIntCPU.h"
#include "Space.h"
#include "OptimizationFunction.h"
#include "Operator.h"
#include "UniformRandomCPU.h"
#include "Selection.h"

template <class T>
class AbstractHAEA {
public:
    AbstractHAEA(Tournament &selection, size_t operatorSize, Operator<T> **operators, size_t populationSize, size_t maxIters);

    pthread_barrier_t pthreadBarrier;

    std::random_device rd;
    std::mt19937 eng;

    UniformRandomIntCPU randomOperator, randomIndividual;
    UniformRandomCPU ur;

    Space<T> *space;
    OptimizationFunction<T> *optimizationFunction;

    size_t populationSize;
    size_t operatorSize;
    size_t maxIters;

    T *population, *newPopulation;

    double **operatorRates;
    Operator<T> **operators;

    Tournament *selection;

    #pragma acc routine seq
    void ratesNormalize(double *operatorRates);
    #pragma acc routine seq
    size_t operatorSelect(double *rates);
    virtual T* solve(Space<T> *space, OptimizationFunction<T> *goal) = 0;
protected:
    void initPopulation();
};

template <class T>
size_t AbstractHAEA<T>::operatorSelect(double *rates) {
    size_t size = this->operatorSize;

    double lower = 0.0;
    double upper = rates[0];
    double num = this->ur.generate();
    for(size_t i = 1; i < size + 1; ++i) {
        if(lower <= num && num < upper)
            return i;
        lower = upper;
        upper += i < size ? rates[i] : 0.0;
    }

    /*double *values = (double*) acc_malloc(sizeof(double) * (size + 1));

    std::fill(values, values + size + 1, 0.0);
    double sum = 0.0;
    values[size] = 1.0;
    for(size_t i = 1; i < size; ++i) {
        sum += rates[i - 1];
        values[i] = sum;
    }

    for(size_t i = 0; i < size; ++i) {
        if(values[i] <= num && num < values[i + 1]) {
            acc_free(values);
            return static_cast<size_t>(i);
        }
    }*/

    return 2387454937;
}

template <class T>
void AbstractHAEA<T>::ratesNormalize(double *operatorRates) {
    double sum = 0.0;
    size_t size = this->operatorSize;
    for(size_t i = 0; i < size; ++i) {
        sum += operatorRates[i];
    }
    for(size_t i = 0; i < size; ++i) {
        operatorRates[i] /= sum;
    }
}

template <class T>
void AbstractHAEA<T>::initPopulation() {
    this->population = new T[this->populationSize];
    this->newPopulation = new T[this->populationSize];
    this->operatorRates = new double*[this->populationSize];
    for(int i = 0; i < this->populationSize; ++i) {
        this->operatorRates[i] = new double[this->operatorSize];
    }

    for(size_t i = 0; i < this->populationSize; ++i) {
        this->population[i] = this->space->getRandomIndividual();
        this->newPopulation[i] = this->space->getRandomIndividual();
        //std::vector<double> operRates(this->operators.size(), 0.0);
        for(size_t j = 0; j < this->operatorSize; ++j) {
            this->operatorRates[i][j] = this->ur.generate();
        }

        this->ratesNormalize(this->operatorRates[i]);
    }

}

template <class T>
AbstractHAEA<T>::AbstractHAEA(Tournament &selection, size_t operatorSize, Operator<T> **operators, size_t populationSize, size_t maxIters) :
        eng(rd()),
        randomOperator(eng, 0, static_cast<int>(operatorSize - 1)),
        randomIndividual(eng, 0, static_cast<int>(populationSize - 1)),
        ur(eng, 0.0, 1.0)
{
    this->maxIters = maxIters;
    this->populationSize = populationSize;
    this->operatorSize = operatorSize;

    this->operators = operators;
    this->selection = &selection;
}



#endif //HOLA_ABSTRACTHAEA_H
