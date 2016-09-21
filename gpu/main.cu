// Using CUDA device to calculate pi
#include <iostream>
#include <cuda.h>
#include <thrust/device_vector.h>

#include "functions/Rastrigin.h"
#include "random/UniformRandom.h"
#include "random/UniformRandomInt.h"
#include "random/GaussianRandom.h"

using namespace std;

// Main routine that executes on the host
int main() {
    GaussianRandom r(5.0, 1.0);

    for(int j = 0 ; j < 2; ++j) {
        thrust::device_vector<double> res = r.generate(5 + j*5);
        for(size_t i = 0; i < res.size(); ++i) {
            cout << res[i] << endl;
        }
        cout << endl;
    }

    return 0;
}
