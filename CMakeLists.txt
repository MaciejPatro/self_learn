cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(self_learn_repo VERSION 0.1 LANGUAGES CXX)

option(testing "testing" ON)
option(asan "asan" OFF)
option(msan "msan" OFF)
set(CMAKE_CXX_FLAGS "-std=c++17 -Weverything -Wno-c++98-compat")
if(asan)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
elseif(msan)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=memory")
endif()

if(testing)
    add_subdirectory(libs/catch2)
    enable_testing()
endif()

add_subdirectory(exercises)