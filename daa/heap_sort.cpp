#include <iostream>

#include "arrayutils.h"

#define HEAP_LEFT(i)   (((i)    << 1) + 1)
#define HEAP_RIGHT(i)  (((i)    << 1) + 2)
#define HEAP_PARENT(i) (((i)-1) >> 1)

#define SWAP(a, b)     (t=(a), (a)=(b), (b)=t)

int comparisons = 0;

void sift_down(int A[], int root, int end)
{
    int t;

    while (HEAP_LEFT(root) < end) {
        int child = HEAP_LEFT(root);

        comparisons++;
        if (child+1 < end && A[child] < A[child+1]) {
            child = child+1;
        }

        comparisons++;
        if (A[root] < A[child]) {
            SWAP(A[root], A[child]);
            root = child;
        } else {
            return;
        }
    }
}

void heapify(int A[], int count)
{
    int start = HEAP_PARENT(count-1) + 1;

    while (start > 0) {
        start--;
        sift_down(A, start, count);
    }
}

void heap_sort2(int A[], int count)
{
    int t;

    heapify(A, count);

    int end = count;

    while (end > 1) {
        end--;
        SWAP(A[end], A[0]);
        sift_down(A, 0, end);
    }
}

void max_heapify(int A[], int n, int index)
{
    int t;

    int left    = HEAP_LEFT(index);
    int right   = HEAP_RIGHT(index);
    int largest = index;

    if (left < n && A[left] > A[largest]) {
        largest = left;
    }

    if (right < n && A[right] > A[largest]) {
        largest = right;
    }

    if (largest != index) {
        SWAP(A[largest], A[index]);
        max_heapify(A, n, largest);
    }
}

void build_max_heap(int A[], int n)
{
    for (int i = n/2; i >= 0; i--) {
        max_heapify(A, n, i);
    }
}

void heap_sort(int A[], int n)
{
    int t;

    build_max_heap(A, n);

    int end = n;

    while (end > 1) {
        end--;
        SWAP(A[end], A[0]);
        max_heapify(A, end, 0);
    }
}

// heap_sort:  {8, 7, 4, 6, 4, 3, 1, 2, 5}
// heap_sort2: {8, 7, 4, 6, 4, 3, 1, 2, 5}

int main()
{
    int A[] = {2, 4, 4, 5, 8, 3, 1, 6, 7};
    int n   = sizeof A / sizeof A[0];

    print_array(A, n);

    heap_sort2(A, n);
    print_array(A, n);

    std::cout << "Comparisons: " << comparisons << '\n';

    return 0;
}
