#include "COOMatrix.h"

namespace sparsematrix {

COOMatrix::COOMatrix(const std::vector<double>& values, const std::vector<int>& rowIndices,
                     const std::vector<int>& colIndices, int rows, int cols)
    : values(values), rowIndices(rowIndices), colIndices(colIndices), rows(rows), cols(cols) {}

SparseMatrix* COOMatrix::convertTo(const std::string& format) const {
    if (format == "CSR") {
        // Conversion logic to CSR
    }
    return nullptr;
}

void COOMatrix::toDense(std::vector<std::vector<double>>& denseMatrix) const {
    denseMatrix.assign(rows, std::vector<double>(cols, 0));
    for (size_t i = 0; i < values.size(); ++i) {
        denseMatrix[rowIndices[i]][colIndices[i]] = values[i];
    }
}

void COOMatrix::transpose() {
    // Transpose logic here
}

std::pair<int, int> COOMatrix::getShape() const {
    return {rows, cols};
}

int COOMatrix::getNNZ() const {
    return values.size();
}

void COOMatrix::sortIndices() {
    // Sorting logic here
}

} // namespace sparsematrix
