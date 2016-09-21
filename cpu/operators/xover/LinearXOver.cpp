//
// Created by jefferson on 5/09/16.
//

#include "LinearXOver.h"

LinearXOver::LinearXOver():
    eng(rd()),
    ur(eng, 0.0, 1.0)
{
    this->arguments = 2;
}

std::vector<std::vector<double>> LinearXOver::apply(std::vector<std::vector<double>> individuals) {
    size_t size = individuals[0].size();
    std::vector<double> ind1(size, 0.0), ind2(size, 0.0);
    double c = ur.generate();
    double c1 = 1.0 - c;
    for(size_t i = 0; i < size; ++i) {
        ind1[i] = individuals[0][i] * c + individuals[1][i] * c1;
        ind2[i] = individuals[0][i] * c1 + individuals[1][i] * c;
    }

    std::vector<std::vector<double>> toReturn;
    toReturn.push_back(ind1);
    toReturn.push_back(ind2);

    return toReturn;
}
