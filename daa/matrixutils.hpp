#pragma once

struct Matrix {
    int stride;
    int rows, cols;
    int *data;
};

// all indices are 0-based
Matrix matrix_add(Matrix A, Matrix B);
Matrix matrix_sub(Matrix A, Matrix B);
Matrix matrix_slice(Matrix M, int row_start, int col_start, int rows, int cols);
void print_matrix(Matrix M);
Matrix get_matrix_from_user();