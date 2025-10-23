include_directories(include)

add_library(eleven src/Eleven.cpp)

add_executable(second_lab_tests tests/main_tests.cpp)
target_link_libraries(second_lab_tests eleven)
target_link_libraries(second_lab_tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(second_lab_tests)