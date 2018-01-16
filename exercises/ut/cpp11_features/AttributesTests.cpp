/***********************************************
*
* Created by mpatro on 12/10/17.
*
***********************************************/

#include <catch.hpp>

/*
   Attributes provide a universal syntax over __attribute__(...), __declspec, etc.
*/

namespace {
[[noreturn]] void fcn() { throw "error"; }
int some_fcn(int i)
{
  int val = i;
  switch(i)
  {
    case 1:
      return val;
    case 2:
      val += i;
      [[fallthrough]];
    case 3:
      return val + i;
    default:
      return 0;
  }
}
} // namespace

TEST_CASE("[CPP11] Attributes now are provided by universal syntax", "[cpp11][attributes]")
{
  SECTION("no return attribute")
  {
    REQUIRE_THROWS(fcn());
  }

  SECTION("fallthrough without warnings")
  {
    REQUIRE(6 == some_fcn(2));
    REQUIRE(6 == some_fcn(3));
  }
}
