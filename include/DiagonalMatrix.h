#ifndef DIAGONALMATRIX_H
#define DIAGONALMATRIX_H

#include "SparseMatrix.h"

namespace sparsematrix {

class DiagonalMatrix : public SparseMatrix {
private:
    std::vector<double> diagonal;
    int size;

public:
    DiagonalMatrix(const std::vector<double>& diagonal);

    SparseMatrix* convertTo(const std::string& format) const override;
    void toDense(std::vector<std::vector<double>>& denseMatrix) const override;
    void transpose() override;
    std::pair<int, int> getShape() const override;
    int getNNZ() const override;

    double getElement(int row, int col) const;
};

} // namespace sparsematrix

#endif // DIAGONALMATRIX_H
