cmake_minimum_required(VERSION 3.6)
project(gpu)

FIND_PACKAGE(CUDA)
INCLUDE(FindCUDA)

set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -std=c++11")
set(SOURCE_FILES_NVCC main.cu functions/Rastrigin.cu functions/Rastrigin.h random/BaseRandom.cu
        random/BaseRandom.h random/UniformRandom.cu random/UniformRandom.h random/UniformRandomInt.cu
        random/UniformRandomInt.h random/GaussianRandom.cu random/GaussianRandom.h operators/Operator.cu
        operators/Operator.h operators/mutations/GaussianMutator.cu operators/mutations/GaussianMutator.h
        operators/xover/LinearXOver.cu operators/xover/LinearXOver.h ga/Hipercube.cu ga/Hipercube.h
        ga/Space.cu ga/Space.h)

cuda_add_executable(gpu ${SOURCE_FILES_NVCC})