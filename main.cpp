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