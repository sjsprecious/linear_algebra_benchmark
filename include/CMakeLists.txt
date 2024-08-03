################################
# Add a library

add_library(linear_algebra INTERFACE)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
target_compile_features(linear_algebra INTERFACE cxx_std_20)

if (ENABLE_RANDOM_INIT)
  target_compile_definitions(linear_algebra INTERFACE USE_RANDOM_INIT)
  target_compile_definitions(linear_algebra INTERFACE RANDOM_NUMBER_SEED=711)
endif()

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