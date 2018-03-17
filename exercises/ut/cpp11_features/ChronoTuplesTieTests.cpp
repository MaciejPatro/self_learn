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

namespace {

} // namespace

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
