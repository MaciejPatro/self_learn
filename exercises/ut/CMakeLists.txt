project(exercisesTests)

add_executable(exercisesTests TheLifeAnswerTest.cpp SimpleLambdaTests.cpp ShapeFactoryTests.cpp)
target_link_libraries(exercisesTests catchlib exercises)
add_test(NAME exercisesTests COMMAND exercisesTests)
