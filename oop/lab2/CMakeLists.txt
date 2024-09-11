cmake_minimum_required(VERSION 3.10)
project(dynamic_array_octal)

set(CMAKE_CXX_STANDARD 17)

# # Загрузка GoogleTest
# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
# )

# FetchContent_MakeAvailable(googletest)

add_executable(lab2 lab2_main.cpp
    src/dynamic_array.cpp
    src/octal.cpp
    src/utils.cpp)

# target_link_libraries(lab2 gtest gtest_main)
