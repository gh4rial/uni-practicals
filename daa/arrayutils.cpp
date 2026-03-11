#include <iostream>
#include <cstdlib>

#include "arrayutils.h"

int get_array_from_user(int A[], int max)
{
    int n;

    std::cout << "Enter number of elements: ";
    std::cin >> n;

    if (n > max) {
        std::cout << "Exceeded max element count: " << max << '\n';
        std::exit(1);
    }

    for (int i = 0; i < n; i++) {
        std::cout << "A[" << i << "]: ";
        std::cin >> A[i];
    }

    return n;
}

int *get_array_from_user_unknown(int *out)
{
    int n;

    std::cout << "Enter number of elements: ";
    std::cin >> n;

    int *A = new int[n];

    for (int i = 0; i < n; i++) {
        std::cout << "A[" << i << "]: ";
        std::cin >> A[i];
    }

    *out = n;

    return A;
}

void print_array(int A[], int n)
{
    std::cout << '{';
    for (int i = 0; i < n-1; i++) {
        std::cout << A[i] << ' ';
    }
    std::cout << A[n-1] << '}';
    std::cout << '\n';
}
