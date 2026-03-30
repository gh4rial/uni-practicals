#include <cstdlib>
#include <iostream>

#include "queueutils.hpp"

Queue queue_new(int A[], int size)
{
    Queue queue{};
    queue.data = A;
    queue.size = size;
    queue.head = queue.tail = 0;
    return queue;
}

void enqueue(Queue *Q, int x)
{
    Q->data[Q->tail] = x;
    if (Q->tail == (Q->size - 1)) {
        Q->tail = 0;
    } else {
        Q->tail++;
    }
}

int dequeue(Queue *Q)
{
    int x = Q->data[Q->head];
    if (Q->head == (Q->size - 1)) {
        Q->head = 0;
    } else {
        Q->head++;
    }
    return x;
}