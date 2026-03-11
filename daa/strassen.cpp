#include <cstdlib>
#include <iostream>

struct Matrix {
    int stride;
    int rows, cols;
    int *data;
};

void   print_matrix(Matrix M);
Matrix get_matrix_from_user();

int  matrix_get_elem(Matrix M, int row, int col);
void matrix_set_elem(Matrix M, int row, int col, int val);

Matrix  matrix_slice(Matrix M, int row_start, int col_start, int rows, int cols);

Matrix    matrix_add(Matrix A, Matrix B);
Matrix    matrix_sub(Matrix A, Matrix B);
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

Matrix matrix_add(Matrix A, Matrix B)
{
    Matrix result{};
    result.rows = A.rows;
    result.cols = A.cols;
    result.stride = A.stride;
    result.data = new int[result.rows*result.cols];

    if (A.rows != B.rows || A.cols != B.cols) {
        std::cout << "Error: Matrices must be of the same order to perform addition\n";
        std::exit(1);
    }

    for (int i = 1; i <= A.rows; i++) {
        for (int j = 1; j <= A.cols; j++) {
            int a = matrix_get_elem(A, i, j);
            int b = matrix_get_elem(B, i, j);
            int c = a + b;
            matrix_set_elem(result, i, j, c);
        }
    }

    return result;
}

Matrix matrix_sub(Matrix A, Matrix B)
{
    Matrix result{};
    result.rows = A.rows;
    result.cols = A.cols;
    result.stride = A.stride;
    result.data = new int[result.rows*result.cols];

    if (A.rows != B.rows || A.cols != B.cols) {
        std::cout << "Error: Matrices must be of the same order to perform addition\n";
        std::exit(1);
    }

    for (int i = 1; i <= A.rows; i++) {
        for (int j = 1; j <= A.cols; j++) {
            int a = matrix_get_elem(A, i, j);
            int b = matrix_get_elem(B, i, j);
            int c = a - b;
            matrix_set_elem(result, i, j, c);
        }
    }

    return result;
}

Matrix matrix_slice(Matrix M, int row_start, int col_start, int rows, int cols)
{
    Matrix slice{};
    slice.stride = M.stride;
    slice.rows = rows;
    slice.cols = cols;
    slice.data = &M.data[(row_start-1)*M.stride + col_start-1];
    return slice;
}

int matrix_get_elem(Matrix M, int row, int col)
{
    if ((row < 1 || row > M.rows) || (col < 1 || col > M.cols)) {
        std::cout << "Error: Invalid index\n";
        std::exit(1);
    }
    return M.data[(row-1)*M.stride + col-1];
}

void matrix_set_elem(Matrix M, int row, int col, int val)
{
    if ((row < 1 || row > M.rows) || (col < 1 || col > M.cols)) {
        std::cout << "Error: Invalid index\n";
        std::exit(1);
    }
    M.data[(row-1)*M.stride + col-1] = val;
}

Matrix strassen_mult(Matrix A, Matrix B)
{
    Matrix result{};
    result.rows = A.rows;
    result.cols = A.cols;
    result.stride = A.stride;
    result.data = new int[result.rows*result.cols];

    // base case
    if (A.rows == 1) {
        int A11 = matrix_get_elem(A, 1, 1);
        int B11 = matrix_get_elem(B, 1, 1);
        int C11 = A11 * B11;
        matrix_set_elem(result, 1, 1, C11);
        return result;
    }

    // divide into submatrices
    Matrix A11 = matrix_slice(A, 1, 1, A.rows/2, A.cols/2);
    Matrix A12 = matrix_slice(A, 1, A.cols/2+1, A.rows/2, A.cols/2);
    Matrix A21 = matrix_slice(A, A.rows/2+1, 1, A.rows/2, A.cols/2);
    Matrix A22 = matrix_slice(A, A.rows/2+1, A.cols/2+1, A.rows/2, A.cols/2);

    Matrix B11 = matrix_slice(B, 1, 1, B.rows/2, B.cols/2);
    Matrix B12 = matrix_slice(B, 1, B.cols/2+1, B.rows/2, B.cols/2);
    Matrix B21 = matrix_slice(B, B.rows/2+1, 1, B.rows/2, B.cols/2);
    Matrix B22 = matrix_slice(B, B.rows/2+1, B.cols/2+1, B.rows/2, B.cols/2);

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
    for (int i = 1; i <= A.rows/2; i++) {
        for (int j = 1; j <= A.cols/2; j++) {
            int val = matrix_get_elem(C11, i, j);
            matrix_set_elem(result, i, j, val);
        }
    }
    // top right
    for (int i = 1; i <= A.rows/2; i++) {
        for (int j = 1; j <= A.cols/2; j++) {
            int val = matrix_get_elem(C12, i, j);
            matrix_set_elem(result, i, A.cols/2 + j, val);
        }
    }
    // bottom left
    for (int i = 1; i <= A.rows/2; i++) {
        for (int j = 1; j <= A.cols/2; j++) {
            int val = matrix_get_elem(C21, i, j);
            matrix_set_elem(result, A.rows/2 + i, j, val);
        }
    }
    // bottom right
    for (int i = 1; i <= A.rows/2; i++) {
        for (int j = 1; j <= A.cols/2; j++) {
            int val = matrix_get_elem(C22, i, j);
            matrix_set_elem(result, A.rows/2 + i, A.cols/2 + j, val);
        }
    }

    return result;
}

Matrix get_matrix_from_user()
{
    Matrix m;

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
            std::cin >> m.data[i*m.cols + j];
        }
    }

    return m;
}

void print_matrix(Matrix m)
{
    for (int i = 0; i < m.rows; i++) {
        std::cout << "[";
        for (int j = 0; j < m.cols-1; j++) {
            std::cout << m.data[i*m.cols + j] << ' ';
        }
        std::cout << m.data[i*(m.cols) + m.cols-1] << "]\n";
    }
}
