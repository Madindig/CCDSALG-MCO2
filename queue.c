#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.c"

typedef struct Queue{
    vertex* arr[513];
    int head;
    int tail;
    int size;
} QueueNode;

void CreateQueueNode(QueueNode* queue1){
    queue1->size = 512;
    queue1->head = queue1->tail = 1;
}

bool QueueEmptyNode(QueueNode* queue1){
    return (bool)(queue1->head == queue1->tail);
}

bool QueueFullNode(QueueNode* queue1){
    return (bool)(queue1->head == (queue1->tail + 1) % queue1->size);
}

vertex* QueueHeadNode(QueueNode* queue1){
    if (!QueueEmptyNode(queue1)){
        return queue1->arr[queue1->head];
    }

    else {
        return NULL;
    }
}

vertex* QueueTailNode(QueueNode* queue1){
    if (!QueueEmptyNode(queue1)){
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

void EnqueueNode(QueueNode* queue1, vertex* newElement){
    if (!QueueFullNode(queue1)){
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

vertex* DequeueNode(QueueNode* queue1){
    if (!QueueEmptyNode(queue1)){
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

int getQueueSizeNode(QueueNode* queue1){
    QueueNode temp;
    CreateQueueNode(&temp);
    int size = 0;

    while (!QueueEmptyNode(queue1)){
        EnqueueNode(&temp, DequeueNode(queue1));
        size++;
    }

    while (!QueueEmptyNode(&temp)){
        EnqueueNode(queue1, DequeueNode(&temp));
    }

    return size;
}

void clearQueueNode(QueueNode* queue1){
    while (!QueueEmptyNode(queue1)){
        DequeueNode(queue1);
    }
}
