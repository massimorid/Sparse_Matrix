// CSCMatrix: A class representing a sparse matrix in CSC format.
// toDense: Converts the CSC matrix to a dense matrix.
// getNNZ: Returns the number of non-zero elements.
// getShape: Returns the shape of the matrix.

#ifndef CSCMATRIX_H
#define CSCMATRIX_H

#include "SparseMatrix.h"

namespace sparsematrix {

class CSCMatrix : public SparseMatrix {
public:
    CSCMatrix(const std::vector<std::vector<double>>& denseMatrix);

    void toDense(std::vector<std::vector<double>>& denseMatrix) const override;
    size_t getNNZ() const override;
    std::pair<size_t, size_t> getShape() const override;

private:
    std::vector<size_t> colPtrs;
    std::vector<size_t> rowIndices;
    std::vector<double> values;
    size_t numRows;
    size_t numCols;
};

} // namespace sparsematrix

#endif // CSCMATRIX_H