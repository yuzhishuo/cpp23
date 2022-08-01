#include <gtest/gtest.h>

#include <iostream>
#include <string>

struct S {
  int a;
  int b;
};

#define SDEF(sname, ...) S sname __VA_OPT__(= {__VA_ARGS__})

// __VA_OPT__ 回根据 __VA_ARGS_ 是否为空来决定 逗号
// 是否出现，因此可以解决LOG("hello world") 的调用问题。
#define LOG(msg, ...) std::string(msg __VA_OPT__(, ) __VA_ARGS__)

TEST(VAOPT, TEST) {
  SDEF(foo);        // replaced by S foo;
  SDEF(bar, 1, 2);  // replaced by S bar = { 1, 2 };

  EXPECT_EQ(bar.a, 1);
  EXPECT_EQ(LOG("HIWORLD", 3), "HIW");
  EXPECT_EQ(LOG("Hi"), "Hi");
}