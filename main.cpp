#include "ga/Hipercube.h"
#include "functions/Rastrigin.h"
#include "random/GaussianRandom.h"
#include "random/UniformRandom.h"
#include "operators/mutations/GaussianMutator.h"

#include <iostream>
#include <random>

using namespace std;

typedef mt19937 base_generator_type;

int main() {
    vector<double> mini(100, 200);
    vector<double> maxi(100, 300);
    Hipercube space(mini, maxi);

    vector<double> curr(100, 0);
    curr = space.repair(curr);

    random_device rd;
    base_generator_type eng(rd());
    UniformRandom ur(eng, 0.0, 1.0);
    GaussianRandom gr(eng, 0.0, 1.0);

    cout << ur.generate() << endl;
    cout << gr.generate() << endl;

    GaussianMutator gMutation(0.0, 1.0, 1.0/100);
    cout << gMutation.getArguments() << endl;
    vector<vector<double>> individuals(static_cast<unsigned long>(gMutation.getArguments()));
    individuals[0] = curr;
    curr = gMutation.apply(individuals);

    for(size_t i = 0 ; i < curr.size(); ++i) {
        cout << curr[i] << endl;
    }

    cout << "****************************************" << endl;
    Rastrigin f;

    for(auto i = curr.begin(); i != curr.end(); ++i) {
        std::cout << *i << std::endl;
    }

    return 0;
}