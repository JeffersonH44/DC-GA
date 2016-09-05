//
// Created by jefferson on 3/09/16.
//

#include <cstddef>
#include "Hipercube.h"


Hipercube::Hipercube(std::vector<double> min, std::vector<double> max) {
    this->min = min;
    this->max = max;
}

std::vector<double> Hipercube::repair(std::vector<double> val) {
    std::vector<double> ret(val);

    for(size_t i = 0; i < ret.size(); ++i) {
        if(ret[i] < this->min[i]) {
            ret[i] = this->min[i];
        } else if(ret[i] > this->max[i]) {
            ret[i] = this->max[i];
        }
    }

    return ret;
}


