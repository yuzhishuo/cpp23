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

TEST(CONCEPT, TEST) {
  using std::operator""s;

  EXPECT_EQ(typeid(F("Hi"s)), typeid(std::string));
  EXPECT_EQ(typeid(M<Me>()), typeid(Me));
  EXPECT_DEATH(M<Me>(), "");
}