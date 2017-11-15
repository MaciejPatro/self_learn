/***********************************************
 *
 * Created by mpatro on 11/15/17.
 *
 ***********************************************/

#include <catch.hpp>

/*
   C++11 introduces a new reference termed the rvalue reference. An rvalue reference to A is created with the syntax
 A&&. This enables two major features: move semantics; and perfect forwarding, the ability to pass arguments while
 maintaining information about them as lvalues/rvalues in a generic way.
*/

TEST_CASE("rvalue references", "[cpp11][move]")
{
  SECTION("rvalue references with typecheck")
  {
    //TODO: soon tm
  }
}
