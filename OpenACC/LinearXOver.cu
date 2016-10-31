//
// Created by jefferson on 21/09/16.
//

#include "LinearXOver.h"

LinearXOver::LinearXOver() {
    this->arguments = 2;
}

std::vector<thrust::device_vector<double>> LinearXOver::apply(std::vector<thrust::device_vector<double>> &individuals) {
    size_t size = individuals[0].size();
    thrust::device_vector<double> ind1(size, 0.0), ind2(size, 0.0);
    double c = ((double) rand() / (RAND_MAX));
    thrust::transform(individuals[0].begin(), individuals[0].end(), individuals[1].begin(), ind1.begin(), linear_xover(c));
    thrust::transform(individuals[0].begin(), individuals[0].end(), individuals[1].begin(), ind2.begin(), linear_xover(1.0 - c));

    std::vector< thrust::device_vector<double> > toReturn;
    toReturn.push_back(ind1);
    toReturn.push_back(ind2);

    return toReturn;
}