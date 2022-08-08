#include <gtest/gtest.h>

#include <iostream>
#include <thread>

#if __cpp_lib_jthread
using namespace std;
void thread_func(std::stop_token token) {
  int data = 0;
  while (!token.stop_requested()) {
    printf("%d\n", data);
    data++;
    std::this_thread::sleep_for(1s);
  }
  printf("Exit\n");
}

TEST(JTHREAD, TEST1) {
  jthread hh(thread_func);

  EXPECT_TRUE(hh.request_stop());

  this_thread::sleep_for(4s);

  std::stop_callback(hh.get_stop_token(), []() {
    std::cout << "TEST1 stop_token call back" << std::endl;
  });
}

TEST(JTHREAD, TEST2) {
  std::stop_source src;  // owner token

  std::stop_token token{src.get_token()};

  // EXPECT_TRUE(token.stop_possible());

  std::stop_callback(src.get_token(),
                     []() { std::cout << "TEST2 unshow" << std::endl; });

  EXPECT_TRUE(src.request_stop());
  EXPECT_FALSE(src.request_stop());
  // EXPECT_FALSE(token.stop_possible());
  std::stop_callback(src.get_token(), []() {
    std::cout << "TEST2 stop_token call back" << std::endl;
  });
}

TEST(JTHREAD, TEST3) {
  std::stop_source src;  // owner token

  std::stop_token token{src.get_token()};

  // EXPECT_TRUE(token.stop_possible());

  // TODO: stop_callback 应当在 request_stop 后调用, 否则不执行
  std::stop_callback(src.get_token(),
                     []() { std::cout << "TEST2 unshow" << std::endl; });

  EXPECT_TRUE(src.request_stop());
}

TEST(JTHREAD, TEST4) {
  jthread hh(thread_func);

  std::stop_callback(hh.get_stop_token(),
                     []() { std::cout << "TEST1 unshow" << std::endl; });

  EXPECT_TRUE(hh.request_stop());
}

TEST(JTHREAD, TEST5) {
  jthread hh(thread_func);

  std::stop_callback  cc (hh.get_stop_token(),
                     []() { std::cout << "TEST1 show" << std::endl; });

  EXPECT_TRUE(hh.request_stop());
}
#endif