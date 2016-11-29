//
// Created by jefferson on 29/11/16.
//

#ifndef DC_GA_HIPERCUBE_H
#define DC_GA_HIPERCUBE_H

namespace hipercube {
    #pragma acc routine vector
    double* repair(double *val, double low, double high, int dimension);
    double** getRandomIndividuals(int individuals, int dimension, double low, double high);
}


#endif //DC_GA_HIPERCUBE_H
