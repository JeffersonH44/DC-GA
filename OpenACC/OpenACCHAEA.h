//
// Created by jefferson on 28/10/16.
//

#ifndef DC_GA_OPENACCHAEA_H
#define DC_GA_OPENACCHAEA_H

#include "AbstractHAEA.h"
#include "Tournament.h"
//#include <omp.h>
#include <iostream>
#include <cstdio>

size_t operatorSelect(double *rates, size_t operatorSize) {
    size_t size = operatorSize;

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
class OpenACCHAEA : public AbstractHAEA<T> {
public:
    OpenACCHAEA(Tournament &selection, size_t operatorSize, Operator<T> **operators, size_t populationSize, size_t maxIters);
    T* solve(Space<T> *space, OptimizationFunction<T> *goal);
    void setThreads(size_t threads);
private:
    void applyOperator(size_t index, T* selectedIndividuals, T* offspring);
    int getArguments(size_t index);
    void copyIndividual(T from, T to);
    size_t threads;
    GaussianMutator gm;
    LinearXOver lxo;
    void replacePopulation();
};

template <class T>
void OpenACCHAEA<T>::copyIndividual(T from, T to) {
    size_t dimension = this->populationSize;
    for(size_t i = 0; i < dimension; ++i) {
        to[i] = from[i];
    }
}

template <class T>
OpenACCHAEA<T>::OpenACCHAEA(Tournament &selection, size_t operatorSize, Operator<T> **operators, size_t populationSize,
                          size_t maxIters) :
        AbstractHAEA<T>(selection, operatorSize, operators, populationSize, maxIters),
        gm(0.0, 0.3, 0.1, populationSize),
        lxo(populationSize)
{
}

template <class T>
void OpenACCHAEA<T>::replacePopulation() {
    for(int i = 0; i < this->populationSize; ++i) {
        //std::copy(this->newPopulation[i], this->newPopulation[i] + this->space->getDimension(), this->population[i]);
        this->copyIndividual(this->newPopulation[i], this->population[i]);
    }
}

template <class T>
void OpenACCHAEA<T>::applyOperator(size_t index, T* selectedIndividuals, T* offspring) {
    switch(index) {
        case 0:
            this->gm.apply(selectedIndividuals, offspring);
            break;
        case 1:
            this->lxo.apply(selectedIndividuals, offspring);
            break;
    }
}

template <class T>
int OpenACCHAEA<T>::getArguments(size_t index) {
    switch(index) {
        case 0:
            return this->gm.getArguments();
        case 1:
            return this->lxo.getArguments();
    }
    return 0;
}

template <class T>
T* OpenACCHAEA<T>::solve(Space<T> *space, OptimizationFunction<T> *goal) {
    //printf("start");
    this->space = space;
    this->optimizationFunction = goal;

    this->initPopulation();
    size_t dimension = this->space->getDimension();
    size_t popSize = this->populationSize;
    size_t operSize = this->operatorSize;
    size_t iters = this->maxIters;

    Tournament selection(*(this->optimizationFunction), 4, dimension, popSize);
    Hipercube newSpace(-5.12, 5.12, dimension);
    Rastrigin optFunction(dimension);
    T* selectedIndividuals = new T[2];
    T* offspring = new T[2];
    offspring[0] = new double[dimension];
    offspring[1] = new double[dimension];

    T* pop = this->population;
    T* newPop = this->newPopulation;
    double **operRates = this->operatorRates;
    UniformRandomCPU uniformRandomCPU = this->ur;


    #pragma acc data copy(this->population[0:popSize][0:dimension]) copyin(this->newPopulation[0:popSize][0:dimension], this->operatorRates[0:popSize][0:operSize], selectedIndividuals[:2], offspring[:2][:1000])
    for(size_t i = 0; i < iters; ++i) {
        //printf("enter");
        #pragma acc parallel loop independent private(offspring) num_gangs(4)
        for(size_t j = 0; j < popSize; ++j) {
            //printf("hi");
            T parent = pop[j];
            double delta = uniformRandomCPU.generate();
            //printf("hi1");

            double* rates = operRates[j];
            size_t operatorIndex = operatorSelect(rates, operSize);
            //Operator<T>* op = this->operators[operatorIndex];
            int arguments = this->getArguments(operatorIndex);
            //printf("hi2");

            double parentFitness = optFunction.apply(parent);
            //T* selectedIndividuals = new T[arguments];
            selectedIndividuals[0] = parent;
            #pragma acc loop seq
            for(int k = 1; k < arguments; ++k) {
                // TODO: selection of the other individuals
                // TODO: for now we select it randomly
                int index = selection.chooseOne(pop);
                //printf("index : %i\n", static_cast<int>(index));
                selectedIndividuals[k] = pop[index];
            }

            this->applyOperator(operatorIndex, selectedIndividuals, offspring);

            // repair offspring
            // TODO: be careful with the in-place modification
            // #pragma acc parallel loop independent
            for(int k = 0; k < arguments; ++k) {
                newSpace.repair(offspring[k]);
            }
            //printf("hi4");

            double childFitness = std::numeric_limits<double>::max();
            T child = nullptr;
            if(arguments > 1) {
                for(int k = 0; k < arguments; ++k){
                    double currentFitness = optFunction.apply(offspring[k]);
                    if(currentFitness < childFitness) {
                        childFitness = currentFitness;
                        child = offspring[k];
                    }
                }
            } else {
                child = offspring[0];
                childFitness = optFunction.apply(child);
            }

            if(childFitness <= parentFitness) {
                if(childFitness < parentFitness)
                    rates[operatorIndex] *= (1.0 + delta);
                this->copyIndividual(child, newPop[j]);
                //std::copy(child, child + newSpace.getDimension(), this->newPopulation[j]);
            } else {
                rates[operatorIndex] *= (1.0 - delta);
                this->copyIndividual(parent, newPop[j]);
                //std::copy(parent, parent + newSpace.getDimension(), this->newPopulation[j]);
            }

            this->ratesNormalize(rates);
        }
        this->replacePopulation();
        //printf("unlock \n");
    }
    delete[] selectedIndividuals;
    delete offspring[0];
    delete offspring[1];
    delete[] offspring;

    for(int i = 0; i < this->populationSize; ++i) {
        delete[] this->newPopulation[i];
        delete[] this->operatorRates[i];
    }
    delete[] this->newPopulation;
    delete[] this->operatorRates;

    return this->population;
}

template <class T>
void OpenACCHAEA<T>::setThreads(size_t threads) {
    this->threads = threads;
}


#endif //DC_GA_OPENACCHAEA_H
