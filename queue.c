#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.c"

typedef struct Queue{
    vertex* arr[513];
    int head;
    int tail;
    int size;
} QueueNode;

void CreateQueueNode(Queue* queue1){
    int i;
    queue1->size = 512;
    queue1->head = queue1->tail = 1;
}

bool QueueEmptyNode(Queue* queue1){
    return (bool)(queue1->head == queue1->tail);
}

bool QueueFullNode(Queue* queue1){
    return (bool)(queue1->head == (queue1->tail + 1) % queue1->size);
}

vertex* QueueHeadNode(Queue* queue1){
    if (!QueueEmpty(queue1)){
        return queue1->arr[queue1->head];
    }

    else {
        return NULL;
    }
}

vertex* QueueTailNode(Queue* queue1){
    if (!QueueEmpty(queue1)){
        if (queue1->tail > 1){
            return queue1->arr[queue1->tail - 1];
        }

        else {
            return queue1->arr[queue1->size];
        }
    }

    else {
        return NULL;
    }
}

void EnqueueNode(Queue* queue1, vertex* newElement){
    if (!QueueFull(queue1)){
        queue1->arr[queue1->tail] = newElement;

        if (queue1->tail < queue1->size){
            queue1->tail++;
        }

        else {
            queue1->tail = 1;
        }
    } //first index is one

    else {
        printf("Overflow error!\n");
    }
}

vertex* DequeueNode(Queue* queue1){
    if (!QueueEmpty(queue1)){
        if (queue1->head < queue1->size){
            queue1->head++;
            return queue1->arr[queue1->head - 1];
        }

        else {
            queue1->head = 1;
            return queue1->arr[queue1->size];
        }
    }

    else {
        return NULL;
    }
}

int getQueueSizeNode(Queue* queue1){
    Queue temp;
    CreateQueue(&temp);
    int size = 0;

    while (!QueueEmpty(queue1)){
        Enqueue(&temp, Dequeue(queue1));
        size++;
    }

    while (!QueueEmpty(&temp)){
        Enqueue(queue1, Dequeue(&temp));
    }

    return size;
}

void clearQueueNode(Queue* queue1){
    while (!QueueEmpty(queue1)){
        Dequeue(queue1);
    }
}
