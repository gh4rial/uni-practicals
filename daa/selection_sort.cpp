#include <iostream>

#include "arrayutils.h"

#define SWAP(a, b) (t=(a), (a)=(b), (b)=t)

int comparisons = 0;

void selection_sort(int A[], int size)
{
    int t;
    for (int i = 0; i < size-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < size; j++) {
            comparisons++;
            if (A[j] < A[min_idx]) {
                min_idx = j;
            }
        }
        SWAP(A[i], A[min_idx]);
    }
}

int main()
{
    int A[] = {4, 2, 7, 3, 5, 6, 7, 9, 1, 0};
    int n   = sizeof A / sizeof A[0];

    print_array(A, n);

    selection_sort(A, n);
    print_array(A, n);

    std::cout << "comparisons: " << comparisons << '\n';

    return 0;
}
