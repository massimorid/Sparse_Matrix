#pragma once

#include "SparseMatrix.h"
#include "CSRMatrix.h"
#include "CSCMatrix.h"
#include "COOMatrix.h"
#include <vector>
#include <thread>

namespace sparsematrix {

class MatrixOperations {
public:
    // Matrix-Matrix multiplication with configurable number of threads
    static SparseMatrix* multiply(const SparseMatrix* A, const SparseMatrix* B, 
                                const std::string& resultFormat = "CSR",
                                int numThreads = -1);  // -1 means use all available threads
    
    // Matrix-Vector multiplication with configurable number of threads
    static std::vector<double> multiply(const SparseMatrix* A, 
                                      const std::vector<double>& x,
                                      int numThreads = -1);

    // Set the chunk size for parallel operations
    static void setChunkSize(size_t size) { chunkSize = size; }

private:
    static CSRMatrix* multiplyCSR(const CSRMatrix* A, const CSRMatrix* B, int numThreads);
    static std::vector<double> multiplyCSRVector(const CSRMatrix* A, 
                                               const std::vector<double>& x,
                                               int numThreads);
    
    static size_t chunkSize; // Chunk size for parallel processing
    static int getOptimalThreadCount(int requestedThreads);
};

} // namespace sparsematrix 
