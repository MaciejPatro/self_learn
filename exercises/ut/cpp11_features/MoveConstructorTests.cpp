/***********************************************
 *
 * Created by mpatro on 11/15/17.
 *
 ***********************************************/

#include <catch.hpp>
#include <iostream>

/*

 http://thbecker.net/articles/rvalue_references/section_01.html

    Move semantics is mostly about performance optimization: the ability to move an object without
 the expensive overhead of copying. The difference between a copy and a move is that a copy leaves
 the source unchanged, and a move will leave the source either unchanged or radically different --
 depending on what the source is. For plain old data, a move is the same as a copy.

    To move an object means to transfer ownership of some resource it manages to another object. You
 could think of this as changing pointers held by the source object to be moved, or now held, by the
 destination object; the resource remains in its location in memory. Such an inexpensive transfer of
 resources is extremely useful when the source is an rvalue, where the potentially dangerous
 side-effect of changing the source after the move is redundant since the source is a temporary
 object that won't be accessible later.

    Moves also make it possible to transfer objects such as std::unique_ptrs, smart pointers that
 are designed to hold a pointer to a unique object, from one scope to another.
 */

namespace {
struct BaseWithMoveConstructor
{
  std::string s;
  BaseWithMoveConstructor() : s("test") {}
  BaseWithMoveConstructor(const BaseWithMoveConstructor& o)
  {
    s = "copy";
  }
  BaseWithMoveConstructor(BaseWithMoveConstructor&& o) noexcept : s(std::move(o.s)) {}
};
BaseWithMoveConstructor f(BaseWithMoveConstructor a)
{
  return a;
}

struct InheritedImplicitMoveConstructor : BaseWithMoveConstructor
{
  std::string s2;
  int         n;
  // implicit move constructor InheritedImplicitMoveConstructor::(InheritedImplicitMoveConstructor&&)
  // calls BaseWithMoveConstructor's move constructor
  // calls s2's move constructor
  // and makes a bitwise copy of n
};

struct ExplicitDestructorPreventingMoves : InheritedImplicitMoveConstructor
{
  ~ExplicitDestructorPreventingMoves() {} // destructor prevents implicit move constructor C::(C&&)
};

struct ExplicitDefaultMoveConstructor : InheritedImplicitMoveConstructor
{
  ExplicitDefaultMoveConstructor() {}
  ~ExplicitDefaultMoveConstructor() {} // destructor would prevent implicit move constructor D::(D&&)
  ExplicitDefaultMoveConstructor(ExplicitDefaultMoveConstructor&&) = default; // forces a move constructor anyway
};

} // namespace

TEST_CASE("Move constructors", "[cpp11][move]")
{
  SECTION("Move from temporary rvalue and from xvalue")
  {
    BaseWithMoveConstructor a1 = f(BaseWithMoveConstructor()); // move-constructs from rvalue temporary
    REQUIRE("test" == a1.s);
    BaseWithMoveConstructor a2 = std::move(a1); // move-constructs from xvalue
    REQUIRE("test" == a2.s);
    REQUIRE("" == a1.s);
  }

  SECTION("Implicit move constructor inherited")
  {
    InheritedImplicitMoveConstructor b1;
    REQUIRE("test" == b1.s);
    InheritedImplicitMoveConstructor b2 = std::move(b1); // calls implicit move constructor
    REQUIRE("" == b1.s);
  }

  SECTION("Explicit destructor prevents implicit move constructor")
  {
    ExplicitDestructorPreventingMoves c1;
    ExplicitDestructorPreventingMoves c2 = std::move(c1); // calls copy constructor
    REQUIRE("copy" == c2.s);
    REQUIRE("test" == c1.s);
  }

  SECTION("Explicit destructor with forced default move constructor")
  {
    ExplicitDefaultMoveConstructor d1;
    ExplicitDefaultMoveConstructor d2 = std::move(d1);
    REQUIRE("" == d1.s);
    REQUIRE("test" == d2.s);
  }
}
