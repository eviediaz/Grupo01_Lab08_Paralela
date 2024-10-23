#include "openmp_lockGuard.h"

#include <mutex>

std::mutex mtx;
std::vector<int> OpenmpLockGuard::calculate(const int* random_input,
                                            const int maximo_valor,
                                            const int numero_elementos) {
  std::vector<int> histograma(maximo_valor, 0);
  
#pragma omp parallel for
  for(int idx = 0; idx < numero_elementos; idx++) {
    std::lock_guard<std::mutex> lock(mtx);
    histograma[random_input[idx] - 1]++;
  }

  return histograma;
}