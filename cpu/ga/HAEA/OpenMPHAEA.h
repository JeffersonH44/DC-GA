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
    OpenACCHAEA(Selection<T> &selection, std::vector< std::shared_ptr<Operator<T> > > operators, size_t populationSize, size_t maxIters);
    std::vector<T> solve(Space<T> *space, OptimizationFunction<T> *goal);
    void setThreads(size_t threads);
private:
    size_t threads;
};

template <class T>
OpenACCHAEA<T>::OpenACCHAEA(Selection<T> &selection, std::vector<std::shared_ptr<Operator<T> > > operators,
                       size_t populationSize, size_t maxIters) : AbstractHAEA<T>(selection, operators, populationSize,
                                                                              maxIters) {
}

template <class T>
std::vector<T> OpenACCHAEA<T>::solve(Space<T> *space, OptimizationFunction<T> *goal) {
    this->space = space;
    this->optimizationFunction = goal;

    this->initPopulation();

    for(size_t i = 0; i < this->maxIters; ++i) {
        //printf("%li %li\n", from, to);
        #pragma omp parallel for num_threads(this->threads)
        for(size_t j = 0; j < this->populationSize; ++j) {
            T parent = this->population[j];
            double delta = this->ur.generate();

            std::vector<double> rates = this->operatorRates[j];
            size_t operatorIndex = this->operatorSelect(rates);
            std::shared_ptr< Operator<T> > op = this->operators[operatorIndex];
            int arguments = op->getArguments();

            double parentFitness = this->optimizationFunction->apply(parent);
            std::vector<T> selectedIndividuals;
            selectedIndividuals.push_back(parent);
            for(int k = 1; k < arguments; ++k) {
                // TODO: selection of the other individuals
                // TODO: for now we select it randomly
                size_t index = 0;
                index = static_cast<size_t>(this->selection->chooseOne(this->population));
                //printf("index : %i\n", static_cast<int>(index));
                selectedIndividuals.push_back(this->population[index]);
            }

            std::vector<T> offspring = op->apply(selectedIndividuals);

            // repair offspring
            for(size_t k = 0; k < offspring.size(); ++k) {
                offspring[k] = this->space->repair(offspring[k]);
            }

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

            this->new_population[j] = child;
        }
        this->population = this->new_population;
        //printf("unlock \n");
    }
    return this->population;
}

template <class T>
void OpenACCHAEA<T>::setThreads(size_t threads) {
    this->threads = threads;
}


#endif //DC_GA_OPENMPHAEA_H
