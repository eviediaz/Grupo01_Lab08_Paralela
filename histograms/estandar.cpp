#include "estandar.h"
#include <mutex>
//#include <thread>

std::mutex mtx_estandar;
void calcular_histograma(std::vector<int>& histograma, int inicio, int fin, int* random_input) {
  for(int idx = inicio; idx < fin; idx++) {
    std::lock_guard<std::mutex> lock(mtx_estandar);
    histograma[random_input[idx] - 1]++;
  }
}

std::vector<int> Estandar::calculate(const int* random_input, const int maximo_valor,
                                     const int numero_elementos) {
  std::vector<int> histograma(maximo_valor, 0);
  const int num_hilos = std::thread::hardware_concurrency();
  std::vector<std::thread> hilos(num_hilos);
  int chunk = numero_elementos / num_hilos;

  for(int idx = 0; idx < num_hilos; idx++) {
    int inicio = chunk * idx;
    int fin = (idx == num_hilos - 1) ? numero_elementos : idx * chunk;
    hilos[idx] =
        std::thread(calcular_histograma, std::ref(histograma), inicio, fin, random_input);
  }

  for(auto& hilo : hilos) {
    hilo.join();
  }

  return histograma;
}