//
// Created by jefferson on 21/09/16.
//

#ifndef HOLA_TOURNAMENT_H
#define HOLA_TOURNAMENT_H


#include <random>
#include <thrust/device_vector.h>
#include "Selection.h"

class Tournament : public Selection<thrust::device_vector<double> >{
public:
    Tournament(OptimizationFunction<thrust::device_vector<double> > &function, int n);
    size_t chooseOne(thrust::host_vector< thrust::device_vector<double> > population);
private:
    std::random_device rd;
    std::mt19937 eng;
    int n;
};


#endif //HOLA_TOURNAMENT_H
