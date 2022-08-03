#pragma once
#ifndef CPP23_CONSTEVAL_TEST_H
#define CPP23_CONSTEVAL_TEST_H

#include <type_traits>
#if __cplusplus == 202002L

template <typename T>
consteval bool is_int(T t) {
  return std::is_integral_v<decltype(t)>;
}

#endif

#if __cplusplus > 202002L
// https://en.cppreference.com/w/cpp/language/consteval
// constexpr 函数可能编译期执行, 也可以在运行期执行, consteval 只能在编译器执行,
// 如果不满足要求编译不通过

consteval bool is_runtime_evaluated() noexcept {
  if
    not consteval { return true; }
  else {
    return false;
  }
}

#endif

#endif  // CPP23_CONSTEVAL_TEST_H