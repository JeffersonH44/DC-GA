//
// Created by jefferson on 6/09/16.
//

#ifndef HOLA_ABSTRACTHAEA_H
#define HOLA_ABSTRACTHAEA_H


#include <vector>
#include <random>
#include <memory>

#include "../../random/UniformRandomInt.h"
#include "../Space.h"
#include "../../functions/OptimizationFunction.h"
#include "../../operators/Operator.h"
#include "../../random/UniformRandom.h"

template <class T>
class AbstractHAEA {
public:
    AbstractHAEA(std::vector< std::shared_ptr<Operator<T> > > operators, size_t populationSize, size_t maxIters);
    //virtual void iteration() = 0;

    std::random_device rd;
    std::mt19937 eng;

    UniformRandomInt randomOperator, randomIndividual;
    UniformRandom ur;

    Space<T> *space;
    OptimizationFunction<T> *optimizationFunction;

    size_t populationSize;
    std::vector<T> population;

    size_t maxIters;

    std::vector< std::vector<double> > operatorRates;
    std::vector< std::shared_ptr<Operator<T> > > operators;

    void ratesNormalize(std::vector<double> &operatorRates);
    size_t operatorSelect(std::vector<double> rates);
    std::vector<T> solve(Space<T> *space, OptimizationFunction<T> *goal);
private:
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
AbstractHAEA<T>::AbstractHAEA(std::vector< std::shared_ptr<Operator<T> > > operators, size_t populationSize, size_t maxIters) :
        eng(rd()),
        randomOperator(eng, 0, static_cast<int>(operators.size()) - 1),
        randomIndividual(eng, 0, static_cast<int>(populationSize - 1)),
        ur(eng, 0.0, 1.0)
{
    this->operators = operators;
    this->maxIters = maxIters;
    this->populationSize = populationSize;
}

template <class T>
std::vector<T> AbstractHAEA<T>::solve(Space<T> *space, OptimizationFunction<T> *goal) {
    this->space = space;
    this->optimizationFunction = goal;

    this->initPopulation();
    for(size_t i = 0; i < this->maxIters; ++i) {
        std::vector<T> new_population;
        for(size_t j = 0; j < this->populationSize; ++j) {
            T parent = this->population[j];
            double delta = this->ur.generate();

            std::vector<double> rates = this->operatorRates[j];
            size_t operatorIndex = this->operatorSelect(rates);
            std::shared_ptr< Operator<T> > op = this->operators[operatorIndex];
            int args = op->getArguments();

            double parentFitness = this->optimizationFunction->apply(parent);
            std::vector<T> selectedIndividuals;
            selectedIndividuals.push_back(parent);
            for(int k = 1; k < args; ++k) {
                // TODO: selection of the other individuals
                // TODO: for now we select it randomly
                size_t index = 0;
                do {
                    index = static_cast<size_t>(this->randomIndividual.generate());
                } while(index == j);

                selectedIndividuals.push_back(this->population[index]);
            }

            std::vector<T> offspring = op->apply(selectedIndividuals);
            double childFitness = std::numeric_limits<double>::max();
            T child;
            if(offspring.size() > 1) {
                for(auto ind = offspring.begin(); ind != offspring.end(); ++ind){
                    double currentFitness = this->optimizationFunction->apply(*ind);
                    if(currentFitness < childFitness) {
                        childFitness = currentFitness;
                        child = *ind;
                    }
                }
            } else {
                child = offspring[0];
                childFitness = this->optimizationFunction->apply(child);
            }

            if(childFitness < parentFitness) {
                rates[operatorIndex] *= (1.0 + delta);
            } else {
                rates[operatorIndex] *= (1.0 - delta);
            }

            this->ratesNormalize(rates);

            new_population.push_back(child);
        }
        this->population = new_population;
    }

    return this->population;
}

#endif //HOLA_ABSTRACTHAEA_H
