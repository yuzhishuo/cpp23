#include <gtest/gtest.h>

#include <type_traits>

class interface {
 public:
  int a{};
  int b{};
  int c{};
  virtual ~interface() = default;
};

class class_test1 : public interface {};

thread_local interface *interface_ptr;

TEST(CLASS21, CONSTRUCTOR11) {
  class_test1 test;
  interface_ptr = &test;

  if constexpr (constexpr auto i = std::has_virtual_destructor_v<class_test1>;
                i) {
    interface_ptr = dynamic_cast<interface *>(std::addressof(test));
  } else {
    interface_ptr = std::addressof(test);
  }

  assert(interface_ptr != nullptr);
  EXPECT_EQ(interface_ptr->a, 0);
  EXPECT_EQ(interface_ptr->b, 0);
  EXPECT_EQ(interface_ptr->c, 0);
}