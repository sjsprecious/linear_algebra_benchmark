include(FetchContent)

################################
# Memory check

if(ENABLE_MEMCHECK)
  if (${GPU_TYPE} STREQUAL "None")
    # We need to suppress some errors/warnings from valgrind to make it work properly 
    find_file(MEMCHECK_SUPPRESS_FILE
        DOC "Suppression file for memory checking"
        NAMES openmpi-valgrind.supp
        PATHS
        /usr/share/openmpi
        /usr/lib64/openmpi/share
        /usr/lib64/openmpi/share/openmpi
        /usr/share)
    if(MEMCHECK_SUPPRESS_FILE)
        set(MEMCHECK_SUPPRESS "--suppressions=${PROJECT_SOURCE_DIR}/test/valgrind.supp --suppressions=${MEMCHECK_SUPPRESS_FILE}")
    else()
        set(MEMCHECK_SUPPRESS "--suppressions=${PROJECT_SOURCE_DIR}/test/valgrind.supp")
    endif()
endif()

################################
# Google test

if(ENABLE_UNIT_TESTS)
  FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG be03d00f5f0cc3a997d1a368bee8a1fe93651f48
  )
  set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
  set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
endif()

################################
# Google benchmark

if(ENABLE_BENCHMARK_TESTS)
  set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON)
  set(BENCHMARK_ENABLE_TESTING OFF)
  FetchContent_Declare(
      benchmark
      GIT_REPOSITORY https://github.com/google/benchmark.git
      GIT_TAG v1.8.3
  )
  FetchContent_MakeAvailable(benchmark)
endif()

################################
# GPU Support

if(NOT ${GPU_TYPE} STREQUAL "None")
  string(TOLOWER ${GPU_TYPE} GPU_TYPE_LOWER)
  # Data center GPUs
  set(cuda_arch_map_v100 70)
  set(cuda_arch_map_a100 80)
  set(cuda_arch_map_h100 90)
  set(cuda_arch_map_h200 90)
  set(cuda_arch_map_b100 100)
  set(cuda_arch_map_b200 100)
  # Consumer grade GPUs
  set(cuda_arch_map_turing 75)

  set(cuda_arch_map_all_major all-major)
  # Setting CUDAARCHS does not override CMAKE_CUDA_ARCHITECTURES or CUDA_ARCHITECTURES
  # until the current process has returned to the caller site in CMake.
  set(ENV{CUDAARCHS} ${cuda_arch_map_${GPU_TYPE_LOWER}})

  if("$ENV{CUDAARCHS}" STREQUAL "")
    # dynamically create the current options
    set(arch_options "")
    foreach(arch IN ITEMS a100 v100 h100 h200 b100 b200 turing)
      list(APPEND arch_options ${arch})
    endforeach()
    message(FATAL_ERROR "${GPU_TYPE_LOWER} unsupported, current options are ${arch_options}.")
  endif()

  message(STATUS "GPU architecture found: $ENV{CUDAARCHS}")

  include(CheckLanguage)
  check_language(CUDA)
  if(NOT CMAKE_CUDA_COMPILER)
    message(FATAL_ERROR "Unable to find compatiable compiler for CUDA.")
  endif()
  enable_language(CUDA)
  find_package(CUDAToolkit REQUIRED)
  set(ENABLE_CUDA ON)
  set(CUDA_STANDARD_REQUIRED ON)
  # Set the CUDA standard to C++20
  set(CMAKE_CUDA_STANDARD 20)
  set(CMAKE_CUDA_STANDARD_REQUIRED ON)
endif()