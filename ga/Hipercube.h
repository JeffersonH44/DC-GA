//
// Created by jefferson on 3/09/16.
//

#ifndef HOLA_HIPERCUBE_H
#define HOLA_HIPERCUBE_H

#include "Space.h"

class Hipercube : public Space<std::vector<double>> {
private:
    std::vector<double> min, max;
public:
    Hipercube(std::vector<double> min, std::vector<double> max);
    std::vector<double> repair(std::vector<double> val);
};


#endif //HOLA_HIPERCUBE_H
