#include "openmp_atomic.h"

#include <atomic>
#include <thread>

std::vector<int> OpenmpAtomic::calculate(const int* random_input,
                                         const int maximo_valor,
                                         const int numero_elementos) {
  std::atomic<int> histograma[maximo_valor] = {};

#pragma omp parallel for
  for(int idx = 0; idx < numero_elementos; idx++) {
    histograma[random_input[idx] - 1]++;
  }

  return std::vector<int>(maximo_valor, 0);
}