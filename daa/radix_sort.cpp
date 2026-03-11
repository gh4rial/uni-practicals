#include <cmath>
#include <iostream>

#include "arrayutils.h"

// d - number of digits in each element of input
void radix_sort(int A[], int size, int d, int *out)
{
    int freqs[10]; // assuming base 10

    for (int i = 0; i < d; i++) {
        for (int j = 0; j < 10; j++) {
            freqs[j] = 0;
        }
        for (int j = 0; j < size; j++) {
            int idx = (A[j] / (int)std::pow(10, i)) % 10;
            freqs[idx]++;
        }
        for (int j = 1; j < 10; j++) {
            freqs[j] += freqs[j-1];
        }
        for (int j = size-1; j >= 0; j--) {
            int idx = (A[j] / (int)std::pow(10, i)) % 10;
            out[freqs[idx]-1] = A[j];
            freqs[idx]--;
        }
    }
}

int main()
{
    int A[] = {24, 25, 69, 32, 10, 19, 44, 57};
    int   n = sizeof A / sizeof A[0];

    print_array(A, n);

    int *B = new int[n];

    radix_sort(A, n, 2, B);
    print_array(B, n);

    return 0;
}
