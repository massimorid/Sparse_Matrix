#include <gtest/gtest.h>
#include "COOMatrix.h"
#include "DenseMatrix.h"

using namespace sparsematrix;

TEST(COOMatrixTest, ConstructionFromDense) {
    DenseMatrix denseMatrix = {
        {1, 0, 0},
        {0, 2, 3},
        {0, 0, 4}
    };
    COOMatrix coo(denseMatrix);

    EXPECT_EQ(coo.getNNZ(), 4);
    EXPECT_EQ(coo.getShape(), std::make_pair(3, 3));
}

TEST(COOMatrixTest, ToDenseConversion) {
    DenseMatrix denseMatrix = {
        {1, 0, 0},
        {0, 2, 3},
        {0, 0, 4}
    };
    COOMatrix coo(denseMatrix);

    DenseMatrix convertedDense;
    coo.toDense(convertedDense);

    EXPECT_EQ(convertedDense, denseMatrix);
}

TEST(COOMatrixTest, EmptyMatrix) {
    DenseMatrix denseMatrix = {};
    COOMatrix coo(denseMatrix);

    EXPECT_EQ(coo.getNNZ(), 0);
    EXPECT_EQ(coo.getShape(), std::make_pair(0, 0));
}

TEST(COOMatrixTest, InvalidInput) {
    DenseMatrix denseMatrix = {
        {1, 0},
        {0, 2, 3}
    };
    EXPECT_THROW(COOMatrix coo(denseMatrix), std::invalid_argument);
}