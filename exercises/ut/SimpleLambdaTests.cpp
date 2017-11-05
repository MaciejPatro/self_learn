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
}
