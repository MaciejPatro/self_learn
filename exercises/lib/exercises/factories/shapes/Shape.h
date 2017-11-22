/***********************************************
 *
 * Created by mpatro on 11/13/17.
 *
 ***********************************************/

#pragma once

#include <string>

namespace exercises {

class ShapeInterface
{
public:
  virtual ~ShapeInterface() {}
  virtual std::string getName() = 0;

protected:
  ShapeInterface() = default;
};

class Circle : public ShapeInterface
{
public:
  std::string getName()
  {
    return "Circle";
  }
};

class Rectangle : public ShapeInterface
{
public:
  std::string getName()
  {
    return "Rectangle";
  }
};

} // namespace exercises
