#ifndef HOLA_TEST_H
#define HOLA_TEST_H

#include <iostream>
#include <cuda.h>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/execution_policy.h>
#include <fstream>
#include <chrono>

#include "UniformRandomInt.h"
#include "Rastrigin.h"
#include "UniformRandom.h"
#include "UniformRandomInt.h"
#include "GaussianRandom.h"
#include "GaussianMutator.h"
#include "LinearXOver.h"
#include "Hipercube.h"
#include "Tournament.h"
#include "AbstractHAEA.h"

void test1();
void test2();

#endif
