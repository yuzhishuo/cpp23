#include <gtest/gtest.h>

#include <array>
#include <list>
#include <vector>

#if __has_include(<span>)

#include <span>
#if __cpp_lib_span

TEST(SPAN, TEST1) {
  constexpr std::span<int> sp;  // default constructor

  EXPECT_FALSE(sp.size());
  EXPECT_EQ(sp.extent, std::numeric_limits<std::size_t>::max());
  static_assert(!sp.size_bytes());
  static_assert(!std::size(sp));
}

TEST(SPAN, TEST2) {
  constexpr int ar[] = {1, 2, 3, 4};  //

  std::span sp{ar};  // why isnt sp  constexpr var;

  constexpr size_t sz = sp.size();

  static_assert(sz == std::size(ar));
  static_assert(sp.size_bytes() == sizeof(ar));
}

TEST(SPAN, TEST3) {
  constexpr std::array ar = {1, 2, 3, 4};  //

  std::span sp{ar};  // why isnt sp  constexpr var;

  constexpr size_t sz = sp.size();

  static_assert(sz == std::size(ar));
  static_assert(sp.size_bytes() == sizeof(ar));
  static_assert(sp.extent == std::size(ar));
}

TEST(SPAN, TEST4) {
  // error
  // constexpr std::vector<char> ar{10, 'a'};  //

  // std::span sp{ar};  // why isnt sp  constexpr var;

  // constexpr size_t sz = sp.size();

  // static_assert(sz == std::size(ar));
  // static_assert(sp.size_bytes() == sizeof(ar));
}

TEST(SPAN, TEST5) {
  std::vector<char> ar{10, 'a'};  //
  std::span sp{std::begin(ar) + 1, 4};
  EXPECT_EQ(sp.size(), 4);
  auto sp1 = sp.subspan(1, 2);

  EXPECT_EQ(sp1.size(), 2);
  EXPECT_EQ(sp.extent, std::numeric_limits<std::size_t>::max());
  EXPECT_EQ(sp1.extent, std::numeric_limits<std::size_t>::max());

  auto sp2 = sp.first(1);
  EXPECT_EQ(sp2.size(), 1);

  auto sp3 = sp.last(1);
  EXPECT_EQ(sp2.size(), 1);
}

#endif
#endif