//
// Created by jefferson on 14/11/16.
//

#ifndef DC_GA_OPENMPIHAEA_H
#define DC_GA_OPENMPIHAEA_H


#include "AbstractHAEA.h"

#include <cmath>
#include <iostream>
#include <boost/serialization/vector.hpp>
#include <boost/mpi.hpp>
#include <cstdlib>

namespace mpi = boost::mpi;

template <class T>
class OpenMPIHAEA : public AbstractHAEA<T> {
public:
    OpenMPIHAEA(Selection<T> &selection, std::vector< std::shared_ptr<Operator<T> > > operators, size_t populationSize, size_t maxIters);
    std::vector<T> solve(Space<T> *space, OptimizationFunction<T> *goal);
    void setThreads(size_t threads);
    void setArgc(int argc);
    void setArgv(char **argv);
private:
    size_t threads;
    int argc;
    char **argv;
};

template <class T>
OpenMPIHAEA<T>::OpenMPIHAEA(Selection<T> &selection, std::vector<std::shared_ptr<Operator<T> > > operators,
                         size_t populationSize, size_t maxIters) : AbstractHAEA<T>(selection, operators, populationSize,
                                                                                maxIters) {

}

template <class T>
std::vector<T> OpenMPIHAEA<T>::solve(Space<T> *space, OptimizationFunction<T> *goal) {
    this->space = space;
    this->optimizationFunction = goal;

    size_t tasks, iam, from, to, processSize, popSize = this->populationSize;

    this->initPopulation();

    mpi::environment env(this->argc, this->argv);
    mpi::communicator world;

    tasks = static_cast<size_t>(world.size());
    iam = static_cast<size_t>(world.rank());
    processSize = popSize / tasks;
    from = iam * processSize;
    to = iam + 1 == tasks ? popSize : from + processSize;

    for(size_t i = 0; i < this->maxIters; ++i) {
        //printf("%li %li\n", from, to);
        #pragma omp parallel for num_threads(this->threads)
        for(size_t j = from; j < to; ++j) {
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
        //std::cout << "I am: " << iam << std::endl;
        if(iam == 0) {
            for(size_t j = to; j < this->populationSize; ++j) {
                //std::cout << "receiving: " << j << std::endl;
                world.recv(mpi::any_source, static_cast<int>(j), this->new_population[j]);
            }
        } else {
            for(size_t j = from; j < to; ++j) {
                //std::cout << "sending: " << j << std::endl;
                world.send(0, static_cast<int>(j), this->new_population[j]);
            }
        }
        world.barrier();
        this->population = this->new_population;
        broadcast(world, this->population, 0);
        //printf("unlock \n");
    }

    if(iam != 0) {
        MPI_Finalize();
        exit(EXIT_SUCCESS);
    }

    return this->population;
}

template <class T>
void OpenMPIHAEA<T>::setThreads(size_t threads) {
    this->threads = threads;
}

template <class T>
void OpenMPIHAEA<T>::setArgc(int argc) {
    this->argc = argc;
}

template <class T>
void OpenMPIHAEA<T>::setArgv(char **argv) {
    this->argv = argv;
}


#endif //DC_GA_OPENMPIHAEA_H
