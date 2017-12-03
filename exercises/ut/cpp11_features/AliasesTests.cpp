/***********************************************
*
* Created by mpatro on 12/3/17.
*
***********************************************/

#include <catch.hpp>

/*
    Template aliases. Semantically similar to using a typedef however, template aliases with using are easier to read
  and are compatible with templates.
*/

namespace {
template <typename T>
using MyVec = std::vector<T>;

bool example_function(int, int)
{
  return true;
}

template <typename T>
using Invoke = typename T::type;

template <typename Condition>
using EnableIf = Invoke<std::enable_if<Condition::value> >;

template <typename T, typename = EnableIf<std::is_trivial<T> > >
int function_for_trivial_types(T)
{
  return 1;
}

} // namespace

TEST_CASE("[CPP11] Aliases using and how it works", "[cpp11][alias]")
{
  SECTION("Template alias for vector")
  {
    MyVec<int> vec{ 1, 2, 4 };
    REQUIRE(std::is_same<decltype(vec), std::vector<int> >::value);
  }

  SECTION("Pointer to a function")
  {
    using func = bool (*)(int, int);
    func f     = example_function;
    REQUIRE(f(2, 3));
  }

  SECTION("Simplification of syntax for std::enable_if used in templates")
  {
    auto i = 5;
    REQUIRE(1 == function_for_trivial_types(i));
  }
}
