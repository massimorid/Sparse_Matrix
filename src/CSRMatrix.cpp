#include "CSRMatrix.h"
#include "COOMatrix.h"

namespace sparsematrix {

CSRMatrix::CSRMatrix(const std::vector<double>& values, const std::vector<int>& colIndices,
                     const std::vector<int>& rowPointers, int rows, int cols)
    : values(values), colIndices(colIndices), rowPointers(rowPointers), rows(rows), cols(cols) {}

SparseMatrix* CSRMatrix::convertTo(const std::string& format) const {
    if (format == "COO") {
        return new COOMatrix(values, rowPointers, colIndices, rows, cols);
    }
    return nullptr;
}

void CSRMatrix::toDense(std::vector<std::vector<double>>& denseMatrix) const {
    denseMatrix.assign(rows, std::vector<double>(cols, 0));
    for (int i = 0; i < rows; ++i) {
        for (int j = rowPointers[i]; j < rowPointers[i + 1]; ++j) {
            denseMatrix[i][colIndices[j]] = values[j];
        }
    }
}

void CSRMatrix::transpose() {
    // Transpose logic here
}

std::pair<int, int> CSRMatrix::getShape() const {
    return {rows, cols};
}

int CSRMatrix::getNNZ() const {
    return values.size();
}

std::vector<double> CSRMatrix::dot(const std::vector<double>& vector) const {
    std::vector<double> result(rows, 0);
    for (int i = 0; i < rows; ++i) {
        for (int j = rowPointers[i]; j < rowPointers[i + 1]; ++j) {
            result[i] += values[j] * vector[colIndices[j]];
        }
    }
    return result;
}

} // namespace sparsematrix
