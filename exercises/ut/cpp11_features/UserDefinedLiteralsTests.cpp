/***********************************************
*
* Created by mpatro on 1/20/18.
*
***********************************************/

#include <catch.hpp>
/*
   User-defined literals allow you to extend the language and add your own syntax. To create a literal, define a
 T operator "" X(...) { ... } function that returns a type T, with a name X. Note that the name of this function
 defines the name of the literal. Any literal names not starting with an underscore are reserved and won't be
 invoked. There are rules on what parameters a user-defined literal function should accept, according to what type the
 literal is called on.
*/

namespace {

constexpr long double operator"" _mm(long double mm)
{
  return mm;
}

constexpr long double operator"" _cm(long double cm)
{
  return 10.0_mm * cm;
}

constexpr long double operator"" _m(long double m)
{
  return 100.0_cm * m;
}

constexpr long double operator"" _km(long double km)
{
  return 1000.0_m * km;
}

constexpr long double operator"" _inch(long double inch)
{
  return 25.4_mm * inch;
}

constexpr long double operator"" _ft(long double ft)
{
  return 12.0_inch * ft;
}

constexpr long double operator"" _yd(long double yd)
{
  return 3.0_ft * yd;
}

} // namespace

TEST_CASE("[CPP11] User-defined literals functionality", "[cpp11][literals]")
{
  SECTION("Metric system equivalence comparison between units")
  {
    REQUIRE(10.0_mm == 1.0_cm);
    REQUIRE(5.0_mm == 0.5_cm);
    REQUIRE(153.0_cm == 1.53_m);
    REQUIRE(1.2_m == 0.0012_km);
  }

  SECTION("Metric vs Imperial system")
  {
    REQUIRE(1.0_ft == 0.3048_m);
    auto meter = 1.0_m;
    auto meter_defined_in_yards = 1.093618_yd;
    REQUIRE(meter == Approx(meter_defined_in_yards));
  }
}
