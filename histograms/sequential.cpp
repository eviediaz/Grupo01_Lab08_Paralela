#include "sequential.h"

std::vector<int> Sequential::calculate(const int* randomInput, const int maximo_valor,
                                       const int numero_elementos) {
  std::vector<int> histogram(maximo_valor, 0);

  for(int idx = 0; idx < numero_elementos; idx++) {
    histogram[randomInput[idx] - 1]++;
  }

  return histogram;
}
