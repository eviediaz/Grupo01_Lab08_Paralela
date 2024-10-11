function(ConfigureTest CMAKE_TEST_NAME)
  ADD_EXECUTABLE(${CMAKE_TEST_NAME} ${ARGN})
  TARGET_LINK_LIBRARIES(${CMAKE_TEST_NAME} experiments ${DEPS} gtest)
  ADD_TEST(NAME ${CMAKE_TEST_NAME} COMMAND ${CMAKE_TEST_NAME})
endfunction()

INCLUDE_DIRECTORIES(../experiments)

ConfigureTest(validation_test
  validation_test.cpp
)
