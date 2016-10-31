// Using CUDA device to calculate pi
#include <iostream>
#include <cuda.h>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/execution_policy.h>
#include <fstream>
#include <chrono>

#include "functions/Rastrigin.h"
#include "random/UniformRandom.h"
#include "random/UniformRandomInt.h"
#include "random/GaussianRandom.h"
#include "operators/mutations/GaussianMutator.h"
#include "operators/xover/LinearXOver.h"
#include "ga/Hipercube.h"
#include "selection/Tournament.h"
#include "ga/HAEA/AbstractHAEA.h"

using namespace std;
using ns = std::chrono::microseconds;
using get_time = std::chrono::steady_clock;

void test();

// Main routine that executes on the host
int main() {
    Hipercube h(-5.12, 5.12, 10000);
    thrust::device_vector<double> a = h.getRandomIndividual();
    thrust::device_vector<double> b = h.getRandomIndividual();
    vector<thrust::device_vector<double>> inds;
    inds.push_back(a);
    inds.push_back(b);

    GaussianMutator gaussianMutator(0.0, 0.3, 0.1);
    LinearXOver linearXOver;
    auto start = get_time::now();
    for(int i = 0; i < 100; ++i) {
        h.repair(a);
    }
    auto end = get_time::now();
    auto diff = end - start;
    cout << std::chrono::duration_cast<ns>(diff).count() << " ";
    //test();
    return 0;
}

void test() {
    size_t popSize[] = {100};
    for(int i = 0; i < 1; ++i) {
        std::cout << "population size: " << popSize[i] << std::endl;

        std::ofstream file;
        file.open(std::to_string(popSize[i]) + ".txt");
        size_t ITERS = 1000;
        size_t POP = popSize[i];
        size_t DIM = 1000;
        int sampling = 2;

        Hipercube space(-5.12, 5.12, static_cast<int>(DIM));

        Rastrigin optimizationFunction;
        Tournament selection(optimizationFunction, 4);

        std::shared_ptr<Operator<thrust::device_vector<double> > > lxo = std::make_shared<LinearXOver>(),
                    gm = std::make_shared<GaussianMutator>(0.0, 0.3, 0.1);


        std::vector< std::shared_ptr<Operator<thrust::device_vector<double> > > > opers(2);
        opers[0] = lxo;
        opers[1] = gm;

        AbstractHAEA<thrust::device_vector<double>> search(selection, opers, POP, ITERS);

        for(int k = 0; k < sampling; ++k) {
            std::cout << "iter: " << k << std::endl;
            auto start = get_time::now();
            search.solve(&space, &optimizationFunction);
            auto end = get_time::now();
            auto diff = end - start;
            cout << std::chrono::duration_cast<ns>(diff).count() << " ";
            file  << std::chrono::duration_cast<ns>(diff).count() << " ";
            /*thrust::host_vector<thrust::device_vector<double> > result = search.solve(&space, &optimizationFunction);
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