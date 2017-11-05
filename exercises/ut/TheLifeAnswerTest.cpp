/***********************************************
 *
 * Created by mpatro on 11/5/17.
 *
 ***********************************************/

#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <exercises/TheLifeAnswer.h>

TEST_CASE("Life, the universe and everything", "[42][theAnswer]")
{
  exercises::TheLifeAnswer answer;
  REQUIRE(42 == answer.answer());
}
