#include <cstdlib>
#include <iostream>

#include "queueutils.hpp"

Queue queue_new(int A[], int size)
{
    Queue Q{};
    Q.data = A;
    Q.size = size;
    Q.head = Q.tail = 0;
    return Q;
}

void queue_enqueue(Queue *Q, int x)
{
    Q->data[Q->tail] = x;
    if (Q->tail == (Q->size - 1)) {
        Q->tail = 0;
    } else {
        Q->tail++;
    }
}

int queue_dequeue(Queue *Q)
{
    int x = Q->data[Q->head];
    if (Q->head == (Q->size - 1)) {
        Q->head = 0;
    } else {
        Q->head++;
    }
    return x;
}