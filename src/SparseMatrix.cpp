// fromDense: Implements the factory method to create a sparse matrix from a dense matrix based on the specified format.


#include "SparseMatrix.h"
#include "CSRMatrix.h"
#include "COOMatrix.h"
#include "CSCMatrix.h"
#include "DiagonalMatrix.h"
#include <stdexcept>

namespace sparsematrix {

SparseMatrix* SparseMatrix::fromDense(const std::vector<std::vector<double>>& denseMatrix, const std::string& format) {
    if (format == "CSR") {
        return new CSRMatrix(denseMatrix);
    } else if (format == "CSC") {
        return new CSCMatrix(denseMatrix);
    } else if (format == "COO") {
        return new COOMatrix(denseMatrix);
    } else if (format == "Diagonal") {
        return new DiagonalMatrix(denseMatrix);
    } else {
        throw std::invalid_argument("Unsupported format: " + format);
    }
}

} // namespace sparsematrix