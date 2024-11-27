// CSCMatrix: Implements the constructor to convert a dense matrix to CSC format.
// toDense: Converts the CSC matrix to a dense matrix.
// getNNZ: Returns the number of non-zero elements.
// getShape: Returns the shape of the matrix.

#include "CSCMatrix.h"
#include <stdexcept>

namespace sparsematrix {

CSCMatrix::CSCMatrix(const std::vector<std::vector<double>>& denseMatrix) {
    numRows = denseMatrix.size();
    if (numRows == 0) {
        numCols = 0;
    } else {
        numCols = denseMatrix[0].size();
    }

    for (const auto& row : denseMatrix) {
        if (row.size() != numCols) {
            throw std::invalid_argument("All rows must have the same number of columns");
        }
    }

    colPtrs.resize(numCols + 1, 0);
    for (size_t j = 0; j < numCols; ++j) {
        for (size_t i = 0; i < numRows; ++i) {
            if (denseMatrix[i][j] != 0) {
                rowIndices.push_back(i);
                values.push_back(denseMatrix[i][j]);
                colPtrs[j + 1]++;
            }
        }
    }
    for (size_t j = 1; j <= numCols; ++j) {
        colPtrs[j] += colPtrs[j - 1];
    }
}

void CSCMatrix::toDense(std::vector<std::vector<double>>& denseMatrix) const {
    denseMatrix.clear();
    denseMatrix.resize(numRows, std::vector<double>(numCols, 0));
    for (size_t j = 0; j < numCols; ++j) {
        for (size_t k = colPtrs[j]; k < colPtrs[j + 1]; ++k) {
            denseMatrix[rowIndices[k]][j] = values[k];
        }
    }
}

size_t CSCMatrix::getNNZ() const {
    return values.size();
}

std::pair<size_t, size_t> CSCMatrix::getShape() const {
    return {numRows, numCols};
}

} // namespace sparsematrix