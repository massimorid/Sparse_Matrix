# Create the SPARSE_MATRIX library
add_library(SPARSE_MATRIX
    SparseMatrix.cpp
    COOMatrix.cpp
    CSCMatrix.cpp
    CSRMatrix.cpp
    DiagonalMatrix.cpp
)

# Specify include directories for this library
target_include_directories(SPARSE_MATRIX PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Ensure the bin directory exists
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Add the main executable
add_executable(main_exec main.cpp)

# Set the output directory for the main executable
set_target_properties(main_exec PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Link the SPARSE_MATRIX library to the main executable
target_link_libraries(main_exec SPARSE_MATRIX)