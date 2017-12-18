project(tail)

set(headers tail/tail.h tail/validation.h)
set(sources tail/tail.cpp tail/validation.cpp)

add_executable(tail tail/tailmain.cpp)
add_library(taillib STATIC ${headers} ${sources})

target_include_directories(tail
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        PUBLIC $<INSTALL_INTERFACE:include/>
        )

target_include_directories(taillib
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        PUBLIC $<INSTALL_INTERFACE:include/>
        )