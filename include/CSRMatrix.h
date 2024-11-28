// CSRMatrix: A class representing a sparse matrix in CSR format.
// toDense: Converts the CSR matrix to a dense matrix.
// getNNZ: Returns the number of non-zero elements.
// getShape: Returns the shape of the matrix.

#ifndef CSRMATRIX_H
#define CSRMATRIX_H

#include "SparseMatrix.h"

namespace sparsematrix {

class CSRMatrix : public SparseMatrix {
public:
    CSRMatrix(const std::vector<std::vector<double>>& denseMatrix);

    void toDense(std::vector<std::vector<double>>& denseMatrix) const override;
    size_t getNNZ() const override;
    std::pair<size_t, size_t> getShape() const override;
    double getElement(size_t row, size_t col) const;

private:
    std::vector<size_t> rowPtrs;
    std::vector<size_t> colIndices;
    std::vector<double> values;
    size_t numRows;
    size_t numCols;
};

} // namespace sparsematrix

#endif // CSRMATRIX_H