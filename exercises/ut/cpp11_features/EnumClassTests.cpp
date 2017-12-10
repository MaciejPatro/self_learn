/***********************************************
*
* Created by mpatro on 12/10/17.
*
***********************************************/

#include <catch.hpp>

/*
   C++11 introduces a new null pointer type designed to replace C's NULL macro. nullptr itself is of type
 std::nullptr_t and can be implicitly converted into pointer types, and unlike NULL, not convertible to integral types
 except bool.
*/

namespace {

//forward declaration
enum class Color : bool;
bool using_color(Color)
{
  return true;
}

enum class Color : bool
{
  Black,
  White,
};

} // namespace

TEST_CASE("[CPP11] enum class", "[cpp11][enum_class]")
{
  SECTION("benefit")
  {
    auto color = Color::Black;
    SECTION("is strong typing")
    {
      REQUIRE(color != Color::White);
      // REQUIRE(0 != Color::Black); not compiling - Black is class
    }

    SECTION("from having well-defined size")
    {
      REQUIRE(sizeof(bool) == sizeof(Color));
    }

    SECTION("from having possible forward declarations")
    {
      REQUIRE(using_color(Color::Black));
    }
  }
}
