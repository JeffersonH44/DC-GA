//
// Created by jefferson on 29/11/16.
//

#include "LinearXOver.h"

double** linearxover::apply(double **individuals, double **toReturn, int dimension,
                            double *randoms, int size, int &current) {
    double c = rd::random(0.0, 1.0, randoms, size, current);
    double c1 = 1.0 - c;

    #pragma acc loop vector
    for(int i = 0; i < dimension; ++i) {
        toReturn[0][i] = individuals[0][i] * c + individuals[1][i] * c1;
        toReturn[1][i] = individuals[0][i] * c1 + individuals[1][i] * c;
    }
    //toReturn[0] = ind1;
    //toReturn[1] = ind2;
    return toReturn;
}
