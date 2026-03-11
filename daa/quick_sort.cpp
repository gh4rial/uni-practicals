#include <iostream>

#include "arrayutils.h"

#define SWAP(a, b) (t=(a), (a)=(b), (b)=t)

int comparisons = 0;

int partition(int A[], int start, int end)
{
    int t;
    int pivot = A[end];
    int idx = start; // index for insertion in low side
    for (int i = start; i < end; i++) {
        if (A[i] <= pivot) {
            SWAP(A[idx], A[i]);
            idx++;
        }
        comparisons++;
    }
    SWAP(A[idx], A[end]);

    return idx;
}

void quick_sort(int A[], int start, int end)
{
    if (start >= end) return;

    int pivot_idx = partition(A, start, end);

    quick_sort(A, start,       pivot_idx-1);
    quick_sort(A, pivot_idx+1, end);
}

int main()
{
    int B[] = {2, 7, 8, 1, 3, 5, 6, 4};
    int bn  = sizeof B / sizeof B[0];

    print_array(B, bn);

    quick_sort(B, 0, bn-1);
    print_array(B, bn);

    std::cout << "Comparisons: " << comparisons << '\n';

    return 0;
}

int main2()
{
    int n;
    int *A = get_array_from_user_unknown(&n);

    print_array(A, n);

    quick_sort(A, 0, n-1);
    print_array(A, n);

    return 0;
}
