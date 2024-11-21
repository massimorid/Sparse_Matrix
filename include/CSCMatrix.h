#ifndef CSCMATRIX_H
#define CSCMATRIX_H

#include "SparseMatrix.h"

namespace sparsematrix {

class CSCMatrix : public SparseMatrix {
private:
    std::vector<double> values;
    std::vector<int> rowIndices;
    std::vector<int> colPointers;
    int rows, cols;

public:
    CSCMatrix(const std::vector<double>& values, const std::vector<int>& rowIndices,
              const std::vector<int>& colPointers, int rows, int cols);
    explicit CSCMatrix(const std::vector<std::vector<double>>& denseMatrix);

    SparseMatrix* convertTo(const std::string& format) const override;
    void toDense(std::vector<std::vector<double>>& denseMatrix) const override;
    void transpose() override;
    std::pair<int, int> getShape() const override;
    int getNNZ() const override;
};

} // namespace sparsematrix

#endif // CSCMATRIX_H

