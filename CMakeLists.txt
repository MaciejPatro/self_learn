cmake_minimum_required(VERSION 3.10)
project(self_learn_repo)

INCLUDE_DIRECTORIES(/home/mpatro/Downloads/dev_tools/Catch2/single_include)
set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES exercises/main_testing.cpp)
add_executable(self_learn_repo ${SOURCE_FILES})