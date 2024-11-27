// COOMatrix: Implements the constructor to convert a dense matrix to COO format.
// toDense: Converts the COO matrix to a dense matrix.
// getNNZ: Returns the number of non-zero elements.
// getShape: Returns the shape of the matrix.

#include "COOMatrix.h"
#include <stdexcept>

namespace sparsematrix {

COOMatrix::COOMatrix(const std::vector<std::vector<double>>& denseMatrix) {
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

    for (size_t i = 0; i < numRows; ++i) {
        for (size_t j = 0; j < numCols; ++j) {
            if (denseMatrix[i][j] != 0) {
                rowIndices.push_back(i);
                colIndices.push_back(j);
                values.push_back(denseMatrix[i][j]);
            }
        }
    }
}

void COOMatrix::toDense(std::vector<std::vector<double>>& denseMatrix) const {
    denseMatrix.clear();
    denseMatrix.resize(numRows, std::vector<double>(numCols, 0));
    for (size_t k = 0; k < values.size(); ++k) {
        denseMatrix[rowIndices[k]][colIndices[k]] = values[k];
    }
}

size_t COOMatrix::getNNZ() const {
    return values.size();
}

std::pair<size_t, size_t> COOMatrix::getShape() const {
    return {numRows, numCols};
}

} // namespace sparsematrix