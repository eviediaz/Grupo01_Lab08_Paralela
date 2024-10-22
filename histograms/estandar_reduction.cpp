#include "estandar_reduction.h"
#include<mutex>
#include<thread>

void calcular_local_histograma(int* local_histograma, int inicio, int fin, int* randomInput) {
  for(int idx = inicio; idx < fin; idx++) {
    local_histograma[randomInput[idx] - 1]++;
  }
}

std::vector<int> Estandar_Reduction::calculate(const int* random_input,
                                               const int maximo_valor,
                                               const int numero_elementos) {
  std::vector<int> histograma(maximo_valor, 0);
  const int num_hilos = std::thread::hardware_concurrency();
  std::vector<std::vector<int>> local_histograma(num_hilos, std::vector<int>(maximo_valor, 0));
  std::vector<std::thread> hilos(num_hilos);
  int chunk = numero_elementos / num_hilos;

  for(int idx = 0; idx < num_hilos; idx++) {
    int inicio = chunk * idx;
    int fin = (idx == num_hilos - 1) ? numero_elementos : idx * chunk;
    hilos[idx] = std::thread(calcular_local_histograma,
                             std::ref(local_histograma[idx]), inicio, fin, random_input);
  }

  for(auto& hilo : hilos) {
    hilo.join();
  }

  for(int idx = 0; idx < num_hilos; idx++) {
    for(int idy = 0; idy < maximo_valor; idy++) {
      histograma[idy] += local_histograma[idx][idy];
    }
  }

  return histograma;
}