# Add the SparseMatrixTests executable
add_executable(SPARSE_MATRIX_TESTS
    test_sparse_matrix.cpp
    test_csr_matrix.cpp
    test_csc_matrix.cpp
    test_coo_matrix.cpp
    test_diagonal_matrix.cpp
)

# Link the SPARSE_MATRIX library to the test executable
target_link_libraries(SPARSE_MATRIX_TESTS SPARSE_MATRIX gtest gtest_main)

# Specify additional directories if needed for tests
target_include_directories(SPARSE_MATRIX_TESTS PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Enable testing
enable_testing()

# Add the test executable to the list of tests
add_test(NAME SparseMatrixTests COMMAND SPARSE_MATRIX_TESTS)
