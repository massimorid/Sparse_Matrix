#include <gtest/gtest.h>
#include "DiagonalMatrix.h"

using namespace sparsematrix;

TEST(DiagonalMatrixTest, ConstructionFromDense) {
    std::vector<std::vector<double>> denseMatrix = {
        {1, 0, 0},
        {0, 2, 0},
        {0, 0, 3}
    };
    DiagonalMatrix diag(denseMatrix);

    EXPECT_EQ(diag.getNNZ(), 3);
    EXPECT_EQ(diag.getShape(), std::make_pair(3, 3));
}

TEST(DiagonalMatrixTest, GetElement) {
    std::vector<std::vector<double>> denseMatrix = {
        {1, 0, 0},
        {0, 2, 0},
        {0, 0, 3}
    };
    DiagonalMatrix diag(denseMatrix);

    EXPECT_EQ(diag.getElement(0, 0), 1);
    EXPECT_EQ(diag.getElement(1, 1), 2);
    EXPECT_EQ(diag.getElement(2, 2), 3);
    EXPECT_EQ(diag.getElement(0, 1), 0); // Off-diagonal elements are zero
}
