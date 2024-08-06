cmake_minimum_required(VERSION 3.20)

################################
# Project name
project(
  linear_algebra_tests
  VERSION 0.0.1
  LANGUAGES CXX
)

################################
# Project setup and dependencies

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
# Add the "cmake" folder to the module path so that the *cmake files can be found by the "include" command
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
option(ENABLE_LAPACKE "Enable the usage of LAPACKE package for linear algebra calculation" OFF)
option(ENABLE_MAGMA "Enable the usage of MAGMA package for linear algebra calculation" OFF)
option(ENABLE_DPLASMA "Enable the usage of DPLASMA package for linear algebra calculation" OFF)
option(ENABLE_MEMCHECK "Enable memory checking in tests" OFF)
option(ENABLE_COVERAGE "Enable code coverage check" OFF)
set(GPU_TYPE "None" CACHE STRING "The GPU type being targeted")

################################
# Dependencies

include(cmake/dependencies.cmake)

################################
# Enable CodeCoverage analysis

if(ENABLE_COVERAGE)
  include(CodeCoverage)
  append_coverage_compiler_flags()
  setup_target_for_coverage_lcov(
      NAME coverage
      EXECUTABLE "ctest"
      EXECUTABLE_ARGS ""
      EXCLUDE "${PROJECT_SOURCE_DIR}/test/*"
      BASE_DIRECTORY "")  # if there is a source code directory, it should be set here
endif()

################################
# Tests

if(ENABLE_UNIT_TESTS OR ENABLE_BENCHMARK_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()

################################
# Add a library

add_library(linear_algebra INTERFACE)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
target_compile_features(linear_algebra INTERFACE cxx_std_20)

# if (ENABLE_LAPACKE)
#   target_compile_definitions(linear_algebra INTERFACE USE_LAPACKE)
# endif()

target_include_directories(linear_algebra INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Check for Intel compiler
if (CMAKE_CXX_COMPILER_ID STREQUAL "Intel" OR CMAKE_CXX_COMPILER_ID STREQUAL "IntelLLVM")
  # Set compiler flags for Intel C++
  if (WIN32)
    # For Windows
    target_compile_options(micm INTERFACE "/fp:precise")
  else ()
    # For other operating systems (e.g., Linux, macOS)
    target_compile_options(micm INTERFACE "-ffp-model=precise")
  endif ()
endif ()

if(ENABLE_CUDA)
  add_library(linear_algebra_cuda)
  target_link_libraries(linear_algebra_cuda PRIVATE linear_algebra)
  target_link_libraries(linear_algebra_cuda PUBLIC CUDA::cudart CUDA::cublas)
  # Set the CUDA standard to C++20
  set(CMAKE_CUDA_STANDARD 20)
  set(CMAKE_CUDA_STANDARD_REQUIRED ON)
  set_property(TARGET linear_algebra_cuda PROPERTY CUDA_STANDARD 20)
endif()