#include "openmp_reduction.h"

std::vector<int> OpenmpReduction::calculate(const int* random_input,
                                            const int maximo_valor,
                                            const int numero_elementos) {
  int histograma[maximo_valor] = {0};
#pragma omp parallel for reduction(+ : histograma[ : maximo_valor])
  for(int idx = 0; idx < numero_elementos; idx++) {
    histograma[random_input[idx] - 1]++;
  }

  return std::vector<int>(maximo_valor, 0) ;
}