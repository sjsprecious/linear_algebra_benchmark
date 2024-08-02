cmake_minimum_required(VERSION 3.20)

################################
# Project name
project(
  linear_algebra_tests
  VERSION 0.0.1
  LANGUAGES CXX
)

################################
# Set the C++ standard to C++20

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

################################
# Project setup and dependencies

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PROJECT_SOURCE_DIR}/cmake")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING
      "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)

message ( STATUS "CMake build configuration for linear_algebra_tests(${CMAKE_BUILD_TYPE}) ${PROJECT_VERSION}" )

################################
# Options

option(ENABLE_UNIT_TESTS "Build unit tests" ON)
option(ENABLE_BENCHMARK_TESTS "Build performance tests" OFF)
option(USE_DOUBLE_PRECISION "Use double precision for linear algebra calculation" ON)
option(ENABLE_LAPACKE "Enable the usage of LAPACKE package for linear algebra calculation" OFF)
option(ENABLE_MAGMA "Enable the usage of MAGMA package for linear algebra calculation" OFF)
option(ENABLE_DPLASMA "Enable the usage of DPLASMA package for linear algebra calculation" OFF)
option(ENABLE_MEMCHECK "Enable memory checking in tests" OFF)
set(GPU_TYPE "None" CACHE STRING "The GPU type being targeted")

################################
# Dependencies

include(cmake/dependencies.cmake)
include(cmake/test_util.cmake)

################################
# Source code or headers

add_subdirectory(include)

################################
# Tests

if(ENABLE_UNIT_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()