/***********************************************
*
* Created by mpatro on 6/24/18.
*
***********************************************/

#include <catch.hpp>

#include <type_traits>
#include <utility>
#include <map>
#include <unordered_map>
#include <limits>

namespace {
// poor man's implementation of strong type

template <typename T>
using IsNotReference = typename std::enable_if<!std::is_reference<T>::value, void>::type;

template <typename T>
class strong_type
{
public:
  template <typename T_ = T, typename = IsNotReference<T_> >
  explicit constexpr strong_type(T&& value) : value_(std::move(value)) {}
  explicit constexpr strong_type(T const& value) : value_(value) {}

  constexpr T const& get() const { return value_; }
private:
  T value_;
};

} // namespace

namespace trading_exercise {

using price = strong_type<double>;
using id    = strong_type<unsigned int>;
constexpr double nan_value = std::numeric_limits<double>::signaling_NaN();

class order_book
{
  using order_map  = std::multimap<double, unsigned int, std::greater<double>>;
  using lookup_map = std::unordered_map<unsigned int, order_map::iterator>;
public:

  void add(price p, id i)
  {
    auto inserted = orders.insert(std::make_pair(p.get(), i.get()));
    ids_lookup.insert(std::make_pair(i.get(), inserted));
  }

  void remove(id i) noexcept
  {
    auto to_be_removed = std::move(ids_lookup[i.get()]);
    ids_lookup.erase(i.get());
    orders.erase(to_be_removed);
  }

  price get_highest_price() const noexcept
  {
    if(!orders.empty())
      return price(orders.begin()->first);
    else
      return price(nan_value);
  }
private:
  order_map  orders;
  lookup_map ids_lookup;
};

TEST_CASE("Order book functionality", "[recruitment]")
{
  order_book book;

  SECTION("Should not have a highest price when empty")
  {
    REQUIRE(std::isnan(book.get_highest_price().get()));
  }

  SECTION("Should provide correct highest price for single object")
  {
    price initial_price(23.4);
    id initial_id(3);

    book.add(initial_price, initial_id);

    REQUIRE(initial_price.get() == book.get_highest_price().get());

    SECTION("On remove should empty book")
    {
      book.remove(initial_id);
      REQUIRE(std::isnan(book.get_highest_price().get()));
    }

    SECTION("On addition with higher price should update highest bid")
    {
      price higher_price(30.4);
      id higher_id(4);

      book.add(higher_price, higher_id);
      REQUIRE(higher_price.get() == book.get_highest_price().get());

      SECTION("adding additional higher price and removing initial shouldn't change state of highest bid")
      {
        id new_higher_id(44);
        book.add(higher_price, new_higher_id);

        REQUIRE(higher_price.get() == book.get_highest_price().get());

        book.remove(higher_id);

        REQUIRE(higher_price.get() == book.get_highest_price().get());
      }
    }

    SECTION("Lower price stock shouldn't change highest bid")
    {
      price lower_price(20.4);
      id lower_id(4);

      book.add(lower_price, lower_id);
      REQUIRE(initial_price.get() == book.get_highest_price().get());

      SECTION("Removal higher bid should result in updated highest bid")
      {
        book.remove(initial_id);
        REQUIRE(lower_price.get() == book.get_highest_price().get());
      }
    }
  }
}

} // namespace trading_exercise
