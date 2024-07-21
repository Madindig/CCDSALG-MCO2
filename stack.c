#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.c"

typedef struct StackNode{
    vertex* arr[256];
    int top;
    int size;
} StackNode;

void CreateStackNode(StackNode* stack1){
    stack1->size = 513;
    stack1->top = 0;
}

bool StackEmptyNode(StackNode* stack1){
    return (bool)(stack1->top == 0);
}

bool StackFullNode(StackNode* stack1){
    return (bool)(stack1->top == stack1->size);
}

void PushNode(StackNode* stack1, vertex* newElement){
    if (!StackFullNode(stack1)){
        stack1->top++;
        stack1->arr[stack1->top] = newElement;
    } //first index is one

    else {
        printf("Overflow error!\n");
    }
}

vertex* PopNode(StackNode* stack1){
    if (!StackEmptyNode(stack1)){
        stack1->top--;
        return stack1->arr[stack1->top + 1];
    }

    else {
        return NULL;
    }
}

vertex* TopNode(StackNode* stack1){
    if (!StackEmptyNode(stack1)){
        return stack1->arr[stack1->top];
    }

    else {
        return NULL;
    }
}

