#include "CSRMatrix.h"
#include <stdexcept>

namespace sparsematrix {

CSRMatrix::CSRMatrix(const std::vector<std::vector<double>>& denseMatrix) {
    numRows = denseMatrix.size();
    if (numRows == 0) {
        numCols = 0;
    } else {
        numCols = denseMatrix[0].size();
    }

    // Check for consistent row sizes
    for (const auto& row : denseMatrix) {
        if (row.size() != numCols) {
            throw std::invalid_argument("All rows must have the same number of columns.");
        }
    }

    rowPtrs.resize(numRows + 1, 0);

    // Populate the CSR structure
    for (size_t i = 0; i < numRows; ++i) {
        for (size_t j = 0; j < numCols; ++j) {
            if (denseMatrix[i][j] != 0) {
                colIndices.push_back(j);
                values.push_back(denseMatrix[i][j]);
                rowPtrs[i + 1]++;
            }
        }
    }

    // Convert rowPtrs to cumulative sums
    for (size_t i = 1; i <= numRows; ++i) {
        rowPtrs[i] += rowPtrs[i - 1];
    }
}

void CSRMatrix::toDense(std::vector<std::vector<double>>& denseMatrix) const {
    denseMatrix.clear();
    denseMatrix.resize(numRows, std::vector<double>(numCols, 0));

    for (size_t i = 0; i < numRows; ++i) {
        for (size_t k = rowPtrs[i]; k < rowPtrs[i + 1]; ++k) {
            denseMatrix[i][colIndices[k]] = values[k];
        }
    }
}

size_t CSRMatrix::getNNZ() const {
    return values.size();
}

std::pair<size_t, size_t> CSRMatrix::getShape() const {
    return {numRows, numCols};
}

double CSRMatrix::getElement(size_t row, size_t col) const {
    for (size_t j = rowPtrs[row]; j < rowPtrs[row + 1]; ++j) {
        if (colIndices[j] == col) {
            return values[j];
        }
    }
    return 0.0;
}

} // namespace sparsematrix
