#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <omp.h>
#include "SparseMatrix.h"
#include "CSRMatrix.h"

std::vector<std::vector<double>> read_matrix(const std::string& file_path) {
    std::ifstream file(file_path);
    std::vector<std::vector<double>> matrix;
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << file_path << std::endl;
        return matrix;
    }

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<double> row;
        double value;
        while (iss >> value) {
            row.push_back(value);
        }
        matrix.push_back(row);
    }

    std::cout << "Matrix read from " << file_path << " with dimensions " << matrix.size() << "x" << (matrix.empty() ? 0 : matrix[0].size()) << std::endl;
    return matrix;
}

void write_matrix(const std::vector<std::vector<double>>& matrix, const std::string& file_path) {
    std::ofstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << file_path << " for writing." << std::endl;
        return;
    }

    for (const auto& row : matrix) {
        for (size_t j = 0; j < row.size(); ++j) {
            file << row[j];
            if (j < row.size() - 1) {
                file << " ";
            }
        }
        file << "\n";
    }

    std::cout << "Matrix written to " << file_path << std::endl;
}

std::vector<std::vector<double>> multiply_sparse_matrices(const sparsematrix::CSRMatrix& matrix1, const sparsematrix::CSRMatrix& matrix2) {
    size_t rows1 = matrix1.getShape().first;
    size_t cols2 = matrix2.getShape().second;
    size_t cols1 = matrix1.getShape().second;

    std::vector<std::vector<double>> result(rows1, std::vector<double>(cols2, 0.0));

    #pragma omp parallel for
    for (size_t i = 0; i < rows1; ++i) {
        for (size_t j = 0; j < cols2; ++j) {
            for (size_t k = 0; k < cols1; ++k) {
                result[i][j] += matrix1.getElement(i, k) * matrix2.getElement(k, j);
            }
        }
    }

    std::cout << "Matrix multiplication completed." << std::endl;
    return result;
}

int main() {
    std::string file1 = "src/matrix_generation/output/dense_matrix_40k_1.txt";
    std::string file2 = "src/matrix_generation/output/dense_matrix_40k_2.txt";
    std::string output_file = "src/matrix_operations/output/result_matrix.txt";

    std::vector<std::vector<double>> dense_matrix1 = read_matrix(file1);
    std::vector<std::vector<double>> dense_matrix2 = read_matrix(file2);

    if (dense_matrix1.empty() || dense_matrix2.empty()) {
        std::cerr << "Error: One of the matrices is empty." << std::endl;
        return 1;
    }

    if (dense_matrix1[0].size() != dense_matrix2.size()) {
        std::cerr << "Error: Matrix dimensions do not match for multiplication." << std::endl;
        return 1;
    }

    // Convert dense matrices to CSR format
    sparsematrix::CSRMatrix sparse_matrix1(dense_matrix1);
    sparsematrix::CSRMatrix sparse_matrix2(dense_matrix2);

    // Perform sparse matrix multiplication
    std::vector<std::vector<double>> result_matrix = multiply_sparse_matrices(sparse_matrix1, sparse_matrix2);

    // Write the result to a file
    write_matrix(result_matrix, output_file);

    std::cout << "Matrix multiplication completed and result written to " << output_file << std::endl;

    return 0;
}