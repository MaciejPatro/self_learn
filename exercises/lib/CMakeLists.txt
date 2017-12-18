project(exercises)

set(headers exercises/TheLifeAnswer.h
            exercises/Factories.h
            exercises/factories/shapes/Shape.h)

set(sources exercises/TheLifeAnswer.cpp)
add_library(exercises STATIC ${headers} ${sources})

target_include_directories(exercises PUBLIC $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>
                                     PUBLIC $<INSTALL_INTERFACE:include/>)
