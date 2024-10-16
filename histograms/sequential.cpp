#include "sequential.h"

std::vector<int> Sequential::calculate(const int* input, const int buckets,
                                       const int input_size) {
  std::vector<int> histogram(buckets, 0);

  for(int idx = 0; idx < input_size; idx++) {
    histogram[input[idx] - 1]++;
  }

  return histogram;
}
