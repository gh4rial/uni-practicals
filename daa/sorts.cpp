#include <cstdlib>
#include <iostream>

#include "sorts.hpp"

#define HEAP_LEFT(i)   (((i)    << 1) + 1)
#define HEAP_RIGHT(i)  (((i)    << 1) + 2)
#define HEAP_PARENT(i) (((i)-1) >> 1)

#define SWAP(a, b) (t=(a), (a)=(b), (b)=t)

int partition(int A[], int start, int end, long *comparisons)
{
    int t;
    int pivot = A[end];
    int idx = start; // index for insertion in low side
    for (int i = start; i < end; i++) {
        if (A[i] <= pivot) {
            SWAP(A[idx], A[i]);
            idx++;
        }
        (*comparisons)++;
    }
    SWAP(A[idx], A[end]);

    return idx;
}

void quick_sort_(int A[], int start, int end, long *comparisons)
{
    if (start >= end) return;

    int pivot_idx = partition(A, start, end, comparisons);

    quick_sort_(A, start,       pivot_idx-1, comparisons);
    quick_sort_(A, pivot_idx+1, end, comparisons);
}

long quick_sort(int A[], int size)
{
    long comparisons = 0;
    quick_sort_(A, 0, size-1, &comparisons);
    return comparisons;

}

void max_heapify(int A[], int size, int index, long *comparisons)
{
    int t;

    int left    = HEAP_LEFT(index);
    int right   = HEAP_RIGHT(index);
    int largest = index;

    if (left < size) {
        (*comparisons)++;
        if (A[left] > A[largest]) {
            largest = left;
        }
    }

    if (right < size) {
        (*comparisons)++;
        if (A[right] > A[largest]) {
            largest = right;
        }
    }

    if (largest != index) {
        SWAP(A[largest], A[index]);
        max_heapify(A, size, largest, comparisons);
    }
}

void build_max_heap(int A[], int size, long *comparisons)
{
    for (int i = size/2 - 1; i >= 0; i--) {
        max_heapify(A, size, i, comparisons);
    }
}

long heap_sort(int A[], int size)
{
    int t;

    long comparisons = 0;

    build_max_heap(A, size, &comparisons);

    for (int end = size-1; end > 0; end--) {
        SWAP(A[end], A[0]);
        max_heapify(A, end, 0, &comparisons);
    }

    return comparisons;
}

void merge(int A[], int start, int mid, int end, long *comparisons)
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
        (*comparisons)++;
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

void merge_sort_(int A[], int start, int end, long *comparisons)
{
    if (start >= end) return;

    int mid = (start + end)/2;

    // divide + conquer
    merge_sort_(A, start, mid, comparisons);
    merge_sort_(A, mid+1, end, comparisons);

    // combine
    merge(A, start, mid, end, comparisons);
}

long merge_sort(int A[], int size)
{
    long comparisons = 0;
    merge_sort_(A, 0, size-1, &comparisons);
    return comparisons;
}

long insertion_sort(int A[], int size)
{
    long comparisons = 0;

    for (int i = 1; i < size; i++) {
        int x = A[i];
        int j = i;
        for (; j > 0; j--) {
            comparisons++;
            if (A[j-1] > x) {
                A[j] = A[j-1];
                continue;
            }
            break;
        }
        A[j] = x;
    }

    return comparisons;
}
