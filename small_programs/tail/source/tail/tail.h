/***********************************************
*
* Created by mpatro on 12/12/17.
*
***********************************************/

#pragma once

#include <string>

namespace tail {
class FileReader
{
public:
  FileReader(std::string fName) : fileName(fName) {}

private:
  std::string fileName;
};
} // namespace tail
