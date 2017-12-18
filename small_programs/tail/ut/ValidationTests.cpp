/***********************************************
*
* Created by mpatro on 12/12/17.
*
***********************************************/

#include <catch.hpp>
#include <tail/validation.h>

TEST_CASE("Tail: Validation of input parameters", "[tail][input]")
{
  SECTION("Reject empty input")
  {
    REQUIRE(isValidInput());
  }
}