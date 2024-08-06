#########################################
# Utility functions for creating tests

if(ENABLE_MEMCHECK)
  if(ENABLE_CUDA)
    find_program(MEMORYCHECK_COMMAND "compute-sanitizer")
    set(MEMORYCHECK_COMMAND_OPTIONS "--error-exitcode=1 --leak-check full --show-backtrace device --launch-timeout=0")
    set(CUDA_MEMORY_CHECK TRUE)
  else()
    find_program(MEMORYCHECK_COMMAND "valgrind")
    set(MEMORYCHECK_COMMAND_OPTIONS "--error-exitcode=1 --trace-children=yes --leak-check=full --gen-suppressions=all ${MEMCHECK_SUPPRESS}")
  endif()
endif()

################################
# build and add a standard test

function(create_standard_test)
  set(prefix TEST)
  set(optionalValues SKIP_MEMCHECK IS_CUDA_TEST)
  set(singleValues NAME WORKING_DIRECTORY)
  set(multiValues SOURCES LIBRARIES)

  include(CMakeParseArguments)
  cmake_parse_arguments(${prefix} "${optionalValues}" "${singleValues}" "${multiValues}" ${ARGN})

  add_executable(test_${TEST_NAME} ${TEST_SOURCES})

  # link additional libraries
  foreach(library ${TEST_LIBRARIES})
    target_link_libraries(test_${TEST_NAME} PUBLIC ${library})
  endforeach()

  if(NOT DEFINED TEST_WORKING_DIRECTORY)
    message(STATUS "TEST_WORKING_DIRECTORY is not defined")
    message(STATUS "Setting TEST_WORKING_DIRECTORY to ${CMAKE_BINARY_DIR}")
    set(TEST_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
  endif()

  add_my_test(${TEST_NAME} test_${TEST_NAME} "" ${TEST_WORKING_DIRECTORY} ${TEST_SKIP_MEMCHECK} ${TEST_IS_CUDA_TEST})
endfunction(create_standard_test)

################################
# Add a unit or performance test

function(add_my_test test_name test_binary test_args working_dir test_skip_memcheck test_is_cuda_test)
  add_test(NAME ${test_name}
           COMMAND ${test_binary} ${test_args}
           WORKING_DIRECTORY ${working_dir})
  set(memcheck "${MEMORYCHECK_COMMAND} ${MEMORYCHECK_COMMAND_OPTIONS}")
  separate_arguments(memcheck)
  if(MEMORYCHECK_COMMAND AND ENABLE_MEMCHECK AND NOT test_skip_memcheck AND (NOT CUDA_MEMORY_CHECK OR test_is_cuda_test))
    add_test(NAME memcheck_${test_name}
             COMMAND ${memcheck} ${CMAKE_BINARY_DIR}/${test_binary} ${test_args}
             WORKING_DIRECTORY ${working_dir})
  endif()
endfunction(add_my_test)