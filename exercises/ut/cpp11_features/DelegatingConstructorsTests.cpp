/***********************************************
*
* Created by mpatro on 12/10/17.
*
***********************************************/

#include <catch.hpp>

/*
   C++11 introduces delegating constructors (chaining invocations)
*/

namespace {

class A
{
public:
  A() : a(5) {}

  A(int multiply) : A() // delegation
  {
    a *= multiply;
  }
  A(int multiply, int reduce) : A(multiply) // delegation
  {
    a -= reduce;
  }
  int a;
};

} // namespace

TEST_CASE("[CPP11] Delegating constructors", "[cpp11][constructor][delegation]")
{
  SECTION("default constructor sets value 5")
  {
    A a;
    REQUIRE(a.a == 5);
  }

  SECTION("delegated to multiply should multiply value 5")
  {
    A a1(3);
    A a2(5);
    REQUIRE(a1.a == 15);
    REQUIRE(a2.a == 25);
  }

  SECTION("second delegation should reduce the multiplied 5 by value")
  {
    A a1(3,3);
    A a2(3,6);
    REQUIRE(a1.a == 12);
    REQUIRE(a2.a == 9);
  }
}
