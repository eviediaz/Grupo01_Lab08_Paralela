#include "gtest/gtest.h"

TEST(PrimerTest, pruebaOK){
  EXPECT_EQ(1,1);
}

TEST(PrimerTest, pruebaFail){
  EXPECT_EQ(1,0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
