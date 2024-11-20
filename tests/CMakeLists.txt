# Add the SparseMatrixTests executable
add_executable(SPARSE_MATRIX_TESTS
    test_sparse_matrix.cpp
)

# Link the SPARSE_MATRIX library to the test executable
target_link_libraries(SPARSE_MATRIX_TESTS SPARSE_MATRIX)

# Specify additional directories if needed for tests
target_include_directories(SPARSE_MATRIX_TESTS PUBLIC ${CMAKE_SOURCE_DIR}/include)
