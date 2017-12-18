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

template <typename... Args>
std::vector<int> get_vector_of_arguments_incremented(Args... args)
{
  std::vector<int> incremented = { ++args... };
  return incremented;
}

template <typename... Args>
std::string get_string_depending_on_generic_or_specialization(Args...)
{
  return "generic";
}

template <>
std::string get_string_depending_on_generic_or_specialization<int, int>(int, int)
{
  return "specialization";
};

} // namespace

TEST_CASE("[CPP11]Basics of variadic templates", "[cpp11][variadic][template]")
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
    REQUIRE(50 != sum_of_elements_of_the_same_type(23.5, 23, 3.5));
  }

  SECTION("Variadic template incrementation of elements + initialization list usage")
  {
    using Catch::Matchers::Equals;

    const std::vector<int> expected_result{ 1, 2, 3, 4 };
    const auto             result = get_vector_of_arguments_incremented(0, 1, 2, 3);

    REQUIRE_THAT(result, Equals(expected_result));
  }

  SECTION("Variadic template specialization example")
  {
    using Catch::Matchers::Equals;
    REQUIRE_THAT(get_string_depending_on_generic_or_specialization(1, 2, 3, "string"), Equals("generic"));
    REQUIRE_THAT(get_string_depending_on_generic_or_specialization(1, 2, 3), Equals("generic"));

    REQUIRE_THAT(get_string_depending_on_generic_or_specialization(22, 75), Equals("specialization"));
  }
}
