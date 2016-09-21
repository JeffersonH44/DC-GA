//
// Created by jefferson on 3/09/16.
//

#include "GaussianMutator.h"
#include "../../random/GaussianRandom.h"

GaussianMutator::GaussianMutator(double mean, double std, double prob) :
    eng(rd()),
    ur(eng, 0.0, 1.0),
    gr(eng, mean, std)
{
    this->prob = prob;
    this->arguments = 1;
}

std::vector<std::vector<double>> GaussianMutator::apply(std::vector<std::vector<double>> individuals) {
    std::vector<double> ind = individuals[0];
    std::vector<double> newInd(ind);
    double rand;
    for(size_t i = 0; i < ind.size(); ++i) {
        rand = ur.generate();
        if(rand < this->prob) {
            newInd[i] = ind[i] + gr.generate();
        }
    }

    std::vector<std::vector<double>> toReturn;
    toReturn.push_back(newInd);

    return toReturn;
}
