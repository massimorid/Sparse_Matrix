# src/matrix_generation/CMakeLists.txt

# Add the matrix generation executable
add_executable(matrix_generation original_matrix.cpp)

# Include directories
target_include_directories(matrix_generation PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link the SPARSE_MATRIX library
target_link_libraries(matrix_generation SPARSE_MATRIX)