#pragma once

struct Queue {
    int head, tail;
    int size;
    int *data;
};

Queue queue_new(int A[], int size);
void  queue_enqueue(Queue *Q, int x);
int   queue_dequeue(Queue *Q);