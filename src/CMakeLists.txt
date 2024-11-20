# Create the SPARSE_MATRIX library
add_library(SPARSE_MATRIX
    conversion.cpp
    sparse_matrix.cpp
    utilities.cpp
)

# Specify include directories for this library
target_include_directories(SPARSE_MATRIX PUBLIC ${CMAKE_SOURCE_DIR}/include)
