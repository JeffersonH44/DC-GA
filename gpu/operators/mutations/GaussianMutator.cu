//
// Created by jefferson on 21/09/16.
//

#include "GaussianMutator.h"

#include <iostream>

GaussianMutator::GaussianMutator(double mean, double std, double prob) :
        ur(0.0, 1.0),
        gr(mean, std)
{
    this->prob = prob;
    this->arguments = 1;
}

thrust::host_vector< thrust::device_vector<double> > GaussianMutator::apply(thrust::host_vector< thrust::device_vector<double> > &individuals) {
    thrust::device_vector<double> newInd(individuals[0].begin(), individuals[0].end());
    thrust::device_vector<double> probs = ur.generate(static_cast<int>(newInd.size()));
    thrust::device_vector<double> mutation = gr.generate(static_cast<int>(newInd.size()));

    thrust::transform(probs.begin(), probs.end(), mutation.begin(), mutation.begin(), allow_mut(this->prob));
    thrust::transform(newInd.begin(), newInd.end(), mutation.begin(), newInd.begin(), thrust::plus<double>());
    thrust::host_vector< thrust::device_vector<double> > toRet(1, newInd);
    return toRet;
}