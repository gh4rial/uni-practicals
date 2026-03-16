#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

#include "sorts.hpp"

int main()
{
    // seeding with current time for random value generation
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::ofstream csv("sorts.csv");
    if (!csv) {
        std::cout << "Error: could not open file\n";
        return 1;
    }

    // columns
    csv << "size,insertion,merge,heap,quick,nlogn\n";

    int input_sizes[10];
    int *inputs[10];

    // populate arrays
    for (int i = 0; i < 10; i++) {
        input_sizes[i] = std::rand() % 971 + 30; // 30 to 1000
        inputs[i] = new int[input_sizes[i]];

        for (int j = 0; j < input_sizes[i]; j++) {
            inputs[i][j] = std::rand() % 100 + 1; // 1 to 100
        }
    }

    long ins_cmps = 0;
    long merge_cmps = 0;
    long heap_cmps = 0;
    long quick_cmps = 0;

    for (int i = 0; i < 10; i++) {
        // duplicate input values for each sort
        int *A = new int[input_sizes[i]];
        int *B = new int[input_sizes[i]];
        int *C = new int[input_sizes[i]];
        int *D = new int[input_sizes[i]];

        for (int j = 0; j < input_sizes[i]; j++) {
            A[j] = inputs[i][j];
            B[j] = inputs[i][j];
            C[j] = inputs[i][j];
            D[j] = inputs[i][j];
        }

        ins_cmps   = insertion_sort(A, input_sizes[i]);
        merge_cmps = merge_sort(B, input_sizes[i]);
        heap_cmps  = heap_sort(C, input_sizes[i]);
        quick_cmps = quick_sort(D, input_sizes[i]);

        csv << input_sizes[i]    << ','
            << ins_cmps          << ','
            << merge_cmps        << ','
            << heap_cmps         << ','
            << quick_cmps        << ','
            << input_sizes[i]*std::log2(input_sizes[i]) << '\n';
    }

    return 0;
}
