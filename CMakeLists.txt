# root/CMakeLists.txt

cmake_minimum_required(VERSION 3.22)
project(SPARSE_MATRIX)
set(PROJECT_AUTHOR "Jorge")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Find OpenMP
find_package(OpenMP REQUIRED)

add_subdirectory(src)
enable_testing()
add_subdirectory(tests)
add_subdirectory(docs)