//
// Created by jefferson on 29/11/16.
//

#ifndef DC_GA_RASTRIGIN_H
#define DC_GA_RASTRIGIN_H

#include <cmath>

namespace rastrigin {
    #pragma acc routine seq
    double apply(double val);

    #pragma acc routine vector
    double apply(double *ind, int dimension);
}

#endif //DC_GA_RASTRIGIN_H
