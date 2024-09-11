cmake_minimum_required(VERSION 3.10)
project(Lab6)

add_compile_options(-Wall -g)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

file(GLOB_RECURSE INCLUDES LIST_DIRECTORIES false ${INCLUDE_DIR}/*.hpp)
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false ${SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false ${TEST_DIR}/*.cpp)

# LIBRARY WITH COMMON FUNCTIONS
add_library(${PROJECT_NAME}_lib
            ${SOURCES}
            ${INCLUDES})            

set_target_properties(${PROJECT_NAME}_lib PROPERTIES
                      CXX_STANDARD 20
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)

# PROJECT ITSELF
add_executable(${PROJECT_NAME}_exe
                ${CMAKE_CURRENT_SOURCE_DIR}/run.cpp)

set_target_properties(${PROJECT_NAME}_exe PROPERTIES
                CXX_STANDARD 20
                CXX_STANDARD_REQUIRED YES
                CXX_EXTENSIONS NO)

add_dependencies(${PROJECT_NAME}_exe ${PROJECT_NAME}_lib)
target_link_libraries(${PROJECT_NAME}_exe ${PROJECT_NAME}_lib)

# DOWNLOAD AND ADD GOOGLETEST WITH FETCHCONTENT
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0  # or the latest stable version
)

# Make gtest available
FetchContent_MakeAvailable(googletest)

enable_testing()

# TESTS
add_executable(${PROJECT_NAME}_game_tests
               ${CMAKE_CURRENT_SOURCE_DIR}/tests/game_tests.cpp)

set_target_properties(${PROJECT_NAME}_game_tests PROPERTIES
                      CXX_STANDARD 20
                      CXX_STANDARD_REQUIRED YES)

target_include_directories(${PROJECT_NAME}_game_tests PRIVATE
                           "${PROJECT_SOURCE_DIR}/src"
                           "${CMAKE_CURRENT_BINARY_DIR}/googletest-src"
                           "${CMAKE_CURRENT_BINARY_DIR}/googletest-src/include")

add_dependencies(${PROJECT_NAME}_game_tests ${PROJECT_NAME}_lib)
target_link_libraries(${PROJECT_NAME}_game_tests ${PROJECT_NAME}_lib gtest_main)

# Enable testing
add_test(NAME ${PROJECT_NAME}_game_tests COMMAND ${PROJECT_NAME}_game_tests)
