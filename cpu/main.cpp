#include <iostream>
#include <chrono>
#include <fstream>
#include <memory>

#include "ga/Hipercube.h"
#include "functions/Rastrigin.h"
#include "selection/Tournament.h"
#include "operators/mutations/GaussianMutator.h"
#include "operators/xover/LinearXOver.h"
#include "ga/HAEA/AbstractHAEA.h"
#include "ga/HAEA/PosixHAEA.h"


using namespace std;
using ns = chrono::microseconds;
using get_time = chrono::steady_clock;

void test();

int main() {
    test();
    return 0;
}

void test() {
    size_t popSize[] = {50};
    for(int i = 0; i < 1; ++i) {
        cout << "population size: " << popSize[i] << endl;
        for(size_t j = 8; j <= 8; j += 7) {

            ofstream file;
            file.open(to_string(popSize[i]) + "_" + to_string(j) + ".txt");

            cout << "threads: " << j << endl;
            size_t ITERS = 500;
            size_t POP = popSize[i];
            size_t DIM = 1000;
            size_t THREADS = j;
            int sampling = 35;

            Hipercube space(-5.12, 5.12, DIM);
            Rastrigin optimizationFunction;
            Tournament selection(optimizationFunction, 4);

            vector< shared_ptr<Operator<vector<double> > > > opers;
            opers.push_back(make_shared<GaussianMutator>(0.0, 0.3, 0.1));
            opers.push_back(make_shared<LinearXOver>());

            PosixHAEA<vector<double>> search(selection, opers, POP, ITERS);
            search.setThreads(THREADS);

            double rmean = 0.0;

            for(int k = 0; k < sampling; ++k) {
                cout << "iter: " << k << endl;
                auto start = get_time::now();
                search.solve(&space, &optimizationFunction);
                auto end = get_time::now();
                auto diff = end - start;
                file  << chrono::duration_cast<ns>(diff).count() << " ";
                /*vector<vector<double> > result = search.solve(&space, &optimizationFunction, THREADS);
                double mean = 0.0;

                for(size_t i = 0; i < result.size(); ++i) {
                    for(size_t j = 0; j < result[0].size(); ++j) {
                        cout << result[i][j] << " ";
                    }
                    mean += optimizationFunction.apply(result[i]);
                }

                mean /= result.size();
                rmean += mean;*/
            }
            file.close();
        }
    }
}