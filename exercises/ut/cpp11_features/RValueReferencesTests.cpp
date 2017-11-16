/***********************************************
 *
 * Created by mpatro on 11/15/17.
 *
 ***********************************************/

#include <catch.hpp>

/*
   C++11 introduces a new reference termed the rvalue reference. An rvalue reference to A is created
 with the syntax A&&. This enables two major features: move semantics; and perfect forwarding, the
 ability to pass arguments while maintaining information about them as lvalues/rvalues in a generic
 way.
*/

namespace
{
enum class Output
{
  ByLvalue,
  ByConstLvalue,
  ByRvalue
};

Output fullyOverloadedFunction(int&) { return Output::ByLvalue; }
Output fullyOverloadedFunction(const int&) { return Output::ByConstLvalue; }
Output fullyOverloadedFunction(int&&) { return Output::ByRvalue; }

Output onlyLvalueOverloads(int&) { return Output::ByLvalue; }
Output onlyLvalueOverloads(const int&) { return Output::ByConstLvalue; }

} // namespace anonymous

TEST_CASE("Rvalue references", "[cpp11][move]")
{
  SECTION("Overloaded functions with Only lvalue overloads")
  {
    SECTION("Call by lvalue")
    {
      int value = 4;
      REQUIRE(Output::ByLvalue == onlyLvalueOverloads(value));
    }

    SECTION("Call by const lvalue")
    {
      const int constValue = 5;
      REQUIRE(Output::ByConstLvalue == onlyLvalueOverloads(constValue));
    }

    SECTION("Rvalue provided requires call to const lvalue overload")
    {
      REQUIRE(Output::ByConstLvalue == onlyLvalueOverloads(3));
    }

    SECTION("std::move will force a call to const lvalue overload")
    {
      int value = 7;
      REQUIRE(Output::ByConstLvalue == onlyLvalueOverloads(std::move(value)));
    }
  }

  SECTION("Overloaded function with rvalue overload existing")
  {
    SECTION("Rvalue instead of const lvalue")
    {
      REQUIRE(Output::ByRvalue == fullyOverloadedFunction(5));
    }

    SECTION("Move required rvalue overload")
    {
      int value = 5;
      REQUIRE(Output::ByRvalue == fullyOverloadedFunction(std::move(value)));
    }

    SECTION("Lvalues to be used correctly")
    {
      int       value      = 3;
      const int constValue = 5;
      REQUIRE(Output::ByLvalue == fullyOverloadedFunction(value));
      REQUIRE(Output::ByConstLvalue == fullyOverloadedFunction(constValue));
    }
  }
}
