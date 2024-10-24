#include <gtest/gtest.h>

#include <random>

#include "sequential.h"
#include "estandar.h"
#include "estandar_reduction.h"
#include "openmp_reduction.h"
#include "openmp_atomic.h"
#include "openmp_lockGuard.h"
#include "openmp_lockUnlock.h"


static int* randomInput = nullptr;
static const int MAXIMO_VALOR = 5;
static const int NUMERO_ELEMENTOS = 100000000;

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

TEST(SequentialTest, pruebaOK) {
  Sequential histogramCalculator;
  
  auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR,
                                                  NUMERO_ELEMENTOS);

  int acum = 0;
  for(auto puntuacion : histograma) acum += puntuacion;
  EXPECT_EQ(acum, NUMERO_ELEMENTOS);
}

TEST(EstandarTest, pruebaOK1) {
   Estandar histograma_estandar;
   auto histograma_paralelo = histograma_estandar.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);
  std::cout << "numero elementos" << histograma_paralelo.size() << std::endl;
  int acum = 0;
  for(auto puntuacion : histograma_paralelo) acum += puntuacion;
  EXPECT_EQ(acum, NUMERO_ELEMENTOS);
}

TEST(EstandarTest_reduct, pruebaOK2) {
  Estandar_Reduction histograma_estandar_reduction;
  auto histograma_paralelo = histograma_estandar_reduction.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);

  int acum = 0;
  for(auto puntuacion : histograma_paralelo) acum += puntuacion;
  EXPECT_EQ(acum, NUMERO_ELEMENTOS);
}

TEST(Estandar_TEST, prueba1) {
    Sequential histogramCalculator;
    auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR,
                                                  NUMERO_ELEMENTOS);
    Estandar histograma_estandar;
    auto histograma_paralelo = histograma_estandar.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);

    for (int i = 0; i < 6; i++)
    {
      std::cout << "Histograma1: " << histograma[i] << " " << "Histograma2: " << histograma_paralelo[i] << std::endl;
    }
    
    for (int i = 0; i < MAXIMO_VALOR; i++)
    {
      EXPECT_EQ(histograma[i], histograma_paralelo[i]);
    }

}

TEST(Estandar_Reduction_TEST, prueba2) {
    Sequential histogramCalculator;
    auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR,
                                                  NUMERO_ELEMENTOS);
    Estandar_Reduction histograma_estandar_reduction;
    auto histograma_paralelo = histograma_estandar_reduction.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);

    for (int i = 0; i < MAXIMO_VALOR; i++)
    {
      EXPECT_EQ(histograma[i], histograma_paralelo[i]);
    }

}




TEST(OPENMP_ATOMIC_TEST, prueba3) {
    Sequential histogramCalculator;
    auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR,
                                                  NUMERO_ELEMENTOS);
    OpenmpAtomic histograma_openMP_Atomic;
    auto histograma_paralelo = histograma_openMP_Atomic.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);

    for (int i = 0; i < MAXIMO_VALOR; i++)
    {
      EXPECT_EQ(histograma[i], histograma_paralelo[i]);
    }
}

TEST(OPENMP_LOCKGUARD_TEST, prueba4) {
    Sequential histogramCalculator;
    auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR,
                                                  NUMERO_ELEMENTOS);
    OpenmpLockGuard histograma_OpenmpLockGuard;
    auto histograma_paralelo = histograma_OpenmpLockGuard.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);

    for (int i = 0; i < MAXIMO_VALOR; i++)
    {
      EXPECT_EQ(histograma[i], histograma_paralelo[i]);
    }
}

TEST(OPENMP_LOCKUNLOCK_TEST, prueba5) {
    Sequential histogramCalculator;
    auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR,
                                                  NUMERO_ELEMENTOS);
    OpenmpLockUnlock histograma_OpenmpLockUnlock;
    auto histograma_paralelo = histograma_OpenmpLockUnlock.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);

    for (int i = 0; i < MAXIMO_VALOR; i++)
    {
      EXPECT_EQ(histograma[i], histograma_paralelo[i]);
    }
}

TEST(REDUCTION_TEST, prueba6) {
    Sequential histogramCalculator;
    auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR,
                                                  NUMERO_ELEMENTOS);
    OpenmpReduction histograma_OpenmpReduction;
    auto histograma_paralelo = histograma_OpenmpReduction.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);

    for (int i = 0; i < MAXIMO_VALOR; i++)
    {
      EXPECT_EQ(histograma[i], histograma_paralelo[i]);
    }
}

int main(int argc, char** argv) {
  inicializa();
  ::testing::InitGoogleTest(&argc, argv);
  auto ret = RUN_ALL_TESTS();
  finaliza();
  return ret;
}
