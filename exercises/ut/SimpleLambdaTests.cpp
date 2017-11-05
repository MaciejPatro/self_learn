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
}
