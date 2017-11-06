/***********************************************
 *
 * Created by mpatro on 11/5/17.
 *
 ***********************************************/

#include <catch.hpp>
#include <complex>

TEST_CASE("Having fun with lambdas", "[lambdas]")
{
  SECTION("Always return true lambda")
  {
    auto always_return_true = []() { return true; };

    REQUIRE(always_return_true());
  }

  SECTION("Lambda checking whether lhs > rhs")
  {
    auto is_greater_than = [](auto lhs, auto rhs) { return lhs > rhs; };

    REQUIRE(is_greater_than(5, 4));
    REQUIRE(is_greater_than(5.23, 4.3));
    REQUIRE_FALSE(is_greater_than(4, 4));
  }

  SECTION("Lambda with side-effect")
  {
    int  some_value        = 5;
    auto three_times_value = [& a = some_value]() -> int { return a++ * 3; }();

    REQUIRE(6 == some_value);
    REQUIRE(15 == three_times_value);
  }

  SECTION("Simple variadic lambda - return number of provided elements")
  {
    auto get_num_of_arguments = [](auto... z) { return sizeof...(z); };

    REQUIRE(0 == get_num_of_arguments());
    REQUIRE(7 == get_num_of_arguments(1, 2, 3, 4, 5, 6, 7));
    REQUIRE(4 == get_num_of_arguments(1, 'a', 1.32, std::complex{1, 1}));
  }

  SECTION("Advanced variadic template - side-effect should contain sum of provided element")
  {
    int i = 0;
    REQUIRE(10 == i);
  }
}