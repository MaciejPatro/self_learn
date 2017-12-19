/***********************************************
*
* Created by mpatro on 12/12/17.
*
***********************************************/

#include <catch.hpp>
#include <tail/validation.h>

namespace tail {

TEST_CASE("Tail: Validation of input parameters", "[tail][input]")
{
  constexpr auto programName = "program_name";
  constexpr auto filename    = "some_file.txt";

  SECTION("Reject input with number of arguments other than 3")
  {
    REQUIRE_FALSE(isValidInput(0, nullptr));
    REQUIRE_FALSE(isValidInput(1, nullptr));
    REQUIRE_FALSE(isValidInput(2, nullptr));
    REQUIRE_FALSE(isValidInput(4, nullptr));
  }

  SECTION("Reject input with number of arguments other than 3 with valid input")
  {
    constexpr auto lines       = "15";
    const char*    validData[] = { programName, lines, filename };
    REQUIRE_FALSE(isValidInput(0, validData));
    REQUIRE_FALSE(isValidInput(1, validData));
    REQUIRE_FALSE(isValidInput(2, validData));
    REQUIRE_FALSE(isValidInput(4, validData));
  }

  SECTION("Reject nullptr as data input")
  {
    REQUIRE_FALSE(isValidInput(3, nullptr));
  }

  SECTION("Reject out_of_range argument as number of lines")
  {
    constexpr auto lines       = "1500000000000000000";
    const char*    validData[] = { programName, lines, filename };

    REQUIRE_FALSE(isValidInput(3, validData));
  }
}

} // namespace tail
