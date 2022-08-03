#include <gtest/gtest.h>

#include <algorithm>
#include <type_traits>

consteval int sqrt(const int x, const int y) {
  if (!x || !y) {
    return 0;
  }

#if __cplusplus > 202002L  // c++23 suport
  if
    consteval { return std::sqrt(x, y); }
#endif
  return x * x;
}

const char* GetStringDyn() { return "dynamic init"; }
constexpr const char* GetString(bool constInit) {
  return constInit ? "constant init" : GetStringDyn();
}

// constinit var must static or thread_local
constinit const char* a = GetString(true);
constinit auto res = sqrt(0, 1);
TEST(CONSTEXPR, TEST3) { EXPECT_EQ(res, 0); }

TEST(CONSTEXPR, TEST1) {
  if constexpr (std::is_integral_v<decltype(1)>) {
    EXPECT_EQ(0, 0);
  } else {
    EXPECT_NE(0, 0);
  }
}

TEST(CONSTEXPR, TEST2) {
  if constexpr (constexpr auto is_int = std::is_integral_v<decltype(1)>;
                is_int) {
    EXPECT_EQ(0, 0);
  } else {
    EXPECT_NE(0, 0);
  }
}
