// SparseMatrix: The base class for all sparse matrix types.
// fromDense: A factory method to create a sparse matrix from a dense matrix.
// toDense: A pure virtual method to convert a sparse matrix to a dense matrix.
// getNNZ: A pure virtual method to get the number of non-zero elements.
// getShape: A pure virtual method to get the shape of the matrix.

#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <vector>
#include <string>

namespace sparsematrix {

class SparseMatrix {
public:
    virtual ~SparseMatrix() = default;

    // Factory method to create a SparseMatrix from a dense matrix
    static SparseMatrix* fromDense(const std::vector<std::vector<double>>& denseMatrix, const std::string& format);

    // Pure virtual method to convert a sparse matrix to a dense matrix
    virtual void toDense(std::vector<std::vector<double>>& denseMatrix) const = 0;

    // Pure virtual method to get the number of non-zero elements
    virtual size_t getNNZ() const = 0;

    // Pure virtual method to get the shape of the matrix
    virtual std::pair<size_t, size_t> getShape() const = 0;
};

} // namespace sparsematrix

#endif // SPARSEMATRIX_H