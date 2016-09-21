//
// Created by jefferson on 5/09/16.
//

#ifndef HOLA_DISTANCE_H
#define HOLA_DISTANCE_H


#include <vector>
#include <algorithm>

class Distance {
public:
    static double tanimoto(std::vector<double> a, std::vector<double> b);
    static double intersection(std::vector<double> a, std::vector<double> b);
};


#endif //HOLA_DISTANCE_H
