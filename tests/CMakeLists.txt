# Include FetchContent module
include(FetchContent)

# Fetch Google Test
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Include Google Test
include(GoogleTest)

# Add the SparseMatrixTests executable
add_executable(SPARSE_MATRIX_TESTS
    test_sparse_matrix.cpp
    test_csr_matrix.cpp
    test_csc_matrix.cpp
    test_coo_matrix.cpp
    test_diagonal_matrix.cpp
    test_matrix_operations.cpp
)

# Set C++ standard for the test executable
set_target_properties(SPARSE_MATRIX_TESTS PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED YES)

# Make all targets in this directory look for headers here
include_directories(${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/include)

# Find OpenMP package
find_package(OpenMP REQUIRED)

# Link the SPARSE_MATRIX library, OpenMP, and Google Test to the test executable
target_link_libraries(SPARSE_MATRIX_TESTS 
    SPARSE_MATRIX 
    GTest::gtest_main
    OpenMP::OpenMP_CXX
)

# Enable testing
enable_testing()

# Discover and register tests
gtest_discover_tests(SPARSE_MATRIX_TESTS)
