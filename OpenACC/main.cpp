#include <iostream>
#include <chrono>
#include <fstream>
#include <memory>

#include "Hipercube.h"
#include "Rastrigin.h"
#include "Tournament.h"
#include "GaussianMutator.h"
#include "LinearXOver.h"
#include "AbstractHAEA.h"


using namespace std;
using ns = chrono::microseconds;
using get_time = chrono::steady_clock;
size_t DIM = 1000;

void test();

int main() {
    Hipercube h(-5.12, 5.12, DIM);
    Rastrigin r(DIM);
    double *inds[10];
    for(int i = 0; i < 10; ++i){
        inds[i] = h.getRandomIndividual();
    }
    GaussianMutator gm(0.0, 1.0, 3.0/DIM, DIM);
    LinearXOver lxo(DIM);
    Tournament t(r, 4, DIM, 10);
    auto start = get_time::now();
    for(int i = 0; i < 100; ++i) {
        size_t j = t.chooseOne(inds);
        cout << j << endl;
    }
    auto end = get_time::now();
    auto diff = end - start;
    cout << std::chrono::duration_cast<ns>(diff).count() << endl;
    //test();
    return 0;
}

/*void test() {
    size_t popSize[] = {50};
    for(int i = 0; i < 1; ++i) {
        cout << "population size: " << popSize[i] << endl;
        for(size_t j = 1; j <= 5; j += 7) {

            ofstream file;
            file.open(to_string(popSize[i]) + "_" + to_string(j) + ".txt");

            cout << "threads: " << j << endl;
            size_t ITERS = 500;
            size_t POP = popSize[i];
            size_t DIM = 1000;
            size_t THREADS = j;
            int sampling = 3;

            Hipercube space(-5.12, 5.12, DIM);
            Rastrigin optimizationFunction;
            Tournament selection(optimizationFunction, 4);

            cout << optimizationFunction.apply(space.getRandomIndividual()) << endl;

            vector< shared_ptr<Operator<vector<double> > > > opers;
            opers.push_back(make_shared<GaussianMutator>(0.0, 0.3, 0.1));
            opers.push_back(make_shared<LinearXOver>());

            OpenMPHAEA<vector<double>> search(selection, opers, POP, ITERS);
            search.setThreads(THREADS);

            double rmean = 0.0;

            for(int k = 0; k < sampling; ++k) {
                cout << "iter: " << k << endl;
                auto start = get_time::now();
                vector<vector<double>> pop = search.solve(&space, &optimizationFunction);
                double bestInd = 10e8;
                for(size_t z = 0; z < pop.size(); ++z) {
                    double elem = optimizationFunction.apply(pop[z]);
                    if(elem < bestInd) {
                        bestInd = elem;
                    }
                }

                cout << bestInd << endl;
                auto end = get_time::now();
                auto diff = end - start;
                file  << chrono::duration_cast<ns>(diff).count() << " ";
                vector<vector<double> > result = search.solve(&space, &optimizationFunction, THREADS);
                double mean = 0.0;

                for(size_t i = 0; i < result.size(); ++i) {
                    for(size_t j = 0; j < result[0].size(); ++j) {
                        cout << result[i][j] << " ";
                    }
                    mean += optimizationFunction.apply(result[i]);
                }

                mean /= result.size();
                rmean += mean;
            }
            file.close();
        }
    }
}*/
