// Using CUDA device to calculate pi
#include <iostream>
#include <cuda.h>
#include <thrust/device_vector.h>

#include "functions/Rastrigin.h"
#include "random/UniformRandom.h"
#include "random/UniformRandomInt.h"
#include "random/GaussianRandom.h"
#include "operators/mutations/GaussianMutator.h"
#include "operators/xover/LinearXOver.h"
#include "ga/Hipercube.h"

using namespace std;

// Main routine that executes on the host
int main() {
    Hipercube hipercube(-5.12, 5.12, 1000);

    thrust::host_vector< thrust::device_vector<double> > individuals;
    thrust::device_vector<double> ind = hipercube.getRandomIndividual(), ind1 = hipercube.getRandomIndividual();

    for(size_t i = 0; i < ind.size(); ++i) {
        cout << ind[i] << " " << ind1[i] << endl;
    }

    /*individuals.push_back(ind);
    individuals.push_back(ind1);

    LinearXOver lx;
    for(int i = 0; i < 2; ++i) {
        individuals = lx.apply(individuals);
    }


    for(size_t i = 0; i < ind.size(); ++i) {
        cout << individuals[0][i] << " " << individuals[1][i] << endl;
    }*/

    return 0;
}
