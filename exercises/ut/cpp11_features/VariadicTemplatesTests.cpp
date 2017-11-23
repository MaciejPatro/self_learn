/***********************************************
*
* Created by mpatro on 11/23/17.
*
***********************************************/

#include <catch.hpp>
#include <string>
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

template <typename T>
T sum_of_elements_of_the_same_type(T elem)
{
  return elem;
}

template <typename T, typename... Args>
T sum_of_elements_of_the_same_type(T first, Args... rest)
{
  return first + sum_of_elements_of_the_same_type(rest...);
};

} // namespace

TEST_CASE("Basics of variadic templates", "[cpp11][variadic][template]")
{
  SECTION("Check number of elements at compile-time")
  {
    static_assert(num_of_elements<>::value == 0);
    static_assert(num_of_elements<char, short, int>::value == 3);
  }

  SECTION("Sum of different elements of same type")
  {
    REQUIRE(23 == sum_of_elements_of_the_same_type(23));
    REQUIRE(50 == sum_of_elements_of_the_same_type(23.5, 23.0, 3.5));

    std::string s1{ "some" };
    std::string s2{ "text" };
    std::string s3{ "here" };
    REQUIRE("sometexthere" == sum_of_elements_of_the_same_type(s1, s2, s3));
  }

  SECTION("Sum of different types fails!")
  {
    // 3.5 downcast to 3 due to conversion to int!
    REQUIRE(49.5 == sum_of_elements_of_the_same_type(23.5, 23, 3.5));
  }
}
