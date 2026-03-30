#pragma once

struct Queue {
    int head, tail;
    int size;
    int *data;
};

Queue queue_new(int A[], int size);
void  enqueue(Queue *Q, int x);
int   dequeue(Queue *Q);