#include <gtest/gtest.h>
#include "MatrixOperations.h"
#include <chrono>
#include <random>

namespace sparsematrix {
namespace testing {

class MatrixOperationsTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create test matrices
        smallDenseA = {
            {1.0, 0.0, 2.0},
            {0.0, 3.0, 0.0},
            {4.0, 0.0, 5.0}
        };
        
        smallDenseB = {
            {1.0, 0.0},
            {0.0, 2.0},
            {3.0, 0.0}
        };

        expectedResult = {
            {7.0, 0.0},
            {0.0, 6.0},
            {19.0, 0.0}
        };

        matA = SparseMatrix::fromDense(smallDenseA, "CSR");
        matB = SparseMatrix::fromDense(smallDenseB, "CSR");
    }

    void TearDown() override {
        delete matA;
        delete matB;
    }

    std::vector<std::vector<double>> generateRandomSparseMatrix(
        size_t rows, size_t cols, double sparsity) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        
        std::vector<std::vector<double>> matrix(rows, std::vector<double>(cols, 0.0));
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                if (dis(gen) > sparsity) {
                    matrix[i][j] = dis(gen);
                }
            }
        }
        return matrix;
    }

    std::vector<std::vector<double>> smallDenseA;
    std::vector<std::vector<double>> smallDenseB;
    std::vector<std::vector<double>> expectedResult;
    SparseMatrix* matA;
    SparseMatrix* matB;
};

TEST_F(MatrixOperationsTest, BasicMultiplication) {
    SparseMatrix* result = MatrixOperations::multiply(matA, matB, "CSR");
    std::vector<std::vector<double>> resultDense;
    result->toDense(resultDense);
    
    ASSERT_EQ(resultDense.size(), expectedResult.size());
    for (size_t i = 0; i < resultDense.size(); ++i) {
        for (size_t j = 0; j < resultDense[i].size(); ++j) {
            EXPECT_NEAR(resultDense[i][j], expectedResult[i][j], 1e-10);
        }
    }
    
    delete result;
}

TEST_F(MatrixOperationsTest, VectorMultiplication) {
    std::vector<double> vec = {1.0, 2.0, 3.0};
    std::vector<double> result = MatrixOperations::multiply(matA, vec);
    std::vector<double> expected = {7.0, 6.0, 19.0};
    
    ASSERT_EQ(result.size(), expected.size());
    for (size_t i = 0; i < result.size(); ++i) {
        EXPECT_NEAR(result[i], expected[i], 1e-10);
    }
}

TEST_F(MatrixOperationsTest, ParallelPerformance) {
    const size_t size = 1000;
    const double sparsity = 0.95;
    
    auto largeA = generateRandomSparseMatrix(size, size, sparsity);
    auto largeB = generateRandomSparseMatrix(size, size, sparsity);
    
    SparseMatrix* sparseA = SparseMatrix::fromDense(largeA, "CSR");
    SparseMatrix* sparseB = SparseMatrix::fromDense(largeB, "CSR");

    std::vector<int> threadCounts = {1, 2, 4, 8};
    for (int threads : threadCounts) {
        auto start = std::chrono::high_resolution_clock::now();
        
        SparseMatrix* result = MatrixOperations::multiply(sparseA, sparseB, "CSR", threads);
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        
        std::cout << "Threads: " << threads << ", Time: " << duration.count() << "ms\n";
        
        delete result;
    }

    delete sparseA;
    delete sparseB;
}

TEST_F(MatrixOperationsTest, DimensionMismatch) {
    std::vector<std::vector<double>> wrongShape = {{1.0, 2.0}};
    SparseMatrix* wrongMat = SparseMatrix::fromDense(wrongShape, "CSR");
    
    EXPECT_THROW(MatrixOperations::multiply(matA, wrongMat, "CSR"), std::invalid_argument);
    
    delete wrongMat;
}

} // namespace testing
} // namespace sparsematrix 
