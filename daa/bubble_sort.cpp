#include <iostream>

#include "arrayutils.h"

#define SWAP(a, b) (t=(a), (a)=(b), (b)=t)

int comparisons1 = 0;
int comparisons2 = 0;

void bubble_sort2(int A[], int size)
{
    int t;
    int iters = 0;
    bool swapped = true;

    while (swapped) {
        iters++;
        swapped = false;

        for (int i = 1; i < size; i++) {
            comparisons2++;
            if (A[i] < A[i-1]) {
                SWAP(A[i], A[i-1]);
                swapped = true;
            }
        }
    }

    std::cout << "bubble_sort2 iterations: " << iters << '\n';
}

void bubble_sort(int A[], int size)
{
    int t;
    int iters = 0;
    for (int i = 0; i < size-1; i++) {
        iters++;
        for (int j = 0; j < size-1 - i; j++) {
            comparisons1++;
            if (A[j] > A[j+1]) {
                SWAP(A[j], A[j+1]);
            }
        }
    }

    std::cout << "bubble sort iterations: " << iters << '\n';
}

int main()
{
    int A[] = {4, 2, 7, 3, 5, 6, 7, 9, 1, 0};
    int n   = sizeof A / sizeof A[0];

    int B[] = {4, 2, 7, 3, 5, 6, 7, 9, 1, 0};

    std::cout << "A:\n";
    print_array(A, n);

    bubble_sort(A, n);
    print_array(A, n);

    std::cout << "comparisons1: " << comparisons1 << '\n';

    std::cout << "B:\n";
    print_array(B, n);

    bubble_sort2(B, n);
    print_array(B, n);

    std::cout << "comparisons2: " << comparisons2 << '\n';

    return 0;
}
