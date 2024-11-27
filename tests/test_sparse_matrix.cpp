#include <gtest/gtest.h>
#include "SparseMatrix.h"
#include "DenseMatrix.h"

using namespace sparsematrix;

TEST(SparseMatrixTest, ConversionToCSR) {
    DenseMatrix denseMatrix = {
        {1, 0, 0},
        {0, 2, 0},
        {3, 0, 4}
    };

    SparseMatrix* sparse = SparseMatrix::fromDense(denseMatrix, "CSR");
    EXPECT_NE(sparse, nullptr);

    DenseMatrix convertedDense;
    sparse->toDense(convertedDense);

    EXPECT_EQ(convertedDense, denseMatrix);

    delete sparse;
}

TEST(SparseMatrixTest, ConversionToCSC) {
    DenseMatrix denseMatrix = {
        {1, 0, 0},
        {0, 2, 0},
        {3, 0, 4}
    };

    SparseMatrix* sparse = SparseMatrix::fromDense(denseMatrix, "CSC");
    EXPECT_NE(sparse, nullptr);

    DenseMatrix convertedDense;
    sparse->toDense(convertedDense);

    EXPECT_EQ(convertedDense, denseMatrix);

    delete sparse;
}

TEST(SparseMatrixTest, InvalidFormat) {
    DenseMatrix denseMatrix = {
        {1, 0, 0},
        {0, 2, 0},
        {3, 0, 4}
    };

    EXPECT_THROW(SparseMatrix::fromDense(denseMatrix, "INVALID"), std::invalid_argument);
}