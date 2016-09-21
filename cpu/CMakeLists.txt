cmake_minimum_required(VERSION 3.6)
project(cpu)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -lpthread -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused")

set(SOURCE_FILES_CXX main.cpp ga/Space.cpp ga/Space.h ga/Hipercube.cpp ga/Hipercube.h functions/OptimizationFunction.cpp functions/OptimizationFunction.h functions/Rastrigin.cpp functions/Rastrigin.h operators/Operator.cpp operators/Operator.h operators/mutations/GaussianMutator.cpp operators/mutations/GaussianMutator.h random/GaussianRandom.cpp random/GaussianRandom.h random/BaseRandom.cpp random/BaseRandom.h random/UniformRandom.cpp random/UniformRandom.h operators/xover/LinearXOver.cpp operators/xover/LinearXOver.h distance/Distance.cpp distance/Distance.h ga/HAEA/AbstractHAEA.cpp ga/HAEA/AbstractHAEA.h random/UniformRandomInt.cpp random/UniformRandomInt.h selection/Selection.cpp selection/Selection.h selection/Tournament.cpp selection/Tournament.h)

add_executable(cpu ${SOURCE_FILES_CXX})