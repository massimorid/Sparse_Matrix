#include <gtest/gtest.h>
#include "CSCMatrix.h"

using namespace sparsematrix;

TEST(CSCMatrixTest, ConstructionFromDense) {
    std::vector<std::vector<double>> denseMatrix = {
        {1, 0, 0},
        {0, 2, 3},
        {0, 0, 4}
    };
    CSCMatrix csc(denseMatrix);

    EXPECT_EQ(csc.getNNZ(), 4);
    EXPECT_EQ(csc.getShape(), std::make_pair(3, 3));
}

TEST(CSCMatrixTest, ToDenseConversion) {
    std::vector<std::vector<double>> denseMatrix = {
        {1, 0, 0},
        {0, 2, 3},
        {0, 0, 4}
    };
    CSCMatrix csc(denseMatrix);

    std::vector<std::vector<double>> convertedDense;
    csc.toDense(convertedDense);

    EXPECT_EQ(convertedDense, denseMatrix);
}
