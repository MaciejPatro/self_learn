project(exercisesTests)

add_executable(exercisesTests TheLifeAnswerTest.cpp)
target_link_libraries(exercisesTests catchlib exercises)
add_test(NAME exercisesTests COMMAND exercisesTests)
