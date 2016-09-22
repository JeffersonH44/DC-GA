cmake_minimum_required(VERSION 3.6)
project(gpu)

FIND_PACKAGE(CUDA)
INCLUDE(FindCUDA)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11")
list(APPEND CUDA_NVCC_FLAGS "-std=c++11 -gencode arch=compute_50,code=compute_50")
set(CUDA_PROPAGATE_HOST_FLAGS OFF)

set(SOURCE_FILES_NVCC main.cu functions/Rastrigin.cu functions/Rastrigin.h random/BaseRandom.cu
        random/BaseRandom.h random/UniformRandom.cu random/UniformRandom.h random/UniformRandomInt.cu
        random/UniformRandomInt.h random/GaussianRandom.cu random/GaussianRandom.h operators/Operator.cu
        operators/Operator.h operators/mutations/GaussianMutator.cu operators/mutations/GaussianMutator.h
        operators/xover/LinearXOver.cu operators/xover/LinearXOver.h ga/Hipercube.cu ga/Hipercube.h
        ga/Space.cu ga/Space.h selection/Selection.cu selection/Selection.h selection/Tournament.cu
        selection/Tournament.h ga/HAEA/AbstractHAEA.cu ga/HAEA/AbstractHAEA.h
        ../cpu/random/BaseRandom.h ../cpu/random/BaseRandom.cpp ../cpu/random/UniformRandomCPU.cpp
        ../cpu/random/UniformRandomCPU.h ../cpu/random/UniformRandomIntCPU.cpp ../cpu/random/UniformRandomIntCPU.h)

cuda_add_executable(gpu ${SOURCE_FILES_NVCC})