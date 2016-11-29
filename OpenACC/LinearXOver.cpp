//
// Created by jefferson on 5/09/16.
//

#include "LinearXOver.h"

LinearXOver::LinearXOver(size_t dimension):
    eng(rd()),
    ur(eng, 0.0, 1.0)
{
    this->arguments = 2;
    this->dimension = dimension;
}

double** LinearXOver::apply(double **individuals, double **toReturn) {
    //double **toReturn = new double*[2];
    size_t size = this->dimension;
    //double *ind1 = new double[size];
    //double *ind2 = new double[size];
    double c = ur.generate();
    double c1 = 1.0 - c;

    #pragma acc loop vector
    for(size_t i = 0; i < size; ++i) {
        toReturn[0][i] = individuals[0][i] * c + individuals[1][i] * c1;
        toReturn[1][i] = individuals[0][i] * c1 + individuals[1][i] * c;
    }
    //toReturn[0] = ind1;
    //toReturn[1] = ind2;
    return toReturn;
}
