/***********************************************
*
* Created by mpatro on 3/22/18.
*
***********************************************/

#include <catch.hpp>

/*
  Generic lambda expressions
 C++14 now allows the auto type-specifier in the parameter list, enabling polymorphic lambdas.

  Lambda capture initializers
 This allows creating lambda captures initialized with arbitrary expressions. The name given to the captured value
 does not need to be related to any variables in the enclosing scopes and introduces a new name inside the lambda
 body. The initializing expression is evaluated when the lambda is created (not when it is invoked).
 */
namespace {

int factory(int i)
{
  return i * 10;
}

} // namespace

TEST_CASE("[CPP14] Lambdas", "[cpp14][lambda]")
{
  SECTION("Generic lambda expressions should correctly allow type deduction")
  {
    constexpr auto identity = [](auto x) { return x; };

    auto        three = identity(3);
    auto        foo   = identity("foo");
    std::string foo2  = identity("foo");

    REQUIRE(std::is_same<int, decltype(three)>::value);
    REQUIRE(std::is_same<const char*, decltype(foo)>::value);

    REQUIRE(std::is_same<std::string, decltype(foo2)>::value);
    REQUIRE_FALSE(std::is_same<std::string, decltype(foo)>::value);
  }

  SECTION("Lambda has capture initializer")
  {
    SECTION("value is calculated at creation")
    {
      auto f = [x = factory(2)] { return x; };
      REQUIRE(20 == f());
    }

    SECTION("Mutable lambda")
    {
      auto generator = [x = 0]() mutable {
        // this would not compile without 'mutable' as we are modifying x on each call
        return x++;
      };
      REQUIRE(0 == generator());
      REQUIRE(1 == generator());
      REQUIRE(2 == generator());
    }
  }
}
