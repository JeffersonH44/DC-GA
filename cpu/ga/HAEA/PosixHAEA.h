//
// Created by jefferson on 28/10/16.
//

#ifndef DC_GA_POSIXHAEA_H
#define DC_GA_POSIXHAEA_H


#include "AbstractHAEA.h"

template <class T>
class PosixHAEA : public AbstractHAEA<T> {
public:
    PosixHAEA(Selection<T> &selection, std::vector< std::shared_ptr<Operator<T> > > operators, size_t populationSize, size_t maxIters);
    std::vector<T> solve(Space<T> *space, OptimizationFunction<T> *goal);
    void setThreads(size_t threads);
private:
    static void *iteration(void *instance);
    size_t threads;
};

template <class T>
PosixHAEA<T>::PosixHAEA(Selection<T> &selection, std::vector<std::shared_ptr<Operator<T> > > operators,
                     size_t populationSize, size_t maxIters) : AbstractHAEA<T>(selection, operators, populationSize,
                                                                            maxIters) {
}

template <class T>
struct thread_args {
    AbstractHAEA<T> *solver;
    size_t from;
    size_t to;
};

template <class T>
std::vector<T> PosixHAEA<T>::solve(Space<T> *space, OptimizationFunction<T> *goal) {
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
void *PosixHAEA<T>::iteration(void *instance) {
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
                index = static_cast<size_t>(solver->selection->chooseOne(solver->population));
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

template <class T>
void PosixHAEA<T>::setThreads(size_t threads) {
    this->threads = threads;
}

#endif //DC_GA_POSIXHAEA_H
