#ifndef SEQUENTIAL_H
#define SEQUENTIAL_H

#include "histogram.h"

class Sequential : Histogram {
 public:
  std::vector<int> calculate(const int*, const int, const int) override;
};

#endif  // SEQUENTIAL_H
