#ifndef OPENMP_LOCKGUARD_H
#define OPENMP_LOCKGUARD_H

#include "histogram.h"

class OpenmpLockGuard: Histogram {
    public:
    std::vector<int> calculate(const int*, const int, const int) override;
};


#endif // OPENMP_LOCKGUARD