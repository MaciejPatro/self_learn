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

struct transaction
{
  unsigned int time;
  bool         is_addition;
  unsigned int id;
  double       price;
};

constexpr double nan_value = std::numeric_limits<double>::signaling_NaN();

class order_book
{
public:
  void add(double price, unsigned int id)
  {
    auto inserted = orders.insert(std::make_pair(price, id));
    ids_lookup.insert(std::make_pair(id, inserted));
  }

  void remove(unsigned int id) noexcept
  {
    auto to_be_removed = std::move(ids_lookup[id]);
    ids_lookup.erase(id);
    orders.erase(to_be_removed);
  }

  double get_highest_price() const noexcept
  {
    if(!orders.empty())
      return orders.begin()->first;
    else
      return nan_value;
  }

private:
  using order_map  = std::multimap<double, unsigned int, std::greater<double>>;
  using lookup_map = std::unordered_map<unsigned int, order_map::iterator>;

  order_map  orders;
  lookup_map ids_lookup;
};

class time_weighted_avg_calc
{
public:
  time_weighted_avg_calc() : time_of_last_update(0), time_summary(0), price_time(0) {}

  void update(const transaction& trans)
  {
    recalculate(trans.time);
    manage_order_book(trans);
  }

  double get_highest() const noexcept
  {
    return price_time / time_summary;
  }

private:
  inline void recalculate(unsigned int current_time) noexcept
  {
    double highest = order_book.get_highest_price();

    if(!std::isnan(highest))
    {
      unsigned int time_diff = current_time - time_of_last_update;

      time_summary += time_diff;
      price_time   += highest * time_diff;
    }
    time_of_last_update = current_time;
  }

  inline void manage_order_book(const transaction& trans)
  {
    if(trans.is_addition)
      order_book.add(trans.price, trans.id);
    else
      order_book.remove(trans.id);
  }

  order_book order_book;
  unsigned int      time_of_last_update;
  unsigned int      time_summary;
  double            price_time;
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

double calculate_TWA_highest(std::string&& filename)
{
  time_weighted_avg_calc calc;

  std::ifstream input(filename, std::ios::binary);
  transaction   trans;

  while(input >> trans)
  {
    calc.update(trans);
  }

  return calc.get_highest();
}

int main(int argc, char** argv)
{
  if(argc == 2)
  {
    std::string filename(argv[0]);
    std::cout << filename;
  }
  return 0;
}

TEST_CASE("memory mapped file", "[recruitment]")
{
  const std::string dir = "/home/mpatro/projects/clion/self_learn_repo/files/";

  SECTION("Empty file should result in nan")
  {
    const std::string empty_file = "empty_file.txt";
    REQUIRE(std::isnan(calculate_TWA_highest(dir + empty_file)));
  }

  SECTION("2 insertion file - should provide average for first time period")
  {
    const std::string file = "2_insertions.txt";
    REQUIRE(15.5 == calculate_TWA_highest(dir + file));
  }

  SECTION("insert and delete - should provide average for first time period")
  {
    const std::string file = "insert_delete.txt";
    REQUIRE(23.5 == calculate_TWA_highest(dir + file));
  }

  SECTION("should correctly average 2 values")
  {
    const std::string file = "average_of_2_values.txt";
    REQUIRE(15 == calculate_TWA_highest(dir + file));
  }

  SECTION("should correctly average 2 weighted values")
  {
    const std::string file = "weighted_average_2_values.txt";
    REQUIRE(15 == calculate_TWA_highest(dir + file));
  }

  SECTION("Should ignore long break without data")
  {
    const std::string file = "long_break_in_between.txt";
    REQUIRE(16 == calculate_TWA_highest(dir + file));
  }

  SECTION("3 value average data")
  {
    const std::string file = "3_val_avg.txt";
    REQUIRE(110.0 == calculate_TWA_highest(dir + file));
  }
}

} // namespace trading_exercise
