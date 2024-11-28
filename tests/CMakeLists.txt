# tests/CMakeLists.txt

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
)

# Add test executables
add_executable(test_coo_matrix test_coo_matrix.cpp)
add_executable(test_csc_matrix test_csc_matrix.cpp)
add_executable(test_csr_matrix test_csr_matrix.cpp)
add_executable(test_diagonal_matrix test_diagonal_matrix.cpp)
add_executable(test_sparse_matrix test_sparse_matrix.cpp)

# Set C++ standard for the test executable
set_target_properties(SPARSE_MATRIX_TESTS PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED YES)

# Make all targets in this directory look for headers here
include_directories(${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/include)

# Include directories
target_include_directories(test_coo_matrix PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(test_csc_matrix PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(test_csr_matrix PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(test_diagonal_matrix PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(test_sparse_matrix PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link the SPARSE_MATRIX library and Google Test to the test executable
target_link_libraries(SPARSE_MATRIX_TESTS SPARSE_MATRIX GTest::gtest_main)

# Link the SPARSE_MATRIX library to the test executables
target_link_libraries(test_coo_matrix SPARSE_MATRIX)
target_link_libraries(test_csc_matrix SPARSE_MATRIX)
target_link_libraries(test_csr_matrix SPARSE_MATRIX)
target_link_libraries(test_diagonal_matrix SPARSE_MATRIX)
target_link_libraries(test_sparse_matrix SPARSE_MATRIX)

# Enable testing
enable_testing()

# Discover and register tests
gtest_discover_tests(SPARSE_MATRIX_TESTS)

# Add tests
add_test(NAME test_coo_matrix COMMAND test_coo_matrix)
add_test(NAME test_csc_matrix COMMAND test_csc_matrix)
add_test(NAME test_csr_matrix COMMAND test_csr_matrix)
add_test(NAME test_diagonal_matrix COMMAND test_diagonal_matrix)
add_test(NAME test_sparse_matrix COMMAND test_sparse_matrix)