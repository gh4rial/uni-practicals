#include <cstdlib>
#include <iostream>

#include "matrixutils.hpp"

Matrix strassen_mult(Matrix A, Matrix B);

int main()
{
    Matrix a = get_matrix_from_user();
    Matrix b = get_matrix_from_user();

    Matrix result = strassen_mult(a, b);

    std::cout << "Multiplying\n";
    print_matrix(a);
    std::cout << " and\n";
    print_matrix(b);
    std::cout << " using Strassen's algorithm, we get\n";
    print_matrix(result);

    return 0;
}

bool is_power_of_2(int x)
{
    return x > 0 && (x & (x-1)) == 0;
}

Matrix strassen_mult(Matrix A, Matrix B)
{
    if (A.cols != B.rows || A.rows != B.cols || A.rows != B.rows)
    {
        std::cout << "Error: Strassen multiplication requires square matrices of the same order\n";
        std::exit(1);
    }

    // guaranted that A.rows == A.cols == B.rows == B.cols
    if (!is_power_of_2(A.rows)) {
        std::cout << "Error: Strassen multiplication requires matrices to be of order NxN where N is a power of two\n";
        std::exit(1);
    }

    Matrix result{};
    result.rows = A.rows;
    result.cols = A.cols;
    result.data = new int[result.rows*result.cols];
    result.stride = result.cols;

    // base case
    if (A.rows == 1) {
        result.data[0] = A.data[0] * B.data[0];
        return result;
    }

    // divide into submatrices
    Matrix A11 = matrix_slice(A, 0, 0, A.rows/2, A.cols/2);
    Matrix A12 = matrix_slice(A, 0, A.cols/2, A.rows/2, A.cols/2);
    Matrix A21 = matrix_slice(A, A.rows/2, 0, A.rows/2, A.cols/2);
    Matrix A22 = matrix_slice(A, A.rows/2, A.cols/2, A.rows/2, A.cols/2);

    Matrix B11 = matrix_slice(B, 0, 0, B.rows/2, B.cols/2);
    Matrix B12 = matrix_slice(B, 0, B.cols/2, B.rows/2, B.cols/2);
    Matrix B21 = matrix_slice(B, B.rows/2, 0, B.rows/2, B.cols/2);
    Matrix B22 = matrix_slice(B, B.rows/2, B.cols/2, B.rows/2, B.cols/2);

    // computations for strassen's:
    // M1 = (A11 + A22)(B11 + B22)
    // M2 = (A21 + A22)B11
    // M3 = A11(B12 - B22)
    // M4 = A22(B21 - B11)
    // M5 = (A11 + A12)B22
    // M6 = (A21 - A11)(B11 + B12)
    // M7 = (A12 - A22)(B21 + B22)
    // C11 = M1 + M4 - M5 + M7
    // C12 = M3 + M5
    // C21 = M2 + M4
    // C22 = M1 - M2 + M3 + M6

    // conquer smaller problems
    Matrix M1 = strassen_mult(matrix_add(A11, A22), matrix_add(B11, B22));
    Matrix M2 = strassen_mult(matrix_add(A21, A22), B11);
    Matrix M3 = strassen_mult(A11, matrix_sub(B12, B22));
    Matrix M4 = strassen_mult(A22, matrix_sub(B21, B11));
    Matrix M5 = strassen_mult(matrix_add(A11, A12), B22);
    Matrix M6 = strassen_mult(matrix_sub(A21, A11), matrix_add(B11, B12));
    Matrix M7 = strassen_mult(matrix_sub(A12, A22), matrix_add(B21, B22));

    Matrix C11 = matrix_add(matrix_sub(matrix_add(M1, M4), M5), M7);
    Matrix C12 = matrix_add(M3, M5);
    Matrix C21 = matrix_add(M2, M4);
    Matrix C22 = matrix_add(matrix_add(matrix_sub(M1, M2), M3), M6);

    // combine into
    //   [C11 C12]
    //   [C21 C22]
    // copy each quadrant into the result matrix
    // top left
    for (int i = 0; i < A.rows/2; i++) {
        for (int j = 0; j < A.cols/2; j++) {
            result.data[i*result.stride + j] = C11.data[i*C11.stride + j];
        }
    }
    // top right
    for (int i = 0; i < A.rows/2; i++) {
        for (int j = 0; j < A.cols/2; j++) {
            result.data[i*result.stride + (j+A.cols/2)] = C12.data[i*C12.stride + j];
        }
    }
    // bottom left
    for (int i = 0; i < A.rows/2; i++) {
        for (int j = 0; j < A.cols/2; j++) {
            result.data[(i+A.rows/2)*result.stride + j] = C21.data[i*C21.stride + j];
        }
    }
    // bottom right
    for (int i = 0; i < A.rows/2; i++) {
        for (int j = 0; j < A.cols/2; j++) {
            result.data[(i+A.rows/2)*result.stride + (j+A.cols/2)] = C22.data[i*C22.stride + j];
        }
    }

    return result;
}