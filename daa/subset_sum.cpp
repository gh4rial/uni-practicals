#include <cstdlib>
#include <iostream>

// TODO: THIS ROUTINE IS INCORRECT, NEEDS TO BE FIXED
int subset_sum(int A[], int size, int max_weight)
{
    int *table = new int[size * (max_weight + 1)];

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < max_weight; j++) {
            if (A[i] > j) {
                // copy value from below
                table[i*max_weight + j] = table[(i-1)*max_weight + j];
            } else {
                int a = table[(i-1)*max_weight + j];
                int b = A[i] + table[(i-1)*max_weight + (j - A[i])];
                table[i*max_weight + j] = (a > b) ? a : b;
            }
        }
    }

    return table[(size-1)*max_weight + (max_weight-1)];
}

int main()
{
    return 0;
}
