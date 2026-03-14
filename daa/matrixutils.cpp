#include <cstdlib>
#include <iostream>

#include "matrixutils.hpp"

Matrix matrix_add(Matrix A, Matrix B)
{
    if (A.rows != B.rows || A.cols != B.cols) {
        std::cout << "Error: Matrices must be of the same order to perform addition\n";
        std::exit(1);
    }

    Matrix result{};
    result.rows = A.rows;
    result.cols = A.cols;
    result.data = new int[result.rows*result.cols];
    result.stride = result.cols;

    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.cols; j++) {
            result.data[i*result.stride + j] = A.data[i*A.stride + j] + B.data[i*B.stride + j];
        }
    }

    return result;
}

Matrix matrix_sub(Matrix A, Matrix B)
{
    if (A.rows != B.rows || A.cols != B.cols) {
        std::cout << "Error: Matrices must be of the same order to perform subtraction\n";
        std::exit(1);
    }

    Matrix result{};
    result.rows = A.rows;
    result.cols = A.cols;
    result.data = new int[result.rows*result.cols];
    result.stride = result.cols;

    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.cols; j++) {
            result.data[i*result.stride + j] = A.data[i*A.stride + j] - B.data[i*B.stride + j];
        }
    }

    return result;
}

Matrix matrix_slice(Matrix M, int row_start, int col_start, int rows, int cols)
{
    if ((row_start < 0 || col_start < 0) || ((row_start+rows) > M.rows) || ((col_start+cols) > M.cols)) {
        std::cout << "Error: Index out of bounds\n";
        std::exit(1);
    }

    Matrix slice{};
    slice.stride = M.stride;
    slice.rows = rows;
    slice.cols = cols;
    slice.data = &M.data[row_start*M.stride + col_start];
    return slice;
}

Matrix get_matrix_from_user()
{
    Matrix m{};

    std::cout << "Enter number of rows: ";
    std::cin >> m.rows;
    if (m.rows < 1) {
        std::cout << "Error: Number of rows must be positive\n";
        std::exit(1);
    }
    std::cout << "Enter number of cols: ";
    std::cin >> m.cols;
    if (m.cols < 1) {
        std::cout << "Error: number of cols must be positive\n";
        std::exit(1);
    }

    m.data = new int[m.rows*m.cols];
    m.stride = m.cols;

    std::cout << "Enter matrix:\n";
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            std::cout << "[" << i << "][" << j << "]: ";
            std::cin >> m.data[i*m.stride + j];
        }
    }

    return m;
}

void print_matrix(Matrix m)
{
    for (int i = 0; i < m.rows; i++) {
        std::cout << "[";
        for (int j = 0; j < m.cols-1; j++) {
            std::cout << m.data[i*m.stride + j] << ' ';
        }
        std::cout << m.data[i*m.stride + m.cols-1] << "]\n";
    }
}