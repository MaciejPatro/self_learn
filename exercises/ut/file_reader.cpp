/***********************************************
*
* Created by mpatro on 6/24/18.
*
***********************************************/

#include <catch.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <type_traits>
#include <utility>
#include <map>
#include <unordered_map>
#include <limits>

namespace trading_exercise {

namespace {
// poor man's implementation of strong type

template <typename T>
using IsNotReference = typename std::enable_if<!std::is_reference<T>::value, void>::type;

template <typename T>
class strong_type
{
public:
  template <typename T_ = T, typename = IsNotReference<T_> >
  explicit constexpr strong_type(T&& value) : value_(std::move(value))
  {
  }
  explicit constexpr strong_type(T const& value) : value_(value) {}

  constexpr T const& get() const
  {
    return value_;
  }

private:
  T value_;
};

} // namespace

namespace order {

using price                = strong_type<double>;
using id                   = strong_type<unsigned int>;
constexpr double nan_value = std::numeric_limits<double>::signaling_NaN();

class order_book
{
  using order_map  = std::multimap<double, unsigned int, std::greater<double> >;
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

} // namespace order

struct transaction
{
  unsigned int time;
  bool         is_addition;
  unsigned int id;
  double       price;
};

std::istream& operator>>(std::istream& is, transaction& t)
{
  char type;
  is >> t.time >> type >> t.id;

  t.is_addition = type == 'I';

  if(t.is_addition)
    is >> t.price;

  return is;
}

order::price read_file(std::string filename)
{
  std::ifstream     input(filename, std::ios::binary);
  order::order_book order_book;
  order::price      highest_price(0);
  transaction       trans;

  while(input >> trans)
  {
    if(trans.is_addition)
      order_book.add(order::price(trans.price), order::id(trans.id));
    else
      order_book.remove(order::id(trans.id));
    highest_price = order_book.get_highest_price();
  }

  return highest_price;
}

TEST_CASE("memory mapped file", "[recruitment]")
{
  const std::string filename = "/home/mpatro/projects/clion/self_learn_repo/files/medium_size_file.txt";
  REQUIRE(read_file(filename).get() == 0);
}

} // namespace trading_exercise
