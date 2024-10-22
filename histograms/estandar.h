#ifndef ESTANDAR_H
#define ESTANDAR_H

#include "histogram.h"

class Estandar : Histogram {
    public:
    std::vector<int> calculate(const int*, const int, const int) override;
};

#endif //ESTANDAR_H