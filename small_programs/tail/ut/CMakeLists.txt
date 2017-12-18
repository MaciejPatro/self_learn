project(tailTests)

add_executable(tailTests TailTests.cpp ValidationTests.cpp)

target_link_libraries(tailTests catchlib taillib)
add_test(NAME tailTests COMMAND tailTests)
