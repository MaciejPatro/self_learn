/***********************************************
*
* Created by mpatro on 12/2/17.
*
***********************************************/

#include <catch.hpp>

/*
    auto-typed variables are deduced by the compiler according to the type of their initializer.
*/

namespace {
template <typename X, typename Y>
auto add(X x, Y y) -> decltype(x + y)
{
  return x + y;
}
} // namespace

TEST_CASE("[CPP11] Auto and decltype", "[cpp11][auto][decltype]")
{
  SECTION("Check type deduction from auto for basic types")
  {
    auto double_val = 3.14;
    REQUIRE(std::is_same<decltype(double_val), double>::value);

    std::vector<int> v{};
    auto             cit = v.cbegin();
    REQUIRE(std::is_same<decltype(cit), std::vector<int>::const_iterator>::value);
  }

  SECTION("Type deduction for references etc")
  {
    auto&& rvalue_val = 1;
    REQUIRE(std::is_same<decltype(rvalue_val), int&&>::value);

    const auto& const_ref_for_init_list = { 1, 2, 3 };
    REQUIRE(std::is_same<decltype(const_ref_for_init_list), const std::initializer_list<int>&>::value);

    auto* raw_pointer = new int[4];
    REQUIRE(std::is_same<decltype(raw_pointer), int*>::value);
    delete[] raw_pointer;
  }

  SECTION("Functions can also deduce the return type using auto. In C++11, a return type must be specified either "
          "explicitly, or using decltype")
  {
    auto sum = add(1, 2);
    REQUIRE(std::is_same<decltype(sum), int>::value);

    auto sum_of_different_types = add(1, 2.1);
    REQUIRE(std::is_same<decltype(sum_of_different_types), double>::value); // upcast to double
  }
}
