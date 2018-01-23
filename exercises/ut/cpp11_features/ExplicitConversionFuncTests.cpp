/***********************************************
*
* Created by mpatro on 1/23/18.
*
***********************************************/

#include <catch.hpp>

/*
    Conversion functions can now be made explicit using the explicit specifier.
*/

namespace {
struct A
{
  operator bool() const
  {
    return true;
  }
};

struct B
{
  explicit operator bool() const
  {
    return true;
  }
};
} // namespace

TEST_CASE("[CPP11]Explicit conversion functions", "[cpp11][explicit][conversion]")
{
  SECTION("Implicit conversion for operator A::operator bool()")
  {
    A implicit{};
    bool implicitly_converted_value = implicit;
    REQUIRE(implicit);
    REQUIRE(implicitly_converted_value);
  }

  SECTION("Explicit conversion for operator B::operator bool() sometimes is impossible")
  {
    B explicit_conv{};
    REQUIRE(explicit_conv);
//    bool explicit_conversion_is_impossible = explicit_conv;
  }
}
