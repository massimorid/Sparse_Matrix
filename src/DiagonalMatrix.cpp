#include "DiagonalMatrix.h"

namespace sparsematrix {

DiagonalMatrix::DiagonalMatrix(const std::vector<double>& diagonal)
    : diagonal(diagonal), size(diagonal.size()) {}

SparseMatrix* DiagonalMatrix::convertTo(const std::string& format) const {
    if (format == "COO") {
        // Conversion logic to COO format
    } else if (format == "CSR") {
        // Conversion logic to CSR format
    }
    return nullptr;
}

void DiagonalMatrix::toDense(std::vector<std::vector<double>>& denseMatrix) const {
    denseMatrix.assign(size, std::vector<double>(size, 0));
    for (int i = 0; i < size; ++i) {
        denseMatrix[i][i] = diagonal[i];
    }
}

void DiagonalMatrix::transpose() {
    // Transposing a diagonal matrix does nothing, so no implementation needed.
}

std::pair<int, int> DiagonalMatrix::getShape() const {
    return {size, size};
}

int DiagonalMatrix::getNNZ() const {
    return diagonal.size();
}

double DiagonalMatrix::getElement(int row, int col) const {
    if (row == col && row < size) {
        return diagonal[row];
    }
    return 0.0;
}

} // namespace sparsematrix
