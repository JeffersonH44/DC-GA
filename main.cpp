#include "ga/Hipercube.h"
#include "functions/Rastrigin.h"
#include "operators/mutations/GaussianMutator.h"
#include "operators/xover/LinearXOver.h"
#include "ga/HAEA/AbstractHAEA.h"

#include <iostream>
#include <random>
#include <vector>
#include <memory>

using namespace std;

typedef mt19937 base_generator_type;

int main() {
    size_t ITERS = 500;
    size_t POP = 100;
    size_t DIM = 20;
    size_t THREADS = 8;

    Hipercube space(-5.12, 5.12, DIM);
    Rastrigin optimizationFunction;

    vector< shared_ptr<Operator<vector<double> > > > opers;
    opers.push_back(make_shared<GaussianMutator>(0.0, 0.3, 0.1));
    opers.push_back(make_shared<LinearXOver>());

    AbstractHAEA<vector<double>> search(opers, POP, ITERS);

    double rmean = 0.0;

    for(int k = 0; k < 30; ++k) {
        vector<vector<double> > result = search.solve(&space, &optimizationFunction, THREADS);
        double mean = 0.0;

        for(size_t i = 0; i < result.size(); ++i) {
            /*for(size_t j = 0; j < result[0].size(); ++j) {
                cout << result[i][j] << " ";
            }*/
            mean += optimizationFunction.apply(result[i]);
        }

        mean /= result.size();
        rmean += mean;
    }

    cout << "mean: " << rmean / 30.0 << endl;

    return 0;
}