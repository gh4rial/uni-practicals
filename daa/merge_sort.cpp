#include <iostream>

#include "arrayutils.h"

int comparisons = 0;

void merge(int A[], int start, int mid, int end)
{
    int lsize = mid - start + 1;
    int rsize = end - mid; // end-mid = end-(mid+1)+1

    // copy elements into temporary storage
    int *L = new int[lsize];
    for (int i = 0; i < lsize; i++) {
        L[i] = A[start+i];
    }
    int *R = new int[rsize];
    for (int i = 0; i < rsize; i++) {
        R[i] = A[(mid+1)+i];
    }

    int i = 0;     // left index
    int j = 0;     // right index
    int k = start; // index into main array
    while (i < lsize && j < rsize) {
        comparisons++;
        // copy smallest element into main array
        if (L[i] <= R[j]) {
            A[k++] = L[i++];
        } else {
            A[k++] = R[j++];
        }
    }
    // copy leftover elements, only one of these will run
    while (i < lsize) {
        A[k++] = L[i++];
    }
    while (j < rsize) {
        A[k++] = R[j++];
    }
}

void merge_sort(int A[], int start, int end)
{
    if (start >= end) return;

    int mid = (start + end)/2;

    // divide + conquer
    merge_sort(A, start, mid);
    merge_sort(A, mid+1, end);

    // combine
    merge(A, start, mid, end);
}

int main()
{
    int n;
    int *A = get_array_from_user_unknown(&n);

    std::cout << "Got array: ";
    print_array(A, n);

    std::cout << "Sorting array...\n";
    merge_sort(A, 0, n-1);

    std::cout << "Sorted array: ";
    print_array(A, n);

    std::cout << "Comparisons: " << comparisons << '\n';

    return 0;
}
