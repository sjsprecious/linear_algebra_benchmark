################################
# Test utilities

include(test_util)

################################
# Tests

create_standard_test(NAME unit_trid_matrix_solver SOURCES test_trid_matrix_solver.cpp LIBRARIES linear_algebra)