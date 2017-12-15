project(tail)

set(headers tail/tail.h)
set(sources tail/tail.cpp)

add_executable(tail tail/tailmain.cpp)
add_library(taillib STATIC ${headers} ${sources})

target_include_directories(tail
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        PUBLIC $<INSTALL_INTERFACE:include/>
        )