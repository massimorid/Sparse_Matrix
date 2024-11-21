#ifndef COOMATRIX_H
#define COOMATRIX_H

#include "SparseMatrix.h"

namespace sparsematrix {

class COOMatrix : public SparseMatrix {
private:
    std::vector<double> values;
    std::vector<int> rowIndices;
    std::vector<int> colIndices;
    int rows, cols;

public:
    COOMatrix(const std::vector<double>& values, const std::vector<int>& rowIndices,
              const std::vector<int>& colIndices, int rows, int cols);

    SparseMatrix* convertTo(const std::string& format) const override;
    void toDense(std::vector<std::vector<double>>& denseMatrix) const override;
    void transpose() override;
    std::pair<int, int> getShape() const override;
    int getNNZ() const override;

    void sortIndices();
};

} // namespace sparsematrix

#endif // COOMATRIX_H
