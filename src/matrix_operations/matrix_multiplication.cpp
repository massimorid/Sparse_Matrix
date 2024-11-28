#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include <omp.h>
#include <filesystem>
#include "CSRMatrix.h"

// Function to read a dense matrix from a file
std::vector<std::vector<double>> read_matrix(const std::string& file_path) {
    std::ifstream file(file_path);
    std::vector<std::vector<double>> matrix;
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << file_path << std::endl;
        return matrix;
    }

    std::vector<std::string> lines;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    matrix.resize(lines.size());

    #pragma omp parallel for
    for (size_t i = 0; i < lines.size(); ++i) {
        std::istringstream iss(lines[i]);
        std::vector<double> row;
        double value;
        while (iss >> value) {
            row.push_back(value);
        }
        matrix[i] = row;
    }

    std::cout << "Matrix read from " << file_path << " with dimensions " << matrix.size() << "x" 
              << (matrix.empty() ? 0 : matrix[0].size()) << std::endl;
    return matrix;
}

// Function to write a matrix to a file
void write_matrix(const std::vector<std::vector<double>>& matrix, const std::string& file_path) {
    std::ofstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << file_path << " for writing." << std::endl;
        return;
    }

    #pragma omp parallel for
    for (size_t i = 0; i < matrix.size(); ++i) {
        std::ostringstream oss;
        for (const auto& val : matrix[i]) {
            oss << val << " ";
        }
        oss << "\n";
        #pragma omp critical
        {
            file << oss.str();
        }
    }
}

int main() {
    // Start timer
    auto start = std::chrono::high_resolution_clock::now();

    std::string file1 = "src/matrix_generation/output/dense_matrix_1.txt";
    std::string file2 = "src/matrix_generation/output/dense_matrix_2.txt";
    std::string output_file = "src/matrix_operations/output/result_matrix.txt";

    std::vector<std::vector<double>> dense_matrix1;
    std::vector<std::vector<double>> dense_matrix2;

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            dense_matrix1 = read_matrix(file1);
        }
        #pragma omp section
        {
            dense_matrix2 = read_matrix(file2);
        }
    }

    if (dense_matrix1.empty() || dense_matrix2.empty()) {
        std::cerr << "Error: One of the matrices is empty." << std::endl;
        return 1;
    }

    if (dense_matrix1[0].size() != dense_matrix2.size()) {
        std::cerr << "Error: Matrix dimensions do not match for multiplication." << std::endl;
        return 1;
    }

    sparsematrix::CSRMatrix sparse_matrix1(dense_matrix1);
    sparsematrix::CSRMatrix sparse_matrix2(dense_matrix2);

    // Perform sparse matrix multiplication
    std::vector<std::vector<double>> result_matrix = sparsematrix::multiply_sparse_matrices(sparse_matrix1, sparse_matrix2);

    // Write the result to a file
    write_matrix(result_matrix, output_file);

    // End timer
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Total execution time: " << duration.count() << " seconds" << std::endl;

    std::cout << "Matrix multiplication completed and result written to " << output_file << std::endl;

    return 0;
}