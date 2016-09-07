#include "ga/Hipercube.h"
#include "functions/Rastrigin.h"
#include "random/GaussianRandom.h"
#include "random/UniformRandom.h"
#include "operators/mutations/GaussianMutator.h"
#include "operators/xover/LinearXOver.h"
#include "random/UniformRandomInt.h"

#include <iostream>
#include <random>
#include <vector>
#include <memory>

using namespace std;

typedef mt19937 base_generator_type;

int main() {
    vector<double> mini(100, 200);
    vector<double> maxi(100, 300);

    random_device rd;
    mt19937 eng(rd());
    UniformRandomInt randomInt(eng, 0, 6);

    cout << randomInt.generate() << endl;

    return 0;
}