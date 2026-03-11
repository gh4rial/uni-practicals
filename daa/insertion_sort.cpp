#include <iostream>

#include "arrayutils.h"

int comparisons = 0;

void insertion_sort(int *arr, int len);

int main()
{
    int A[] = {4, 2, 7, 3, 5, 6, 7, 9, 1, 0};
    int n   = sizeof A / sizeof A[0];

    std::cout << "Before sort:\n";
    print_array(A, n);

    insertion_sort(A, n);

    std::cout << "After sort:\n";
    print_array(A, n);

    std::cout << "Comparisons: " << comparisons << '\n';

    return 0;
}

void insertion_sort(int *arr, int len)
{
    std::cout << "Sorting using insertion sort...\n";

    for (int i = 1; i < len; i++) {
        int x = arr[i];
        int j = i;
        for (; j > 0 && arr[j-1] > x; j--) {
            comparisons++;
            arr[j] = arr[j-1];
        }
        arr[j] = x;
    }
}
