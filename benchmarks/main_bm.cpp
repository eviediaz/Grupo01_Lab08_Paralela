#include <benchmark/benchmark.h>

#include <mutex>
#include <new>
#include <random>
#include <thread>

#include "sequential.h"
#include "estandar.h"
#include "estandar_reduction.h"
#include "openmp_reduction.h"

static int* randomInput = nullptr;
static const int MAXIMO_VALOR = 5;
static const int NUMERO_ELEMENTOS = 100000000;


// Funciones de inicializacion
void inicializa() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> uni_dis(1, MAXIMO_VALOR);

  if(randomInput == nullptr) {
    randomInput = new int[NUMERO_ELEMENTOS];
    for(int i = 0; i < NUMERO_ELEMENTOS; ++i) {
      randomInput[i] = uni_dis(gen);
    }
  }
}

void finaliza() {
  if(randomInput != nullptr) {
    delete[] randomInput;
    randomInput = nullptr;
  }
}


// -- FUNCIONES BENCHMARK --
static void BM_secuencial(benchmark::State& state) {
  Sequential histogramCalculator;

  for(auto _ : state) {
    auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);
    benchmark::DoNotOptimize(histograma);
  }
}

static void BM_estandar(benchmark::State& state) {
  Estandar calculadoraHistograma_Estandar;
  
  for(auto _ : state) {
    auto histograma = calculadoraHistograma_Estandar.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);
  }
}

static void BM_estandar_reduction(benchmark::State& state) {
  Estandar_Reduction calculadoraHistograma_EstandarReduction;
  for(auto _ : state) {
    calculadoraHistograma_EstandarReduction.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);
  }
}

static void BM_openmp_reduction(benchmark::State& state) {
  OpenmpReduction calculadoraHistograma_OpenMPReduction;
  for(auto _ : state) {
    calculadoraHistograma_OpenMPReduction.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);
  }
}

static void BM_openmp_atomic(benchmark::State& state) {
  std::atomic<int> histograma[MAXIMO_VALOR] = {};  // default

  for(auto _ : state) {
#pragma omp parallel for
    for(int idx = 0; idx < NUMERO_ELEMENTOS; idx++) {
      histograma[randomInput[idx] - 1]++;
    }
  }
}

static void BM_openmp_lock_guard(benchmark::State& state) {
  int histograma[MAXIMO_VALOR] = {0};
  std::mutex mtx;

  for(auto _ : state) {
#pragma omp parallel for
    for(int idx = 0; idx < NUMERO_ELEMENTOS; idx++) {
      std::lock_guard<std::mutex> lock(mtx);
      histograma[randomInput[idx] - 1]++;
    }
  }
}

static void BM_openmp_lock_unlock(benchmark::State& state) {
  int histograma[MAXIMO_VALOR] = {0};
  std::mutex mtx;

  for(auto _ : state) {
#pragma omp parallel for
    for(int idx = 0; idx < NUMERO_ELEMENTOS; idx++) {
      mtx.lock();
      histograma[randomInput[idx] - 1]++;
      mtx.unlock();
    }
  }
}

static void BM_openmp_critical(benchmark::State& state) {
  int histograma[MAXIMO_VALOR] = {0};

  for(auto _ : state) {
#pragma omp parallel for
    for(int idx = 0; idx < NUMERO_ELEMENTOS; idx++) {
#pragma omp critical
      histograma[randomInput[idx] - 1]++;
    }
  }
}

static void BM_openmp_ompatomic(benchmark::State& state) {
  int histograma[MAXIMO_VALOR] = {0};

  for(auto _ : state) {
#pragma omp parallel for
    for(int idx = 0; idx < NUMERO_ELEMENTOS; idx++) {
#pragma omp atomic
      histograma[randomInput[idx] - 1]++;
    }
  }
}

// Agregar funciones a BenchMark
BENCHMARK(BM_secuencial)->UseRealTime()->Unit(benchmark::kMillisecond);
BENCHMARK(BM_estandar)->UseRealTime()->Unit(benchmark::kMillisecond);
BENCHMARK(BM_estandar_reduction)->UseRealTime()->Unit(benchmark::kMillisecond);
BENCHMARK(BM_openmp_atomic)->UseRealTime()->Unit(benchmark::kMillisecond);
BENCHMARK(BM_openmp_reduction)->UseRealTime()->Unit(benchmark::kMillisecond);
BENCHMARK(BM_openmp_lock_guard)->UseRealTime()->Unit(benchmark::kMillisecond);
BENCHMARK(BM_openmp_lock_unlock)->UseRealTime()->Unit(benchmark::kMillisecond);
BENCHMARK(BM_openmp_critical)->UseRealTime()->Unit(benchmark::kMillisecond);
BENCHMARK(BM_openmp_ompatomic)->UseRealTime()->Unit(benchmark::kMillisecond);

int main(int argc, char** argv) {
  inicializa();
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
  finaliza();
}
