project(figures)

cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-ggdb)

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(figures)
add_subdirectory(test)

add_executable(main main.cpp)
target_link_libraries(main figures_lib)
