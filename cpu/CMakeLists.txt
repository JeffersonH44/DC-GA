cmake_minimum_required(VERSION 3.6)

project(mytest)

set(SOURCE_FILES_MPI mainMPI.cpp ga/Space.cpp ga/Space.h ga/Hipercube.cpp ga/Hipercube.h functions/OptimizationFunction.cpp
        functions/OptimizationFunction.h functions/Rastrigin.cpp functions/Rastrigin.h operators/Operator.cpp
        operators/Operator.h operators/mutations/GaussianMutator.cpp operators/mutations/GaussianMutator.h
        random/GaussianRandom.cpp random/GaussianRandom.h random/BaseRandom.cpp random/BaseRandom.h
        random/UniformRandomCPU.cpp random/UniformRandomCPU.h operators/xover/LinearXOver.cpp
        operators/xover/LinearXOver.h distance/Distance.cpp distance/Distance.h ga/HAEA/AbstractHAEA.cpp
        ga/HAEA/AbstractHAEA.h random/UniformRandomIntCPU.cpp random/UniformRandomIntCPU.h selection/Selection.cpp
        selection/Selection.h selection/Tournament.cpp selection/Tournament.h ga/HAEA/OpenMPIHAEA.cpp ga/HAEA/OpenMPIHAEA.h)

add_executable(mytest ${SOURCE_FILES_MPI})

# Require MPI for this project:
find_package(MPI REQUIRED)
find_package (Boost 1.55.0 REQUIRED COMPONENTS mpi)

set(CMAKE_CXX_COMPILE_FLAGS ${CMAKE_CXX_COMPILE_FLAGS} ${MPI_COMPILE_FLAGS} ${Boost_LIBRARIES} -fopenmp)
set(CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS} ${MPI_LINK_FLAGS})
include_directories(${MPI_INCLUDE_PATH})
target_link_libraries(mytest ${MPI_LIBRARIES} ${Boost_LIBRARIES})

# Add a test:
enable_testing()
add_test(SimpleTest ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} 4 ${CMAKE_CURRENT_BINARY_DIR}/mytest)

project(cpu)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp -lpthread -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused")


set(SOURCE_FILES_CXX main.cpp ga/Space.cpp ga/Space.h ga/Hipercube.cpp ga/Hipercube.h functions/OptimizationFunction.cpp
        functions/OptimizationFunction.h functions/Rastrigin.cpp functions/Rastrigin.h operators/Operator.cpp
        operators/Operator.h operators/mutations/GaussianMutator.cpp operators/mutations/GaussianMutator.h
        random/GaussianRandom.cpp random/GaussianRandom.h random/BaseRandom.cpp random/BaseRandom.h
        random/UniformRandomCPU.cpp random/UniformRandomCPU.h operators/xover/LinearXOver.cpp
        operators/xover/LinearXOver.h distance/Distance.cpp distance/Distance.h ga/HAEA/AbstractHAEA.cpp
        ga/HAEA/AbstractHAEA.h random/UniformRandomIntCPU.cpp random/UniformRandomIntCPU.h selection/Selection.cpp
        selection/Selection.h selection/Tournament.cpp selection/Tournament.h ga/HAEA/PosixHAEA.cpp ga/HAEA/PosixHAEA.h ga/HAEA/OpenMPHAEA.cpp ga/HAEA/OpenMPHAEA.h)

add_executable(cpu ${SOURCE_FILES_CXX})