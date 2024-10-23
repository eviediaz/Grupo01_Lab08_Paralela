#ifndef OPENMP_REDUCTION_H
#define OPENMP_REDUCTION_H

#include "histogram.h"

class OpenmpReduction: Histogram {
    public:
    std::vector<int> calculate(const int*, const int, const int) override;
};


#endif // OPENMP_REDUCTION_H