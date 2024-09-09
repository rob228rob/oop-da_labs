cmake_minimum_required(VERSION 3.10)
project(BinaryCountTests)

set(CMAKE_CXX_STANDARD 17)

# Загрузка GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(BinaryCountTests test_binary_count.cpp)

target_link_libraries(BinaryCountTests gtest gtest_main)

include(GoogleTest)
