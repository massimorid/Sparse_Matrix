#ifndef CSR_MATRIX_H
#define CSR_MATRIX_H

#include <vector>
#include <utility>

namespace sparsematrix {

class CSRMatrix {
private:
    size_t numRows; // Number of rows
    size_t numCols; // Number of columns
    std::vector<size_t> rowPtrs;    // Row pointers
    std::vector<size_t> colIndices; // Column indices
    std::vector<double> values;     // Non-zero values

public:
    // Constructor to create a CSR matrix from a dense matrix
    explicit CSRMatrix(const std::vector<std::vector<double>>& denseMatrix);

    // Converts the CSR matrix back to a dense matrix
    void toDense(std::vector<std::vector<double>>& denseMatrix) const;

    // Get the number of non-zero elements
    size_t getNNZ() const;

    // Get the shape of the matrix as {rows, columns}
    std::pair<size_t, size_t> getShape() const;

    // Get a specific element from the matrix
    double getElement(size_t row, size_t col) const;

    // Public getters for internal attributes
    const std::vector<size_t>& getRowPtrs() const { return rowPtrs; }
    const std::vector<size_t>& getColIndices() const { return colIndices; }
    const std::vector<double>& getValues() const { return values; }
};

// Function to multiply two sparse matrices
std::vector<std::vector<double>> multiply_sparse_matrices(const CSRMatrix& mat1, const CSRMatrix& mat2);

} // namespace sparsematrix

#endif // CSR_MATRIX_H