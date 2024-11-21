#include "CSCMatrix.h"
#include "COOMatrix.h"
#include "CSRMatrix.h"

namespace sparsematrix {

CSCMatrix::CSCMatrix(const std::vector<double>& values, const std::vector<int>& rowIndices,
                     const std::vector<int>& colPointers, int rows, int cols)
    : values(values), rowIndices(rowIndices), colPointers(colPointers), rows(rows), cols(cols) {}

SparseMatrix* CSCMatrix::convertTo(const std::string& format) const {
    if (format == "CSR") {
        // Conversion logic to CSR format
    } else if (format == "COO") {
        // Conversion logic to COO format
    }
    return nullptr;
}

void CSCMatrix::toDense(std::vector<std::vector<double>>& denseMatrix) const {
    denseMatrix.assign(rows, std::vector<double>(cols, 0));
    for (size_t col = 0; col < cols; ++col) {
        for (int idx = colPointers[col]; idx < colPointers[col + 1]; ++idx) {
            denseMatrix[rowIndices[idx]][col] = values[idx];
        }
    }
}

void CSCMatrix::transpose() {
    // Transpose logic here
}

std::pair<int, int> CSCMatrix::getShape() const {
    return {rows, cols};
}

int CSCMatrix::getNNZ() const {
    return values.size();
}

} // namespace sparsematrix
