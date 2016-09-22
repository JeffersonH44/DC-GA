#include "gpu/functions/Rastrigin.h"

#include <iostream>
#include <random>
#include <vector>
#include <memory>
#include <ctime>
#include <chrono>
#include <fstream>
#include <string>
#include <thrust/device_vector.h>

using namespace std;


typedef mt19937 base_generator_type;


int main() {
    thrust::device_vector<double> vec(1000, 3);
    Rastrigin r;
    double result = r.apply(vec);
    cout << result << endl;
    return 0;
}

/*void test_cpu() {

}*/

functions/Rastrigin.cu random/BaseRandom.cu  random/UniformRandom.cu  random/UniformRandomInt.cu random/GaussianRandom.cu  operators/Operator.cu  operators/mutations/GaussianMutator.cu  operators/xover/LinearXOver.cu  ga/Hipercube.cu  ga/Space.cu  selection/Selection.cu  selection/Tournament.cu  ga/HAEA/AbstractHAEA.cu