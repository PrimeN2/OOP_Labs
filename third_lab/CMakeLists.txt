include_directories(include)

add_executable(third_lab 
    main.cpp
    src/figure.cpp
    src/Pentagon.cpp
    src/Rhombus.cpp
    src/Trapezoid.cpp)


add_executable(third_lab_tests 
    tests/main_test.cpp
    src/figure.cpp
    src/Pentagon.cpp
    src/Rhombus.cpp
    src/Trapezoid.cpp)
target_link_libraries(third_lab_tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(third_lab_tests)
