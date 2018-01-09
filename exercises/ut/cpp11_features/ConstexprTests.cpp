/***********************************************
*
* Created by mpatro on 12/15/17.
*
***********************************************/

#include <catch.hpp>
/*
    Constant expressions are expressions evaluated by the compiler at compile-time. Only non-complex computations can be
  carried out in a constant expression. Use the constexpr specifier to indicate the variable, function, etc. is a
  constant expression.
*/
namespace {

constexpr int square(int x)
{
  return x * x;
}

struct Complex
{
  constexpr Complex(double r, double i) : re(r), im(i) {}

  constexpr double real() const
  {
    return re;
  }
  constexpr double imag() const
  {
    return im;
  }

private:
  double re;
  double im;
};

} // namespace

TEST_CASE("[CPP11]Const expressions - how do they really work", "[cpp11][constexpr]")
{
  SECTION("Square calculated at compile-time")
  {
    static_assert(square(2) == 4);
  }

  SECTION("Square function works completely fine at runtime")
  {
    int i = 4;
    REQUIRE(square(i) == 16);
  }

  SECTION("Constexpr with classes - complex class")
  {
    constexpr Complex I(0, 1);
    static_assert(0 == I.real());
    static_assert(1 == I.imag());
  }
}
