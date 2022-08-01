#include <gtest/gtest.h>

struct A {
  char8_t a;
  int b;
};

struct B {
  unsigned char a;
  int b;
};

TEST(CHAR8_T, TEST) {
  // char8_t - UTF-8 字符表示的类型，要求大到足以表示任何 UTF-8 编码单元（ 8
  // 位）。它与 unsigned char 具有相同的大小、符号性和对齐（从而与 char 和
  // signed char 具有相同的大小和对齐），但它是独立的类型。
  EXPECT_EQ(sizeof(char8_t), 1UL);
  EXPECT_EQ(sizeof(A), sizeof(B));
  EXPECT_EQ(sizeof(unsigned char), sizeof(char8_t));
}