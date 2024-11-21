#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

const int rows = 3;
const int columns = 4;

int matrix[3][4] = {
    {0, 5, 2, 0},
    {0, 0, 0, 8},
    {0, 3, 6, 0}
};

void printMatrix(int (&matrix)[rows][columns]) { // this is the function to print the dense matirex
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl; 
    }
}


tuple<vector<int>, vector<int>, vector<int>> formatConversionCSC(int (&matrix)[rows][columns]) { // here you convert matrix to CSC format
    vector<int> vals;
    vector<int> row_indices;
    vector<int> col_ptr(columns + 1, 0); // init with zero, +1 for the extra column pointer

   
    for (int col = 0; col < columns; ++col) { // do an iteration by column first
        for (int row = 0; row < rows; ++row) {
            if (matrix[row][col] != 0) {
                vals.push_back(matrix[row][col]);  // stire the non-zero value
                row_indices.push_back(row);       // store the row index
            }
        }
        col_ptr[col + 1] = vals.size(); // point to the start of the next column
    }

    return {vals, row_indices, col_ptr};
}

int main() {
    cout << "the matrix:" << endl;
    printMatrix(matrix);

 
    auto [vals, row_indices, col_ptr] = formatConversionCSC(matrix);   // convert to CSC format

    cout << "\nnon-zero values (vals): "; // csc representation
    for (int v : vals) {
        cout << v << " ";
    }

    cout << "\nrow indices (rows): ";
    for (int r : row_indices) {
        cout << r << " ";
    }

    cout << "\ncolumn pointers (col_ptr): ";
    for (int c : col_ptr) {
        cout << c << " ";
    }

    return 0;
}
