// Using CUDA device to calculate pi
#include <iostream>
#include <cuda.h>
#include <thrust/device_vector.h>

#include "functions/Rastrigin.h"
#include "random/UniformRandom.h"
#include "random/UniformRandomInt.h"
#include "random/GaussianRandom.h"
#include "operators/mutations/GaussianMutator.h"

using namespace std;

// Main routine that executes on the host
int main() {
    thrust::host_vector< thrust::device_vector<double> > individuals, result;
    thrust::device_vector<double> ind(1000, 1.0);
    individuals.push_back(ind);

    GaussianMutator gm(0.0, 1.0, 10.0/50.0);
    for(int i = 0; i < 1000; ++i) {
        result = gm.apply(individuals);
        individuals = thrust::host_vector< thrust::device_vector<double> >(result.begin(), result.end());
    }


    for(size_t i = 0; i < ind.size(); ++i) {
        cout << individuals[0][i] << " ";
    }

    return 0;
}
