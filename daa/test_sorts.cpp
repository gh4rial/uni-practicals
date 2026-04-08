#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

#include "sorts.hpp"

#define RUN_COUNT 100 // number of "runs"
#define RUN_SIZE  10  // number of "input instances" in each run

int merge_sort_copy(int A[], int size)
{
    int *B = new int[size];
    for (int i = 0; i < size; i++) {
        B[i] = A[i];
    }

    return merge_sort(B, size);
}

int heap_sort_copy(int A[], int size)
{
    int *B = new int[size];
    for (int i = 0; i < size; i++) {
        B[i] = A[i];
    }

    return heap_sort(B, size);
}

int quick_sort_copy(int A[], int size)
{
    int *B = new int[size];
    for (int i = 0; i < size; i++) {
        B[i] = A[i];
    }

    return quick_sort(B, size);
}

int insertion_sort_copy(int A[], int size)
{
    int *B = new int[size];
    for (int i = 0; i < size; i++) {
        B[i] = A[i];
    }

    return insertion_sort(B, size);
}

void generate_data(int A[], int size)
{
    for (int i = 0; i < size; i++) {
        A[i] = std::rand() % 1000 + 1; // 1 to 1000
    }
}

int main()
{
    // seeding with current time for random value generation
    std::srand((unsigned int)std::time(NULL));

    std::ofstream csv("sorts.csv");

    if (!csv) {
        std::cout << "Error: could not open csv file\n";
        return 1;
    }

    // columns
    csv << "size,insertion,merge,heap,quick,n log n\n";

    long avg_ins, avg_heap, avg_quick, avg_merge;

    for (int i = 0; i < RUN_COUNT; i++) {
        avg_ins = avg_heap = avg_quick = avg_merge = 0;

        int input_size = std::rand() % 971 + 30; // 30 to 1000

        std::cout << "Run #" << i+1 << '\n';
        std::cout << "Size: " << input_size << '\n';

        for (int j = 0; j < RUN_SIZE; j++) {
            int *A = new int[input_size];

            generate_data(A, input_size);

            avg_ins += insertion_sort_copy(A, input_size);
            avg_merge += merge_sort_copy(A, input_size);
            avg_heap += heap_sort_copy(A, input_size);
            avg_quick += quick_sort_copy(A, input_size);
        }

        std::cout << "  Average insertion sort comparisons: " << ((double)avg_ins)/RUN_SIZE << '\n';
        std::cout << "  Average merge sort comparisons: " << ((double)avg_merge)/RUN_SIZE << '\n';
        std::cout << "  Average heap sort comparisons: " << ((double)avg_heap)/RUN_SIZE << '\n';
        std::cout << "  Average quick sort comparisons: " << ((double)avg_quick)/RUN_SIZE << '\n';

        csv << input_size                   << ','
            << ((double)avg_ins)/RUN_SIZE   << ','
            << ((double)avg_merge)/RUN_SIZE << ','
            << ((double)avg_heap)/RUN_SIZE  << ','
            << ((double)avg_quick)/RUN_SIZE << ','
            << input_size * std::log2(input_size) << '\n';
    }

    return 0;
}