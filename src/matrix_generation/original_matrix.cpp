// src/matrix_generation/original_matrix.cpp

#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
#include <omp.h>
#include <filesystem>

void generate_matrix(const std::string& output_file, int rows, int cols, double sparsity) {
    // Random number generator setup
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    std::uniform_real_distribution<> sparsity_dis(0.0, 1.0);

    // Open output file
    std::ofstream file(output_file);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for writing.\n";
        return;
    }

    // Generate matrix and write to file
    std::cout << "Generating and writing matrix to file: " << output_file << std::endl;

    // Use a parallel region to generate the matrix
    #pragma omp parallel
    {
        // Each thread will have its own random number generator
        std::random_device rd_thread;
        std::mt19937 gen_thread(rd_thread());
        std::uniform_real_distribution<> dis_thread(0.0, 1.0);
        std::uniform_real_distribution<> sparsity_dis_thread(0.0, 1.0);

        // Use a critical section to ensure only one thread writes to the file at a time
        #pragma omp for
        for (int i = 0; i < rows; ++i) {
            std::ostringstream oss;
            for (int j = 0; j < cols; ++j) {
                if (sparsity_dis_thread(gen_thread) < sparsity) {
                    oss << 0.0; // Write zero value
                } else {
                    oss << std::fixed << std::setprecision(6) << dis_thread(gen_thread); // Write random value
                }
                if (j < cols - 1) {
                    oss << " "; // Add a space between values
                }
            }
            oss << "\n"; // Newline at the end of each row

            #pragma omp critical
            {
                file << oss.str();
            }
        }
    }

    file.close();
    std::cout << "Matrix generation complete. Saved to " << output_file << std::endl;
}

int main() {
    // Define matrix dimensions
    const int rows = 500;
    const int cols = 500;

    // Define sparsity factor (e.g., 0.95 means 95% of the elements are zero)
    const double sparsity = 0.95;

    // Ensure the output directory exists
    std::filesystem::create_directories("src/matrix_generation/output");

    // Output file names
    const std::string output_file1 = "src/matrix_generation/output/dense_matrix_40k_1.txt";
    const std::string output_file2 = "src/matrix_generation/output/dense_matrix_40k_2.txt";

    // Generate the first matrix
    generate_matrix(output_file1, rows, cols, sparsity);

    // Generate the second matrix
    generate_matrix(output_file2, rows, cols, sparsity);

    return 0;
}