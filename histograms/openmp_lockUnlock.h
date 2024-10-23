#ifndef OPENMP_LOCKUNLOCK_H
#define OPENMP_LOCKUNLOCK_H

#include "histogram.h"

class OpenmpLockUnlock: Histogram {
    public:
    std::vector<int> calculate(const int*, const int, const int) override;
};


#endif // OPENMP_LOCKUNLOCK_H