/***********************************************
*
* Created by mpatro on 11/23/17.
*
***********************************************/

#include <catch.hpp>

/*
    The ... syntax creates a parameter pack or expands one. A template parameter pack is a template parameter that
 accepts zero or more template arguments (non-types, types, or templates). A template with at least one parameter pack
 is called a variadic template.
*/
namespace {
template <typename... T>
struct num_of_elements
{
  constexpr static int value = sizeof...(T);
};
} // namespace

TEST_CASE("Basics of variadic templates", "[cpp11][variadic][template]")
{
  SECTION("Check number of elements at compile-time")
  {
    static_assert(num_of_elements<>::value == 0);
    static_assert(num_of_elements<char, short, int>::value == 3);
  }
}
