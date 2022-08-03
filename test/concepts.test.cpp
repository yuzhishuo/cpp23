#include <gtest/gtest.h>

#include <concepts>
#include <string>
#include <vector>

template <typename T>
concept Containersable = requires(T a) {
  { std::vector<T>{}.at(1) }
  ->std::convertible_to<T&>;
};

struct Me {
 private:
  Me& operator=(Me&) = delete;
  Me(Me&&) = delete;
  Me(Me&) = delete;
  Me() = delete;
};

template <Containersable T>
[[noreturn]] T F(T) {
  throw "";
}

template <Containersable T>
[[noreturn]] T M() {
  exit(-1);
}

TEST(CONCEPT, TEST1) {
  using std::operator""s;

  EXPECT_EQ(typeid(F("Hi"s)), typeid(std::string));
  EXPECT_EQ(typeid(M<Me>()), typeid(Me));
  EXPECT_DEATH(M<Me>(), "");
}

#include <type_traits>

template <typename T>
concept integral = std::is_integral_v<T>;

template <integral T>
T integralAdd(T a, T b) noexcept {
  return a + b;
}

auto intergralAdd1(integral auto a, integral auto b) noexcept
    -> decltype(a + b) {
  return a + b;
}

template <typename T>
requires integral<T> T intergralAdd2(T a, T b) noexcept {
  return a + b;
}

static auto intergralAdd3 = []<integral T>(T a, T b) -> auto { return a + b; };

TEST(CONCEPT, TEST2) {
  EXPECT_EQ(integralAdd(1, 2), 3);
  EXPECT_EQ(intergralAdd1(1, 3), 4);
  EXPECT_EQ(intergralAdd2(1, 3), 4);
  EXPECT_EQ(intergralAdd3(1, 4), 5);
}