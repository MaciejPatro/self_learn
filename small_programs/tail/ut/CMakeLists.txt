project(tailTests)

add_executable(tailTests tailTests.cpp)

target_link_libraries(tailTests catchlib taillib)
add_test(NAME tailTests COMMAND tailTests)
