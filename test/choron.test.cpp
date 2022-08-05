#include <gtest/gtest.h>

#include <chrono>
using namespace std::chrono;
TEST(CHRONO, TEST1) {
  constexpr auto current_year = 2022y;
  constexpr auto current_month = August;
  constexpr auto current_day = 5d;

  static_assert(static_cast<int>(current_year) / 4 != 0 &&
                !current_year.is_leap());
  static_assert(current_year.ok());

  constexpr auto befor_christ = -2022y;
  static_assert(static_cast<int>(befor_christ) / 4 != 0 &&
                !befor_christ.is_leap());
  static_assert(befor_christ.ok());

  static_assert(static_cast<unsigned int>(current_month));
  static_assert(current_month.ok());

  static_assert(static_cast<unsigned int>(current_day));
  static_assert(current_day.ok());

  constexpr year_month_day current{current_year, current_month, current_day};

  static_assert(current.year() == current_year);
  static_assert(current.month() == current_month);
  static_assert(current.day() == current_day);

  constexpr auto tp1 = std::chrono::local_days(current);
  constexpr auto tp2 = std::chrono::sys_days(current);

  constexpr auto fulldate2 = 2019y / September / 18d;

  year_month_day fulldate3{Monday[3] / September /
                           2019};  // Monday[3] 表示第三个星期一
}

TEST(CHRONO, TEST2) {
  constexpr auto m = Monday;
  constexpr auto m3 = Monday[3];

  year_month_day fulldate3{Monday[3] / September /
                           2019};  // 2019年 9月 第三个星期一
}

TEST(CHRONO, TEST3) {
  constexpr auto ymwdl{Tuesday[last] / 11 / 2021};
  static_assert(static_cast<local_days>(ymwdl) ==
                static_cast<local_days>(November / 30 / 2021));
}

#include <thread>

TEST(CHRONO, TIMEPOINT) {
  constexpr year_month_day fulldate3{Monday[3] / September / 2019};
  constexpr year_month_day fulldate4{Monday[4] / September / 2019};
  // constexpr auto du = fulldate4- fulldate3;  //erro

  auto current_time = std::chrono::steady_clock::now();

  std::this_thread::sleep_for(3s);

  auto delay3_time = std::chrono::steady_clock::now();

  auto du = delay3_time - current_time;  // delay3_time

  time_point tp{std::chrono::steady_clock::now() + 3s};

  auto f = tp.time_since_epoch().count();
}

TEST(CHRONO, DURATION) {
  constexpr duration t = 3s;

  constexpr hh_mm_ss ss{t};

  static_assert(is_pm(17h));

  static_assert(make24(3h, true) == 15h);
}
