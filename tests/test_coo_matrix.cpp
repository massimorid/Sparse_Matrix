#include <gtest/gtest.h>
#include "COOMatrix.h"

using namespace sparsematrix;

TEST(COOMatrixTest, ConstructionFromDense) {
    std::vector<std::vector<double>> denseMatrix = {
        {1, 0, 0},
        {0, 2, 3},
        {0, 0, 4}
    };
    COOMatrix coo(denseMatrix);

    EXPECT_EQ(coo.getNNZ(), 4);
    EXPECT_EQ(coo.getShape(), std::make_pair(3, 3));
}

TEST(COOMatrixTest, ToDenseConversion) {
    std::vector<std::vector<double>> denseMatrix = {
        {1, 0, 0},
        {0, 2, 3},
        {0, 0, 4}
    };
    COOMatrix coo(denseMatrix);

    std::vector<std::vector<double>> convertedDense;
    coo.toDense(convertedDense);

    EXPECT_EQ(convertedDense, denseMatrix);
}
