/***********************************************
*
* Created by mpatro on 2/4/18.
*
***********************************************/

#include <catch.hpp>
#include <string>

/*
   User-defined literals allow you to extend the language and add your own syntax. To create a literal, define a
 T operator "" X(...) { ... } function that returns a type T, with a name X. Note that the name of this function
 defines the name of the literal. Any literal names not starting with an underscore are reserved and won't be
 invoked. There are rules on what parameters a user-defined literal function should accept, according to what type the
 literal is called on.
*/

namespace {
struct Forwardable
{
  Forwardable() : m(Method::None) {}
  Forwardable(const Forwardable& o)
  {
    m = Method::Copied;
  }
  Forwardable(Forwardable&& o)
  {
    m = Method::Moved;
  }
  enum class Method
  {
    None,
    Copied,
    Moved
  };
  Method m;
};

template <typename T>
Forwardable wrapper(T&& arg)
{
  return Forwardable{ std::forward<T>(arg) };
}
} // namespace

TEST_CASE("[CPP11] Standard library features introduced", "[cpp11][stl]")
{
  /*
   std::move indicates that the object passed to it may be moved, or in other words, moved from one object to another
   without a copy. The object passed in should not be used after the move in certain situations.
  */
  SECTION("std::move")
  {
    SECTION("Unique pointer moving example")
    {
      std::unique_ptr<int> p1{ new int };
      *p1                     = 5;
      std::unique_ptr<int> p3 = std::move(p1); // now unsafe to dereference object held by p1
      REQUIRE(*p3 == 5);
    }
  }

  /*
   std::forward
   Returns the arguments passed to it as-is, either as an lvalue or rvalue references, and includes cv-qualification.
   Useful for generic code that need a reference (either lvalue or rvalue) when appropriate, e.g factories.
   Forwarding gets its power from template argument deduction:

   T& & becomes T&
   T& && becomes T&
   T&& & becomes T&
   T&& && becomes T&&
   */
  SECTION("std::forward")
  {
    SECTION("move should enforce forward otherwise object should be copied")
    {
      REQUIRE(Forwardable::Method::Moved == wrapper(Forwardable{}).m);
      Forwardable a{};
      REQUIRE(Forwardable::Method::Copied == wrapper(a).m);
      REQUIRE(Forwardable::Method::Moved == wrapper(std::move(a)).m);
    }
  }

  SECTION("std::to_string - convert numeric arguments to strings")
  {
    REQUIRE(std::to_string(23) == "23");
    REQUIRE(std::to_string(-423.45) == "-423.450000");
    REQUIRE(std::to_string(1e-1) == "0.100000");
  }
}
