//
// Created by jefferson on 6/09/16.
//

#include "AbstractHAEA.h"

int AbstractHAEA::operatorSelect(std::vector<double> rates) {
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
            return static_cast<int>(i);
        }
    }
}

void AbstractHAEA::ratesNormalize(std::vector<double> operatorRates) {
    double sum = 0.0;
    size_t size = operatorRates.size();
    for(size_t i = 0; i < size; ++i) {
        sum += operatorRates[i];
    }
    for(size_t i = 0; i < size; ++i) {
        operatorRates[i] /= sum;
    }
}

void AbstractHAEA::initPopulation() {
    for(int i = 0; i < this->populationSize; ++i) {
        this->population.push_back(this->space.getRandomIndividual());

        std::vector<double> operRates(this->operatorRates.size(), 0.0);
        for(size_t j = 0; j < this->operatorRates.size(); ++j) {
            operRates[j] = this->ur.generate();
        }

        this->ratesNormalize(operRates);

        this->operatorRates.push_back(operRates);
    }

}

template <class T>
AbstractHAEA::AbstractHAEA(std::vector<Operator<T> > operators, int populationSize, int maxIters) :
eng(rd()),
randomOperator(eng, 0, static_cast<int>(operators.size()) - 1),
randomIndividual(eng, 0, populationSize - 1),
ur(eng, 0.0, 1.0)
{
    this->operators = operators;
    this->maxIters = maxIters;
}

template <class T>
std::vector<T> AbstractHAEA::solve(Space<T> space, OptimizationFunction<T> goal) {
    this->space = space;
    this->optimizationFunction = goal;

    this->initPopulation();
    for(int i = 0; i < this->maxIters; ++i) {
        std::vector<T> new_population;
        for(int j = 0; j < this->populationSize; ++j) {
            T parent = this->population[j];
            double delta = this->ur.generate();

            std::vector<double> rates = this->operatorRates[i];
            int operatorIndex = this->operatorSelect(rates);
            Operator<T> op = this->operators[operatorIndex];
            int args = op.getArguments();

            double parentFitness = this->optimizationFunction.apply(parent);
            std::vector<T> selectedIndividuals;
            selectedIndividuals.push_back(parent);
            for(int k = 1; k < args; ++k) {
                // TODO: selection of the other individuals
                // TODO: for now we select it randomly
                int index = -1;
                do {
                    index = static_cast<int>(this->randomIndividual.generate());
                } while(index != j);

                selectedIndividuals.push_back(this->population[index]);
            }

            std::vector<T> offspring = op.apply(selectedIndividuals);
            double childFitness = std::numeric_limits<double>::max();
            T child;
            if(offspring.size() > 1) {
                for(auto ind = offspring.begin(); ind != offspring.end(); ++ind){
                    double currentFitness = this->optimizationFunction.apply(*ind);
                    if(currentFitness < childFitness) {
                        childFitness = currentFitness;
                        child = *ind;
                    }
                }
            } else {
                child = offspring[0];
                childFitness = this->optimizationFunction.apply(child);
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