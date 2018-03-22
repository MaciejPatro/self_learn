project(exercisesTests)

add_executable(exercisesTests
        TheLifeAnswerTest.cpp
        ShapeFactoryTests.cpp
        cpp11_features/SimpleLambdaTests.cpp
        cpp11_features/MoveConstructorTests.cpp
        cpp11_features/RValueReferencesTests.cpp
        cpp11_features/VariadicTemplatesTests.cpp
        cpp11_features/InitializerListsTests.cpp
        cpp11_features/AutoTests.cpp
        cpp11_features/AliasesTests.cpp
        cpp11_features/NullPtrTests.cpp
        cpp11_features/EnumClassTests.cpp
        cpp11_features/AttributesTests.cpp
        cpp11_features/ConstexprTests.cpp
        cpp11_features/DelegatingConstructorsTests.cpp
        cpp11_features/UserDefinedLiteralsTests.cpp
        cpp11_features/ClassTweaksTests.cpp
        cpp11_features/ExplicitConversionFuncTests.cpp
        cpp11_features/StlFeaturesTests.cpp
        cpp11_features/ChronoTuplesTieTests.cpp
        cpp14_features/LambdaTests.cpp)

target_link_libraries(exercisesTests catchlib exercises)
add_test(NAME exercisesTests COMMAND exercisesTests)
