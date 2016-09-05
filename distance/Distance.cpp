//
// Created by jefferson on 5/09/16.
//

#include <cstddef>

#include "Distance.h"

double Distance::tanimoto(std::vector<double> a, std::vector<double> b) {
    double p, q, m;
    p = q = m = 0.0;
    for(size_t i = 0; i < a.size(); ++i) {
        p += a[i];
        q += b[i];
        m += std::min(a[i], b[i]);
    }
    return (p + q - 2 * m) / (p + q - m);
}

double Distance::intersection(std::vector<double> a, std::vector<double> b) {
    double ans = 0.0;
    for(size_t i = 0; i < a.size(); ++i) {
        ans += std::min(a[i], b[i]);
    }
    return 1 - ans;
}
