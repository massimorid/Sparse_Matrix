// DiagonalMatrix: Implements the constructor to convert a dense matrix to diagonal format.
// toDense: Converts the diagonal matrix to a dense matrix.
// getNNZ: Returns the number of non-zero elements.
// getShape: Returns the shape of the matrix.

#include "DiagonalMatrix.h"
#include <stdexcept>

namespace sparsematrix {

DiagonalMatrix::DiagonalMatrix(const std::vector<std::vector<double>>& denseMatrix) {
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

    for (size_t i = 0; i < numRows && i < numCols; ++i) {
        if (denseMatrix[i][i] != 0) {
            values.push_back(denseMatrix[i][i]);
        }
    }
}

void DiagonalMatrix::toDense(std::vector<std::vector<double>>& denseMatrix) const {
    denseMatrix.clear();
    denseMatrix.resize(numRows, std::vector<double>(numCols, 0));
    for (size_t i = 0; i < values.size(); ++i) {
        denseMatrix[i][i] = values[i];
    }
}

size_t DiagonalMatrix::getNNZ() const {
    return values.size();
}

std::pair<size_t, size_t> DiagonalMatrix::getShape() const {
    return {numRows, numCols};
}

double DiagonalMatrix::getElement(size_t row, size_t col) const {
    if (row >= numRows || col >= numCols) {
        throw std::out_of_range("Index out of range");
    }
    return (row == col) ? values[row] : 0.0;
}

} // namespace sparsematrix