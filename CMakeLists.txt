cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(self_learn_repo VERSION 0.1 LANGUAGES CXX)

option(testing "testing" ON)
option(asan "asan" OFF)
option(msan "msan" OFF)
option(coverage "coverage" OFF)

set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wpedantic -Wno-c++98-compat")

if(asan)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
elseif(msan)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=memory -fno-omit-frame-pointer")
elseif(tsan)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
elseif(coverage)
    # does -g option is needed?
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 --coverage -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

if(testing)
    add_subdirectory(libs/catch2)
    enable_testing()
endif()

add_subdirectory(exercises)
add_subdirectory(small_programs)