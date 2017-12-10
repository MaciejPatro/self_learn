/***********************************************
*
* Created by mpatro on 12/3/17.
*
***********************************************/

#include <catch.hpp>
#include <memory>

/*
   C++11 introduces a new null pointer type designed to replace C's NULL macro. nullptr itself is of type
 std::nullptr_t and can be implicitly converted into pointer types, and unlike NULL, not convertible to integral types
 except bool.
*/

namespace {

bool fnc(int)
{
  return false;
};

bool fnc(char*)
{
  return true;
};

bool expecting_unique_ptr_function(std::unique_ptr<int>)
{
  return true;
}

} // namespace

TEST_CASE("[CPP11] nullptr usage", "[cpp11][nullptr]")
{
  SECTION("Specific function can be called only with nullptr or int. NULL is ambiguous and is not compiling")
  {
    // fnc(NULL); is ambiguous!
    REQUIRE(fnc(nullptr));
    REQUIRE_FALSE(fnc(5));
  }

  SECTION("Nullptr can be used with unique/shared pointers")
  {
    REQUIRE(expecting_unique_ptr_function(nullptr));
    // REQUIRE(expecting_unique_ptr_function(NULL)); incorrect type - will not compile
  }
}
