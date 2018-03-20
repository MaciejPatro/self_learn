/***********************************************
*
* Created by mpatro on 3/17/18.
*
***********************************************/

#include <catch.hpp>
#include <chrono>
/*
   std::chrono

 The chrono library contains a set of utility functions and types that deal with durations, clocks, and time points.
 One use case of this library is benchmarking code.
*/
TEST_CASE("[CPP11] std::chrono", "[cpp11][chrono]")
{
  SECTION("Chrono example - for benchmarking purposes")
  {
    const auto start_point = std::chrono::system_clock::now();
    const auto end_point   = start_point + std::chrono::seconds(2);

    const std::chrono::duration<double> expected_duration = std::chrono::seconds(2);
    const std::chrono::duration<double> counted_result    = end_point - start_point;

    REQUIRE(expected_duration.count() == counted_result.count());
  }
}

TEST_CASE("[CPP11] std::tuple and std::tie", "[cpp11][tuple]")
{
  SECTION("Tuple and tie usage")
  {
    constexpr int some_value = 43;
    constexpr double some_floating_point = 3.54;
    const std::string text = "text";

    auto my_tuple = std::make_tuple(some_value, some_floating_point, text);

    REQUIRE(some_floating_point == std::get<1>(my_tuple));
    REQUIRE(some_value == std::get<0>(my_tuple));
    REQUIRE(text == std::get<2>(my_tuple));

    std::string tie_text;
    int tie_value;
    std::tie(tie_value, std::ignore, tie_text) = my_tuple; // c++17 supports better way to handle this
    REQUIRE(tie_value == some_value);
    REQUIRE(tie_text == text);
  }
}
