cmake_minimum_required(VERSION 3.10)
project(SparseMatrix)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add source files and create the SparseMatrix library
add_library(SparseMatrix
    src/matrix_foundation.cpp
    src/conversion.cpp
    src/utilities.cpp
)

# Add test executable
add_executable(SparseMatrixTests
    tests/test_sparse_matrix.cpp
)

# Link the test executable with SparseMatrix library and GoogleTest
target_link_libraries(SparseMatrixTests
    PRIVATE SparseMatrix GTest::gtest_main pthread
)
