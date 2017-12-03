project(exercisesTests)

add_executable(exercisesTests
        TheLifeAnswerTest.cpp
        ShapeFactoryTests.cpp
        cpp11_features/SimpleLambdaTests.cpp
        cpp11_features/MoveConstructorTests.cpp
        cpp11_features/RValueReferencesTests.cpp
        cpp11_features/VariadicTemplatesTests.cpp cpp11_features/InitializerListsTests.cpp cpp11_features/AutoTests.cpp cpp11_features/AliasesTests.cpp cpp11_features/NullPtrTests.cpp)

target_link_libraries(exercisesTests catchlib exercises)
add_test(NAME exercisesTests COMMAND exercisesTests)
