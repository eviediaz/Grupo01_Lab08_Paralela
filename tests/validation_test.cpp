#include <gtest/gtest.h>

#include <random>

#include "sequential.h"
#include "estandar.h"
#include "estandar_reduction.h"
#include "openmp_reduction.h"
#include "openmp_atomic.h"
#include "openmp_lockGuard.h"
#include "openmp_lockUnlock.h"
#include "openmp_critical.h"
#include "openmp_ompatomic.h"

static int* randomInput = nullptr;
static const int MAXIMO_VALOR = 5;
static const int NUMERO_ELEMENTOS = 100000000;
auto histograma;

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
  histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR,
                                                  NUMERO_ELEMENTOS);
  int acum = 0;
  for(auto puntuacion : histograma) acum += puntuacion;
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
    Estandar histograma_estandar;
    auto histograma_paralelo = histograma_estandar.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);

    for (int i = 0; i < MAXIMO_VALOR; i++)
    {
      EXPECT_EQ(histograma[i], histograma_paralelo[i]);
    }

}

TEST(Estandar_Reduction_TEST, prueba2) {
    Estandar_Reduction histograma_estandar_reduction;
    auto histograma_paralelo = histograma_estandar_reduction.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);

    for (int i = 0; i < MAXIMO_VALOR; i++)
    {
      EXPECT_EQ(histograma[i], histograma_paralelo[i]);
    }

}

TEST(OPENMP_LOCKGUARD_TEST, prueba3) {
    OpenmpLockGuard histograma_OpenmpLockGuard;
    auto histograma_paralelo = histograma_OpenmpLockGuard.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);

    for (int i = 0; i < MAXIMO_VALOR; i++)
    {
      EXPECT_EQ(histograma[i], histograma_paralelo[i]);
    }
}

TEST(OPENMP_LOCKUNLOCK_TEST, prueba4) {
    OpenmpLockUnlock histograma_OpenmpLockUnlock;
    auto histograma_paralelo = histograma_OpenmpLockUnlock.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);

    for (int i = 0; i < MAXIMO_VALOR; i++)
    {
      EXPECT_EQ(histograma[i], histograma_paralelo[i]);
    }
}

TEST(CRITICAL_TEST, prueba5) {
    Openmp_Critical histograma_Openmp_Critical;
    auto histograma_paralelo = histograma_Openmp_Critical.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);

    for (int i = 0; i < MAXIMO_VALOR; i++)
    {
      EXPECT_EQ(histograma[i], histograma_paralelo[i]);
    }
}
TEST(OPENMP_OPMATOMIC_TEST, prueba6) {
    Openmp_OmpAtomic histograma_Openmp_OmpAtomic;
    auto histograma_paralelo = histograma_Openmp_OmpAtomic.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);

    for (int i = 0; i < MAXIMO_VALOR; i++)
    {
      EXPECT_EQ(histograma[i], histograma_paralelo[i]);
    }
}
TEST(OPENMP_ATOMIC_TEST, prueba7) {
    OpenmpAtomic histograma_openMP_Atomic;
    auto histograma_paralelo = histograma_openMP_Atomic.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);

    for (int i = 0; i < MAXIMO_VALOR; i++)
    {
      EXPECT_EQ(histograma[i], histograma_paralelo[i]);
    }
}
TEST(REDUCTION_TEST, prueba8) {
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
