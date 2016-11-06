//
// Created by jefferson on 28/10/16.
//

#ifndef DC_GA_OPENMPHAEA_H
#define DC_GA_OPENMPHAEA_H

#include "AbstractHAEA.h"
#include <omp.h>

template <class T>
class OpenACCHAEA : public AbstractHAEA<T> {
public:
    OpenACCHAEA(Tournament &selection, size_t operatorSize, Operator<T> **operators, size_t populationSize, size_t maxIters);
    T* solve(Space<T> *space, OptimizationFunction<T> *goal);
    void setThreads(size_t threads);
private:
    size_t threads;
    void replacePopulation();
};

template <class T>
OpenACCHAEA<T>::OpenACCHAEA(Tournament &selection, size_t operatorSize, Operator<T> **operators, size_t populationSize,
                          size_t maxIters) : AbstractHAEA<T>(selection, operatorSize, operators, populationSize,
                                                                              maxIters) {
}

template <class T>
void OpenACCHAEA<T>::replacePopulation() {
    for(int i = 0; i < this->populationSize; ++i) {
        std::copy(this->newPopulation[i], this->newPopulation[i] + this->space->getDimension(), this->population[i]);
    }
}

template <class T>
T* OpenACCHAEA<T>::solve(Space<T> *space, OptimizationFunction<T> *goal) {
    this->space = space;
    this->optimizationFunction = goal;

    this->initPopulation();
    size_t dimension = this->space->getDimension();
    size_t popSize = this->populationSize;
    size_t operSize = this->operatorSize;

    #pragma acc data copy(this->population[0:popSize][0:dimension]) copyin(this->newPopulation[0:popSize][0:dimension], this->operatorRates[0:popSize][0:operSize])
    for(size_t i = 0; i < this->maxIters; ++i) {
        //printf("%li %li\n", from, to);
        #pragma acc parallel loop independent
        for(size_t j = 0; j < this->populationSize; ++j) {
            T parent = this->population[j];
            double delta = this->ur.generate();

            double* rates = this->operatorRates[j];
            size_t operatorIndex = this->operatorSelect(rates);
            Operator<T>* op = this->operators[operatorIndex];
            int arguments = op->getArguments();

            double parentFitness = this->optimizationFunction->apply(parent);
            T* selectedIndividuals = new T[arguments];
            selectedIndividuals[0] = parent;
            for(int k = 1; k < arguments; ++k) {
                // TODO: selection of the other individuals
                // TODO: for now we select it randomly
                int index = this->selection->chooseOne(this->population);
                //printf("index : %i\n", static_cast<int>(index));
                selectedIndividuals[k] = this->population[index];
            }

            T* offspring = op->apply(selectedIndividuals);
            delete[] selectedIndividuals;

            // repair offspring
            // TODO: be careful with the in-place modification
            for(int k = 0; k < arguments; ++k) {
                this->space->repair(offspring[k]);
            }

            double childFitness = std::numeric_limits<double>::max();
            T child = nullptr;
            if(arguments > 1) {
                for(int k = 0; k < arguments; ++k){
                    double currentFitness = this->optimizationFunction->apply(offspring[k]);
                    if(currentFitness < childFitness) {
                        if(!child) {
                            delete[] child;
                        }
                        childFitness = currentFitness;
                        child = offspring[k];
                    } else {
                        delete[] offspring[k];
                    }
                }
            } else {
                child = offspring[0];
                childFitness = this->optimizationFunction->apply(child);
            }

            if(childFitness <= parentFitness) {
                if(childFitness < parentFitness)
                    rates[operatorIndex] *= (1.0 + delta);
                std::copy(child, child + this->space->getDimension(), this->newPopulation[j]);
            } else {
                rates[operatorIndex] *= (1.0 - delta);
                std::copy(parent, parent + this->space->getDimension(), this->newPopulation[j]);
            }

            delete child;

            this->ratesNormalize(rates);
        }
        this->replacePopulation();
        //printf("unlock \n");
    }

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


#endif //DC_GA_OPENMPHAEA_H
