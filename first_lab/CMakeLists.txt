include_directories(include)

add_library(closest_pair_lib src/closest_pair_tonum.cpp)

add_executable(first_lab main.cpp)
target_link_libraries(first_lab closest_pair_lib)

add_executable(first_lab_tests tests/main_test.cpp)
target_link_libraries(first_lab_tests closest_pair_lib)
target_link_libraries(first_lab_tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(first_lab_tests)
