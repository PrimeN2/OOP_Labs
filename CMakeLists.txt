cmake_minimum_required(VERSION 3.10)
project(OOP_LABS)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)
    
FetchContent_MakeAvailable(googletest)
    
option(BUILD_TESTS "BUILD_TESTS" OFF)
if(BUILD_TESTS)
    enable_testing()
endif()

add_subdirectory(first_lab)
add_subdirectory(second_lab)
add_subdirectory(third_lab)