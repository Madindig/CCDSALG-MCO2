#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "graph.h"

//returns a pointer to the next vertex in the list
vertex* createVertex(vertex* node, String name){
    vertex* newEdge = (vertex*)malloc(sizeof(vertex)); //allocate memory for a new vertex
    strcpy(newEdge->name, name); //give it a name
    newEdge->edge = NULL; //set its edge to NULL
    newEdge->hasBeenVisited = false;
    node->edge = newEdge; //the newly created vertex forms an edge with the previous vertex

    //printf("New edge name: %s\n", node->edge->name);
    //printf("Previous edge name: %s \n", node->name);

    return node->edge;
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

//key is the name of the vertex
vertex* getVertex(graph* someGraph, String key){
    int i;
    bool isFound = false;
    vertex* returnVal;
    vertex* temp;

    for (i = 0; i < someGraph->numVertices && !isFound; i++){
        temp = &(someGraph->adjacencyList[i]);
        //printf("Degree of current vertex: %d\n", getDegree(temp));
        //printf("Comparing %s and %s. Result: %d\n", temp->name, key, caseInsensitiveStringCompare(someGraph->adjacencyList[i].name, key));
        if (strcasecmp(temp->name, key) == 0){
            isFound = true;
            returnVal = &(someGraph->adjacencyList[i]);
        }
    }

    if (isFound)
        return returnVal;

    else return NULL;
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
