#include "openmp_lockUnlock.h"

#include <mutex>

std::vector<int> OpenmpLockUnlock::calculate(const int* random_input,
                                             const int maximo_valor,
                                             const int numero_elementos) {
  std::mutex mtx;
  std::vector<int> histograma(maximo_valor, 0);

#pragma omp parallel for
  for(int idx = 0; idx < numero_elementos; idx++) {
    mtx.lock();
    histograma[random_input[idx] - 1]++;
    mtx.unlock();
  }
  return histograma;
}
