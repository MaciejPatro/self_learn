/***********************************************
 *
 * Created by mpatro on 11/13/17.
 *
 ***********************************************/

#include <catch.hpp>
#include <exercises/factories/shapes/Shape.h>

TEST_CASE("Shape Factory", "[factory]")
{
  SECTION("Created rectangle and check name")
  {
    exercises::Rectangle rect;
    REQUIRE(rect.getName() == "Rectangle");
  }
}
