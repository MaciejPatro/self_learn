/***********************************************
 *
 * Created by mpatro on 11/5/17.
 *
 ***********************************************/

#include <catch.hpp>

TEST_CASE("Having fun with lambdas", "[lambdas]")
{
  SECTION("Always return true lambda")
  {
    auto always_return_true = []() { return true; };

    REQUIRE(always_return_true());
  }

  SECTION("Lambda checking whether lhs > rhs")
  {
    auto is_greater_than = [](auto lhs, auto rhs) { return lhs > rhs; };

    REQUIRE(is_greater_than(5, 4));
    REQUIRE(is_greater_than(5.23, 4.3));
    REQUIRE_FALSE(is_greater_than(4, 4));
  }

  SECTION("Lambda with side-effect")
  {
    int  some_value        = 5;
    auto three_times_value = [& a = some_value]() -> int { return a++ * 3; }();

    REQUIRE(some_value == 6);
    REQUIRE(three_times_value == 15);
  }
}
