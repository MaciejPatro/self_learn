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

class Probability
{
  long double value;

public:
  explicit constexpr Probability(long double v) : value(v){};

  constexpr Probability& operator+(const Probability& rhs)
  {
    this->value += rhs.value;
    if(this->value > 1.0)
      this->value = 1.0;
    return *this;
  }

  constexpr bool operator==(const Probability& rhs) const
  {
    return this->value == rhs.value;
  }
};

constexpr Probability operator"" _prob(long double v)
{
  if(v < 0)
    return Probability(0.0);
  if(v > 1.0)
    return Probability(1.0);
  return Probability(v);
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
    auto meter                  = 1.0_m;
    auto meter_defined_in_yards = 1.093618_yd;
    REQUIRE(meter == Approx(meter_defined_in_yards));
  }

  SECTION("Probability example used as constexpr with overloaded operators")
  {
    static_assert(0.4_prob + 0.2_prob == 0.6_prob);
    static_assert(0.7_prob + 0.8_prob == 1.0_prob); // you can't have more than 100% chances;
    //    static_assert(0.4_prob + 0.2 == 0.6_prob); - not gonna compile;
  }
}
