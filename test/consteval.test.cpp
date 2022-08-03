#include "consteval.test.h"

#include <gtest/gtest.h>

TEST(CONSTEVAL, TEST1) {
  constexpr bool res = is_int(1);
  EXPECT_TRUE(res);
}