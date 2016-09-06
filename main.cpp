#include "ga/Hipercube.h"
#include "functions/Rastrigin.h"
#include "random/GaussianRandom.h"
#include "random/UniformRandom.h"
#include "operators/mutations/GaussianMutator.h"
#include "operators/xover/LinearXOver.h"

#include <iostream>
#include <random>
#include <vector>
#include <memory>

using namespace std;

typedef mt19937 base_generator_type;

int main() {
    vector<double> mini(100, 200);
    vector<double> maxi(100, 300);
    vector< vector<double> > inds;
    inds.push_back(mini);
    Hipercube space(mini, maxi);


    GaussianMutator gaussianMutator(0.0, 1.0, 0.1);
    LinearXOver linearXOver;

    vector<shared_ptr<Operator<vector<double> > > > opers;
    opers.push_back(make_shared<GaussianMutator>(0.0, 1.0, 0.1));

    inds = opers[0]->apply(inds);

    return 0;
}