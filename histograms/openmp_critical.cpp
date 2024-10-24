#include "openmp_critical.h"

std::vector<int> OpenmpAtomic::calculate(const int* random_input,
                                         const int maximo_valor,
                                         const int numero_elementos) {
    std::vector<int> histograma(maximo_valor, 0);

    #pragma omp parallel for
    for(int idx = 0; idx < numero_elementos; idx++) {
        #pragma omp critical
        histograma[random_input[idx] - 1]++;
    }

  return std::vector<int>();
}