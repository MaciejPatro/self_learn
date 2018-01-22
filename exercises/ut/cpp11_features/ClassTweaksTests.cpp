/***********************************************
*
* Created by mpatro on 1/22/18.
*
***********************************************/

#include <catch.hpp>

/*
    Explicit virtual overrides
  Specifies that a virtual function overrides another virtual function. If the virtual function does not override a
  parent's virtual function, throws a compiler error.

    Final specifier
  Specifies that a virtual function cannot be overridden in a derived class or that a class cannot be inherited from.

    Default functions
  A more elegant, efficient way to provide a default implementation of a function, such as a constructor.

    Deleted functions
  A more elegant, efficient way to provide a deleted implementation of a function. Useful for preventing copies on
  objects.
*/

namespace {
struct OverrideA
{
  virtual void foo();
  void         bar();
};

struct OverrideB : OverrideA
{
  void foo() override; // correct -- B::foo overrides A::foo
  //  void bar() override; // error -- A::bar is not virtual
  //  void baz() override; // error -- B::baz does not override A::baz
};

struct NonFinalA
{
  virtual void foo();
};

struct FinalB : NonFinalA
{
  virtual void foo() final;
};

struct CannotOverrideFoo : FinalB
{
  //  virtual void foo(); // error -- declaration of 'foo' overrides a 'final' function
};

constexpr int some_value = 5;

struct BaseClass {
  BaseClass() : x(some_value) {}
  int x;
};

struct DefaultInheritanceOfConstructor : BaseClass {
  // Calls BaseClass::BaseClass
  DefaultInheritanceOfConstructor() = default;
};

class DeletedOperators {
public:
  int x;
  DeletedOperators(int x) : x(x) {};
  DeletedOperators(const DeletedOperators&) = delete;
  DeletedOperators& operator=(const DeletedOperators&) = delete;
};

DeletedOperators x{ 123 }; // ok
//DeletedOperators y = x; // error -- call to deleted copy constructor
//y = x; // error -- operator= deleted

} // namespace

TEST_CASE("[CPP11] Class modifications introduces in C++11", "[cpp11][default][delete][override][final]")
{
  SECTION("Default contructor inherited from base class")
  {
    DefaultInheritanceOfConstructor c;
    REQUIRE(c.x == some_value);
  }
}
