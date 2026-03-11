#include <iostream>

#include "arrayutils.h"

// 'out' should be a pointer to the first element of an array of atleast 'size' elements
void count_sort(int A[], int size, int lim, int *out)
{
    // size = len of A[] (and out[])
    // lim  = upper limit on integer elements in A (i.e. 0 <= A[i] <= lim)
    int *freqs = new int[lim+1];

    for (int i = 0; i <= lim; i++) {
        freqs[i] = 0;
    }
    for (int i = 0; i < size; i++) {
        freqs[A[i]]++;
    }
    // accumulates the frequencies
    for (int i = 1; i <= lim; i++) {
        freqs[i] += freqs[i-1];
    }
    for (int i = size-1; i >= 0; i--) {
        out[freqs[A[i]]-1] = A[i];
        freqs[A[i]]--;
    }
}

int main()
{
    int A[] = {1, 4, 2, 8, 5, 7, 9, 3, 4, 6, 5};
    int   n = sizeof A / sizeof A[0];

    print_array(A, n);

    int *B = new int[n];

    count_sort(A, n, 10, B);
    print_array(B, n);

    return 0;
}
