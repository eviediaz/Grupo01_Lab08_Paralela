#ifndef ESTANDAR_REDUC_H
#define ESTANDAR_REDUC_H

#include "histogram.h"

class Estandar_Reduction : Histogram {
    public:
    std::vector<int> calculate(const int*, const int, const int) override;
};

#endif //ESTANDAR_REDUC_H