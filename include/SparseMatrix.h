#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <vector>
#include <string>
#include <utility>

namespace sparsematrix {

class SparseMatrix {
public:
    virtual ~SparseMatrix() = default;

    virtual SparseMatrix* convertTo(const std::string& format) const = 0;
    virtual void toDense(std::vector<std::vector<double>>& denseMatrix) const = 0;
    virtual void transpose() = 0;
    virtual std::pair<int, int> getShape() const = 0;
    virtual int getNNZ() const = 0;

    static SparseMatrix* fromDense(const std::vector<std::vector<double>>& denseMatrix, const std::string& format);
};

} // namespace sparsematrix

#endif // SPARSEMATRIX_H
