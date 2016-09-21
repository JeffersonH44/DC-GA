//
// Created by jefferson on 15/09/16.
//

#ifndef HOLA_TOURNAMENT_H
#define HOLA_TOURNAMENT_H


#include <random>
#include "Selection.h"

class Tournament : public Selection<std::vector<double>>{
public:
    Tournament(OptimizationFunction<std::vector<double> > &function, int n);
    size_t chooseOne(std::vector< std::vector<double> > population);

private:
    std::random_device rd;
    std::mt19937 eng;
    int n;
};


#endif //HOLA_TOURNAMENT_H
