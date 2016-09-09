//
// Created by jefferson on 6/09/16.
//

#ifndef HOLA_ABSTRACTHAEA_H
#define HOLA_ABSTRACTHAEA_H


#include <vector>
#include <random>
#include <memory>
#include <pthread.h>

#include "../../random/UniformRandomInt.h"
#include "../Space.h"
#include "../../functions/OptimizationFunction.h"
#include "../../operators/Operator.h"
#include "../../random/UniformRandom.h"

template <class T>
class AbstractHAEA {
public:
    AbstractHAEA(std::vector< std::shared_ptr<Operator<T> > > operators, size_t populationSize, size_t maxIters);
    static void *iteration(void *instance);

    pthread_barrier_t pthreadBarrier;

    std::random_device rd;
    std::mt19937 eng;

    UniformRandomInt randomOperator, randomIndividual;
    UniformRandom ur;

    Space<T> *space;
    OptimizationFunction<T> *optimizationFunction;

    size_t populationSize;
    std::vector<T> population, new_population;

    size_t maxIters;

    std::vector< std::vector<double> > operatorRates;
    std::vector< std::shared_ptr<Operator<T> > > operators;

    void ratesNormalize(std::vector<double> &operatorRates);
    size_t operatorSelect(std::vector<double> rates);
    std::vector<T> solve(Space<T> *space, OptimizationFunction<T> *goal, size_t threads);
private:
    void initPopulation();
};

template <class T>
struct thread_args {
    AbstractHAEA<T> *solver;
    size_t from;
    size_t to;
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
        ur(eng, 0.0, 1.0),
        new_population(populationSize)
{
    this->operators = operators;
    this->maxIters = maxIters;
    this->populationSize = populationSize;
}

template <class T>
std::vector<T> AbstractHAEA<T>::solve(Space<T> *space, OptimizationFunction<T> *goal, size_t threads) {
    this->space = space;
    this->optimizationFunction = goal;

    this->initPopulation();

    std::vector<pthread_t> thread(threads);
    std::vector<thread_args<T>> t_args(threads);

    size_t batch = threads < this->populationSize ? (this->populationSize / threads) : this->populationSize;
    size_t from = 0;
    size_t to = from + batch;
    pthread_barrier_init(&this->pthreadBarrier, 0, static_cast<unsigned int>(threads));

    for(size_t i = 0; i < threads; ++i) {
        if(i + 1 == threads) to = this->populationSize;
        t_args[i] = {this, from, to};
        //t_args.solver = *this;
        //t_args.to = to;
        //t_args.from = from;

        int ret = pthread_create(&thread[i], NULL, iteration, &t_args[i]);
        if(ret != 0) {
            printf("Error: pthread_create() failed\n");
            exit(EXIT_FAILURE);
        }

        from = to;
        to += batch;
    }

    void *status;
    for(size_t i = 0; i < threads; ++i) {
        int ret = pthread_join(thread[i], &status);
        if(ret != 0) {
            printf("Error: pthread_join() failed\n");
            exit(EXIT_FAILURE);
        }
    }
    pthread_barrier_destroy(&this->pthreadBarrier);

    return this->population;
}

template <class T>
void *AbstractHAEA<T>::iteration(void *instance) {
    thread_args<T> *args = static_cast<thread_args<T>*>(instance);
    AbstractHAEA<T> *solver = args->solver;
    size_t from = args->from;
    size_t to = args->to;
    //printf("%li %li\n", from, to);

    for(size_t i = 0; i < solver->maxIters; ++i) {
        //printf("%li %li\n", from, to);
        for(size_t j = from; j < to; ++j) {
            T parent = solver->population[j];
            double delta = solver->ur.generate();

            std::vector<double> rates = solver->operatorRates[j];
            size_t operatorIndex = solver->operatorSelect(rates);
            std::shared_ptr< Operator<T> > op = solver->operators[operatorIndex];
            int arguments = op->getArguments();

            double parentFitness = solver->optimizationFunction->apply(parent);
            std::vector<T> selectedIndividuals;
            selectedIndividuals.push_back(parent);
            for(int k = 1; k < arguments; ++k) {
                // TODO: selection of the other individuals
                // TODO: for now we select it randomly
                size_t index = 0;
                do {
                    index = static_cast<size_t>(solver->randomIndividual.generate());
                } while(index == j);
                //printf("index : %i\n", static_cast<int>(index));
                selectedIndividuals.push_back(solver->population[index]);
            }

            std::vector<T> offspring = op->apply(selectedIndividuals);

            // repair offspring
            for(size_t k = 0; k < offspring.size(); ++k) {
                offspring[k] = solver->space->repair(offspring[k]);
            }

            double childFitness = std::numeric_limits<double>::max();
            T child;
            if(offspring.size() > 1) {
                for(auto ind = offspring.begin(); ind != offspring.end(); ++ind){
                    double currentFitness = solver->optimizationFunction->apply(*ind);
                    if(currentFitness < childFitness) {
                        childFitness = currentFitness;
                        child = *ind;
                    }
                }
            } else {
                child = offspring[0];
                childFitness = solver->optimizationFunction->apply(child);
            }

            if(childFitness < parentFitness) {
                rates[operatorIndex] *= (1.0 + delta);
            } else {
                rates[operatorIndex] *= (1.0 - delta);
            }

            solver->ratesNormalize(rates);

            solver->new_population[j] = child;
        }
        pthread_barrier_wait(&solver->pthreadBarrier);

        if(from == 0) {
            solver->population = solver->new_population;
            //printf("unlock \n");
        }
        pthread_barrier_wait(&solver->pthreadBarrier);
        // solver.population = new_population;
    }
    return nullptr;
}

#endif //HOLA_ABSTRACTHAEA_H
