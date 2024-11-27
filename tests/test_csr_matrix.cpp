#include <gtest/gtest.h>
#include "CSRMatrix.h"
#include "DenseMatrix.h"

using namespace sparsematrix;

TEST(CSRMatrixTest, ConstructionFromDense) {
    DenseMatrix denseMatrix = {
        {1, 0, 0},
        {0, 2, 3},
        {0, 0, 4}
    };
    CSRMatrix csr(denseMatrix);

    EXPECT_EQ(csr.getNNZ(), 4);
    EXPECT_EQ(csr.getShape(), std::make_pair(3, 3));
}

TEST(CSRMatrixTest, ToDenseConversion) {
    DenseMatrix denseMatrix = {
        {1, 0, 0},
        {0, 2, 3},
        {0, 0, 4}
    };
    CSRMatrix csr(denseMatrix);

    DenseMatrix convertedDense;
    csr.toDense(convertedDense);

    EXPECT_EQ(convertedDense, denseMatrix);
}

TEST(CSRMatrixTest, EmptyMatrix) {
    DenseMatrix denseMatrix = {};
    CSRMatrix csr(denseMatrix);

    EXPECT_EQ(csr.getNNZ(), 0);
    EXPECT_EQ(csr.getShape(), std::make_pair(0, 0));
}

TEST(CSRMatrixTest, InvalidInput) {
    DenseMatrix denseMatrix = {
        {1, 0},
        {0, 2, 3}
    };
    EXPECT_THROW(CSRMatrix csr(denseMatrix), std::invalid_argument);
}