#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "graph.h"
//#include <windows.h>

//returns a pointer to the next vertex in the list
vertex* createVertex(vertex* node, String name){
    vertex* newEdge = (vertex*)malloc(sizeof(vertex)); //allocate memory for a new vertex
    strcpy(newEdge->name, name); //give it a name
    newEdge->idNum = 0;
    newEdge->edge = NULL; //set its edge to NULL
    newEdge->hasBeenVisited = false;
    node->edge = newEdge; //the newly created vertex forms an edge with the previous vertex

    //printf("New edge name: %s\n", node->edge->name);
    //printf("Previous edge name: %s \n", node->name);

    return node->edge;
}

bool caseInsensitiveStringCompare(String one, String two){
    int i;
    int len1 = (int)strlen(one);
    int len2 = (int)strlen(two);
    String copyOfOne = "";
    String copyOfTwo = "";

    for (i = 0; i < len1; i++){
        copyOfOne[i] = toupper(one[i]);
    }

    for (i = 0; i < len2; i++){
        copyOfTwo[i] = toupper(two[i]);
    }

    return (bool)(strcmp(copyOfOne, copyOfTwo) == 0);
}

//key is the name of the vertex
//returns the first vertex with a similar name
vertex* getVertex(graph* someGraph, String key){
    int i;
    bool isFound = false;
    vertex* returnVal;
    vertex* temp;

    for (i = 0; i < someGraph->numVertices && !isFound; i++){
        temp = &(someGraph->adjacencyList[i]);
        //printf("Degree of current vertex: %d\n", getDegree(temp));
        //printf("Comparing %s and %s. Result: %d\n", temp->name, key, caseInsensitiveStringCompare(someGraph->adjacencyList[i].name, key));
        if (caseInsensitiveStringCompare(temp->name, key)){
            isFound = true;
            returnVal = &(someGraph->adjacencyList[i]);
        }
    }

    if (isFound)
        return returnVal;

    else return NULL;
}

//adds an id to every vertex
//if two vertices have the same name, the vertex with the lower ID number is visited first
void addIDNum(graph* newGraph){
    int i;
    vertex* currentNode;
    vertex* temp;
    bool doneAssigning = false;
    String nameOfCurrent; //the key used to assign all vertices with the same name with the same idNum
    String nameOfThisAdjacentNode;
    vertex* hasFailedToAssign;
    vertex* basePtr = &(newGraph->adjacencyList[0]);
    int index;

    for (i = 0; i < newGraph->numVertices; i++){ //go through each linked list
        currentNode = &(newGraph->adjacencyList[i]);
        strcpy(nameOfCurrent, currentNode->name);
        currentNode->idNum = i + 1;
        currentNode = currentNode->edge;
        //printf("Val. of i: %d\n", i);

        while (currentNode != NULL){ //go through all adjacent vertices
            doneAssigning = false;
            hasFailedToAssign = getVertex(newGraph, currentNode->name); //get address of the head of the linked list in case it fails to assign
            if (hasFailedToAssign == &(newGraph->adjacencyList[i])){ //getVertex actually returned not an adjacent vertex, but itself; happens when vertices with same name are adjacent to each other
                //printf("Condition is true\n");
                hasFailedToAssign++; //start checking from the next linked list head
                //printf("Checking next head\n");
                index = (hasFailedToAssign - basePtr) / sizeof(vertex); //to avoid index out of bounds
                //printf("Initializing index\n");
                while (index < newGraph->numVertices && strcmp(nameOfCurrent, hasFailedToAssign->name) != 0){
                    hasFailedToAssign++;
                    index = (hasFailedToAssign - basePtr) / sizeof(vertex);
                } //after this loop, hasFailedToAssign should actually be on the correct adjacent vertex
                //printf("Done looping");
            }

            strcpy(nameOfThisAdjacentNode, hasFailedToAssign->name); //just in case it fails to assign, the name of the head of the linked list will be used

            temp = hasFailedToAssign->edge; //get the actual adjacent vertex from adjacency list and then check its first edge

            //printf("Current adjacent node: %s\n", currentNode->name);

            while (temp != NULL && !doneAssigning){ //go through all the adjacent vertices of each vertex adjacent to the current vertex from the outermost loop
                if (strcmp(nameOfCurrent, temp->name) == 0 && temp->idNum == 0){
                    temp->idNum = i + 1;
                    doneAssigning = true;
                }

                else temp = temp->edge;

                if (temp == NULL && !doneAssigning){ //happens when there are similar vertices (i.e. similar name); you can not find the current vertex's name because it is not adjacent to this similar vertex
                    hasFailedToAssign++; //start checking from the next linked list head
                    index = (hasFailedToAssign - basePtr) / sizeof(vertex); //to avoid index out of bounds
                    while (index < newGraph->numVertices && (strcmp(nameOfThisAdjacentNode, hasFailedToAssign->name) != 0 || hasFailedToAssign == &(newGraph->adjacencyList[i]))){
                        hasFailedToAssign++;
                        index = (hasFailedToAssign - basePtr) / sizeof(vertex);
                    }

                    temp = hasFailedToAssign->edge; //assigns the next similar vertex to the currentNode so you can search for the nameOfCurrent again
                }
            }

            currentNode = currentNode->edge;
        }
    }
}

bool fileToGraph(FILE* fp, graph* newGraph){
    if (fp == NULL)
        return false;

    fscanf(fp, "%d", &newGraph->numVertices);
    int i;
    String nextStr = "";
    bool isNewLine;
    vertex* temp;

    for (i = 0; i < newGraph->numVertices; i++){
        isNewLine = true;
        strcpy(nextStr, "");
        while (strcmp(nextStr, "-1") != 0){
            fscanf(fp, "%s", nextStr);

            //printf("Next string: %s\n", nextStr);
            //Sleep(1000);

            if (strcmp(nextStr, "-1") != 0){
                if (isNewLine){
                    strcpy(newGraph->adjacencyList[i].name, nextStr);
                    newGraph->adjacencyList[i].hasBeenVisited = false;
                    newGraph->adjacencyList[i].edge = NULL;
                    temp = &(newGraph->adjacencyList[i]);
                    isNewLine = false;
                }

                else {
                    temp = createVertex(temp, nextStr);
                }
            }
        }
    }

    addIDNum(newGraph);

    fclose(fp);

    return true;
}

int getDegree(vertex* node){
    vertex* temp = node;
    int deg = 0;
    while (temp->edge != NULL){
        temp = temp->edge;
        deg++;
    }

    return deg;
}

void resetVisitStatus(graph* someGraph){
    int i;
    vertex* temp;
    for (i = 0; i < someGraph->numVertices; i++){
        temp = &(someGraph->adjacencyList[i]);
        while (temp != NULL){
            temp->hasBeenVisited = false;
            temp = temp->edge;
        }
    }
}

/*
int main(){
    FILE *fp = NULL;
    graph newGraph;

    fp = fopen("GRAPH.txt", "r");

    if (!fileToGraph(fp, &newGraph))
        printf("The file does not exist.\n");

    fclose(fp);

    printf("Name of node: %s", getVertex(&newGraph, "DiaNa")->name);
}*/
