#include <gtest/gtest.h>
#include "CSRMatrix.h"
#include "SparseMatrix.h"

using namespace sparsematrix;

TEST(CSRMatrixTest, ConstructionFromDense) {
    std::vector<std::vector<double>> denseMatrix = {
        {1, 0, 0},
        {0, 2, 3},
        {0, 0, 4}
    };
    CSRMatrix csr(denseMatrix);

    EXPECT_EQ(csr.getNNZ(), 4);
    EXPECT_EQ(csr.getShape(), std::make_pair(3, 3));
}

TEST(CSRMatrixTest, ToDenseConversion) {
    std::vector<std::vector<double>> denseMatrix = {
        {1, 0, 0},
        {0, 2, 3},
        {0, 0, 4}
    };
    CSRMatrix csr(denseMatrix);

    std::vector<std::vector<double>> convertedDense;
    csr.toDense(convertedDense);

    EXPECT_EQ(convertedDense, denseMatrix);
}

TEST(CSRMatrixTest, SparseMatrixFromDense) {
    std::vector<std::vector<double>> denseMatrix = {
        {1, 0, 0},
        {0, 2, 0},
        {3, 0, 4}
    };

    SparseMatrix* sparse = SparseMatrix::fromDense(denseMatrix, "CSR");
    EXPECT_NE(sparse, nullptr);

    auto shape = sparse->getShape();
    EXPECT_EQ(shape.first, 3);
    EXPECT_EQ(shape.second, 3);

    delete sparse;
}
