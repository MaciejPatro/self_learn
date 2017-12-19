/***********************************************
*
* Created by mpatro on 12/18/17.
*
***********************************************/

#include "validation.h"
#include <string>
#include <stdexcept>

namespace tail {
bool isValidInput(int numOfArgs, const char** data)
{
  if(numOfArgs != 3)
    return false;
  if(data == nullptr)
    return false;
  try
  {
    if(std::stoi(data[1]) < 0)
      return false;
  }
  catch(const std::out_of_range&)
  {
    return false;
  }
  return true;
}
} // namespace tail