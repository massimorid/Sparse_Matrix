#ifndef CSRMATRIX_H
#define CSRMATRIX_H

#include "SparseMatrix.h"

namespace sparsematrix {

class CSRMatrix : public SparseMatrix {
private:
    std::vector<double> values;
    std::vector<int> colIndices;
    std::vector<int> rowPointers;
    int rows, cols;

public:
    CSRMatrix(const std::vector<double>& values, const std::vector<int>& colIndices,
              const std::vector<int>& rowPointers, int rows, int cols);
    explicit CSRMatrix(const std::vector<std::vector<double>>& denseMatrix);

    SparseMatrix* convertTo(const std::string& format) const override;
    void toDense(std::vector<std::vector<double>>& denseMatrix) const override;
    void transpose() override;
    std::pair<int, int> getShape() const override;
    int getNNZ() const override;
};

} // namespace sparsematrix

#endif // CSRMATRIX_H
