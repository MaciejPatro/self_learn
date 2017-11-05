/***********************************************
 *
 * Created by mpatro on 11/5/17.
 *
 ***********************************************/

#include <catch.hpp>

TEST_CASE("Having fun with lambdas", "[lambdas]")
{
  SECTION("Always return true lambda")
  {
    auto always_return_true = []() { return true; };
    REQUIRE(always_return_true());
  }
  SECTION("Lambda checking whether LHS > RHS")
  {
    class MyType
    {
       public:
      MyType(int i)
          : someVar(i)
      {
      }
      bool operator>(const MyType& arg) const noexcept { return this->someVar > arg.someVar; }

       private:
      int someVar;
    };

    MyType four{4};
    MyType two{2};
    auto   greater_than_lambda = [](auto lhs, auto rhs) { return lhs > rhs; };
    REQUIRE(greater_than_lambda(5, 4));
    REQUIRE(greater_than_lambda(5.23, 4.3));
    REQUIRE(greater_than_lambda(four, two));
  }
}
