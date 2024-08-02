################################
# Test utilities

include(test_util)

################################
# Tests

create_standard_test(NAME unit_naive_trid_matrix_solver SOURCES test_naive_trid_matrix_solver.cpp LIBRARIES linear_algebra)