#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
#include <omp.h>
#include <filesystem>
#include <chrono>
#include <vector>

// Function to generate a sparse matrix
std::vector<std::vector<double>> generate_sparse_matrix(int rows, int cols, double sparsity) {
    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    std::vector<std::vector<double>> matrix(rows, std::vector<double>(cols, 0.0));

    #pragma omp parallel
    {
        std::mt19937 gen_thread(rd() + omp_get_thread_num());
        std::uniform_real_distribution<> dis_thread(0.0, 1.0);

        #pragma omp for
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (dis_thread(gen_thread) >= sparsity) {
                    matrix[i][j] = dis_thread(gen_thread);
                }
            }
        }
    }

    return matrix;
}

// Function to write a matrix to a file
void write_matrix_to_file(const std::string& output_file, const std::vector<std::vector<double>>& matrix) {
    std::ofstream file(output_file);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open file for writing.");
    }

    for (const auto& row : matrix) {
        for (size_t j = 0; j < row.size(); ++j) {
            file << std::fixed << std::setprecision(6) << row[j];
            if (j < row.size() - 1) file << " ";
        }
        file << "\n";
    }

    file.close();
    std::cout << "Matrix saved to " << output_file << std::endl;
}

int main(int argc, char* argv[]) {
    // Start timer
    auto start = std::chrono::high_resolution_clock::now();

    // Default matrix dimensions and sparsity
    int rows = 5000;
    int cols = 5000;
    double sparsity = 0.95;
    std::string output_dir = "src/matrix_generation/output";

    // Parse command-line arguments
    if (argc > 1) rows = std::stoi(argv[1]);
    if (argc > 2) cols = std::stoi(argv[2]);
    if (argc > 3) sparsity = std::stod(argv[3]);
    if (argc > 4) output_dir = argv[4];

    // Ensure the output directory exists
    std::filesystem::create_directories(output_dir);

    // Output file names
    const std::string output_file1 = output_dir + "/dense_matrix_1.txt";
    const std::string output_file2 = output_dir + "/dense_matrix_2.txt";

    // Generate and save the first matrix
    auto matrix1 = generate_sparse_matrix(rows, cols, sparsity);
    write_matrix_to_file(output_file1, matrix1);

    // Generate and save the second matrix
    auto matrix2 = generate_sparse_matrix(rows, cols, sparsity);
    write_matrix_to_file(output_file2, matrix2);

    // End timer
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Total execution time: " << duration.count() << " seconds" << std::endl;

    return 0;
}
