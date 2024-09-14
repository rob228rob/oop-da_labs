project(gcd)

cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-ggdb)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(main main.cpp)

add_subdirectory(test)
