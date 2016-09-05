#include "ga/Hipercube.h"
#include "functions/Rastrigin.h"
#include "random/GaussianRandom.h"
#include "random/UniformRandom.h"
#include "operators/mutations/GaussianMutator.h"
#include "operators/xover/LinearXOver.h"

#include <iostream>
#include <random>

using namespace std;

typedef mt19937 base_generator_type;

int main() {
    vector<double> mini(100, 200);
    vector<double> maxi(100, 300);
    Hipercube space(mini, maxi);

    return 0;
}