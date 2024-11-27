#include "MatrixOperations.h"
#include <stdexcept>
#include <unordered_map>
#include <omp.h>
#include <algorithm>
#include <future>

namespace sparsematrix {

// Initialize static member
size_t MatrixOperations::chunkSize = 100;

int MatrixOperations::getOptimalThreadCount(int requestedThreads) {
    if (requestedThreads <= 0) {
        return std::thread::hardware_concurrency();
    }
    return std::min(requestedThreads, static_cast<int>(std::thread::hardware_concurrency()));
}

SparseMatrix* MatrixOperations::multiply(const SparseMatrix* A, const SparseMatrix* B, 
                                       const std::string& resultFormat,
                                       int numThreads) {
    auto shapeA = A->getShape();
    auto shapeB = B->getShape();
    
    if (shapeA.second != shapeB.first) {
        throw std::invalid_argument("Matrix dimensions mismatch for multiplication");
    }

    numThreads = getOptimalThreadCount(numThreads);
    omp_set_num_threads(numThreads);
    
    const CSRMatrix* csrA = dynamic_cast<const CSRMatrix*>(A);
    const CSRMatrix* csrB = dynamic_cast<const CSRMatrix*>(B);

    if (csrA && csrB) {
        return multiplyCSR(csrA, csrB, numThreads);
    }

    // Fallback to parallel dense multiplication
    std::vector<std::vector<double>> denseA, denseB, denseResult;
    
    #pragma omp parallel sections
    {
        #pragma omp section
        { A->toDense(denseA); }
        #pragma omp section
        { B->toDense(denseB); }
    }
    
    denseResult.resize(shapeA.first, std::vector<double>(shapeB.second, 0.0));
    
    #pragma omp parallel for collapse(2) schedule(dynamic, chunkSize)
    for (size_t i = 0; i < shapeA.first; ++i) {
        for (size_t j = 0; j < shapeB.second; ++j) {
            double sum = 0.0;
            #pragma omp simd reduction(+:sum)
            for (size_t k = 0; k < shapeA.second; ++k) {
                sum += denseA[i][k] * denseB[k][j];
            }
            denseResult[i][j] = sum;
        }
    }
    
    return SparseMatrix::fromDense(denseResult, resultFormat);
}

CSRMatrix* MatrixOperations::multiplyCSR(const CSRMatrix* A, const CSRMatrix* B, int numThreads) {
    auto shapeA = A->getShape();
    auto shapeB = B->getShape();

    std::vector<std::vector<std::pair<size_t, double>>> results(shapeA.first);
    
    #pragma omp parallel for schedule(dynamic, chunkSize) num_threads(numThreads)
    for (size_t i = 0; i < shapeA.first; ++i) {
        std::unordered_map<size_t, double> tempRow;
        
        for (size_t k = A->rowPtrs[i]; k < A->rowPtrs[i + 1]; ++k) {
            size_t a_col = A->colIndices[k];
            double a_val = A->values[k];
            
            for (size_t j = B->rowPtrs[a_col]; j < B->rowPtrs[a_col + 1]; ++j) {
                size_t b_col = B->colIndices[j];
                double b_val = B->values[j];
                tempRow[b_col] += a_val * b_val;
            }
        }
        
        std::vector<std::pair<size_t, double>> rowElements(tempRow.begin(), tempRow.end());
        std::sort(rowElements.begin(), rowElements.end());
        results[i] = std::move(rowElements);
    }

    // Construct final CSR matrix
    std::vector<size_t> rowPtrs(shapeA.first + 1);
    std::vector<size_t> colIndices;
    std::vector<double> values;

    rowPtrs[0] = 0;
    for (size_t i = 0; i < results.size(); ++i) {
        rowPtrs[i + 1] = rowPtrs[i] + results[i].size();
        for (const auto& elem : results[i]) {
            colIndices.push_back(elem.first);
            values.push_back(elem.second);
        }
    }

    return new CSRMatrix(shapeA.first, shapeB.second, rowPtrs, colIndices, values);
}

std::vector<double> MatrixOperations::multiply(const SparseMatrix* A, 
                                             const std::vector<double>& x,
                                             int numThreads) {
    auto shape = A->getShape();
    if (shape.second != x.size()) {
        throw std::invalid_argument("Matrix and vector dimensions mismatch for multiplication");
    }

    numThreads = getOptimalThreadCount(numThreads);
    omp_set_num_threads(numThreads);

    const CSRMatrix* csrA = dynamic_cast<const CSRMatrix*>(A);
    if (csrA) {
        return multiplyCSRVector(csrA, x, numThreads);
    }

    std::vector<std::vector<double>> dense;
    A->toDense(dense);
    std::vector<double> result(shape.first, 0.0);
    
    #pragma omp parallel for schedule(dynamic, chunkSize)
    for (size_t i = 0; i < shape.first; ++i) {
        double sum = 0.0;
        #pragma omp simd reduction(+:sum)
        for (size_t j = 0; j < shape.second; ++j) {
            sum += dense[i][j] * x[j];
        }
        result[i] = sum;
    }

    return result;
}

std::vector<double> MatrixOperations::multiplyCSRVector(const CSRMatrix* A, 
                                                      const std::vector<double>& x,
                                                      int numThreads) {
    auto shape = A->getShape();
    std::vector<double> result(shape.first, 0.0);

    #pragma omp parallel for schedule(dynamic, chunkSize) num_threads(numThreads)
    for (size_t i = 0; i < shape.first; ++i) {
        double sum = 0.0;
        #pragma omp simd reduction(+:sum)
        for (size_t k = A->rowPtrs[i]; k < A->rowPtrs[i + 1]; ++k) {
            sum += A->values[k] * x[A->colIndices[k]];
        }
        result[i] = sum;
    }

    return result;
}

} // namespace sparsematrix 
