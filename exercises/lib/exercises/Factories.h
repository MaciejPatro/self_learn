/***********************************************
 *
 * Created by mpatro on 11/7/17.
 *
 ***********************************************/

#pragma once

namespace exercises {
namespace factory {

class SomeInterface
{
public:
  virtual ~SomeInterface() {}
  int anInterfaceFunction(double someArgument) = delete;
};

} // namespace factory
} // namespace exercises
