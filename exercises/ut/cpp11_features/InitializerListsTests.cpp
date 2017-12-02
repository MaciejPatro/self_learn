/***********************************************
*
* Created by mpatro on 12/1/17.
*
***********************************************/

#include <catch.hpp>

/*
    A lightweight array-like container of elements created using a "braced list" syntax. For example, { 1, 2, 3 }
  creates a sequences of integers, that has type std::initializer_list<int>. Useful as a replacement to passing a
  vector of objects to a function.
*/

namespace {
int sum(const std::initializer_list<int>& list)
{
  int total = 0;
  for(auto& e : list)
    total += e;
  return total;
}
} // namespace

TEST_CASE("[CPP11]Initializer lists - how do they actually work", "[cpp11][initializer]")
{
  SECTION("Function with initializer_list as parameter")
  {
    auto list = { 1, 2, 3 };
    REQUIRE(6 == sum(list));
    REQUIRE(0 == sum({}));
    REQUIRE(5 == sum({ 1, 1, 1, 1, 1 }));
  }
}
