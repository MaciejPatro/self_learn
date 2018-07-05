/***********************************************
*
* Created by mpatro on 3/23/18.
*
***********************************************/

#include <catch.hpp>

/*
  Return type deduction

 Using an auto return type in C++14, the compiler will attempt to deduce the type for you. With lambdas, you can now
 deduce its return type using auto, which makes returning a deduced reference or rvalue reference possible.

 */

namespace {

auto should_return_type_int(int i)
{
  return i;
}

template <typename T>
auto& should_deduce_reference_template(T& t)
{
  return t;
}

// Returns a reference to a deduced type.

} // namespace

TEST_CASE("[CPP14] Type Deduction", "[cpp14][return]")
{
  SECTION("Should deduce int as return type of a function with auto")
  {
    auto value_with_deduced_type = should_return_type_int(5);
    REQUIRE(std::is_same<int, decltype(value_with_deduced_type)>::value);
  }

  SECTION("Type deduction with lambdas")
  {
    auto lambda_with_type_deduction = [](auto& x) -> auto&
    {
      return should_deduce_reference_template(x);
    };

    int  some_value              = 123;
    int& reference_to_some_value = lambda_with_type_deduction(some_value);
    REQUIRE(some_value == reference_to_some_value);
  }
}
