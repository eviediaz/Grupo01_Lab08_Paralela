#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <vector>

class Histogram {
 public:
  virtual std::vector<int> calculate(const int*, const int, const int) = 0;
  // Histogram(const int, const int);
  // private:
  //     std::vector<int> histogram(buckets,0);
};

#endif  // HISTOGRAM_H
