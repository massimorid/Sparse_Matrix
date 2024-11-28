# src/matrix_operations/CMakeLists.txt

# Add the matrix multiplication executable
add_executable(matrix_multiplication matrix_multiplication.cpp)

# Include directories
target_include_directories(matrix_multiplication PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link the SPARSE_MATRIX library and OpenMP
target_link_libraries(matrix_multiplication SPARSE_MATRIX OpenMP::OpenMP_CXX)

# Set the output directory for the executable
set_target_properties(matrix_multiplication PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})