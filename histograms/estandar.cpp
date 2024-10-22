#include "estandar.h"
#include <mutex>
#include <thread>

std::mutex mtx_estandar;
void calcular_histograma(int* histograma, int inicio, int fin) {
  for(int idx = inicio; idx < fin; idx++) {
    std::lock_guard<std::mutex> lock(mtx_estandar);
    histograma[randomInput[idx] - 1]++;
  }
}

std::vector<int> Estandar::calculate(const int* input, const int buckets,
                                     const int input_size) {
  int histograma[MAXIMO_VALOR] = {0};
  const int num_hilos = std::thread::hardware_concurrency();
  std::vector<std::thread> hilos(num_hilos);
  int chunk = NUMERO_ELEMENTOS / num_hilos;

  for(int idx = 0; idx < num_hilos; idx++) {
    int inicio = chunk * idx;
    int fin = (idx == num_hilos - 1) ? NUMERO_ELEMENTOS : idx * chunk;
    hilos[idx] =
        std::thread(calcular_histograma, std::ref(histograma), inicio, fin);
  }

  for(auto& hilo : hilos) {
    hilo.join();
  }

  return histograma;
}