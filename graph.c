#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

typedef char String[256];

typedef struct vertex{
    String name;
    struct vertex* edge;
    bool hasBeenVisited;
} vertex;

typedef struct graphTag{
    int numVertices;
    vertex adjacencyList[256];
} graph;

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
                    temp = createVertex(&(newGraph->adjacencyList[i]), nextStr);
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

bool caseInsensitiveStringCompare(String one, String two){
    if (strlen(one) != strlen(two))
        return false;
    int i;
    bool isMatching = true;
    int len = strlen(one); //it is assumed at this point that the two strings have the same name

    for (i = 0; i < len && isMatching; i++){
        if (toupper(one[i]) != toupper(two[i])){
            isMatching = false;
        }
    }

    return isMatching;
}

int getDegree(vertex* node){
    vertex* temp = node->edge;
    int deg = 0;
    while (temp->edge != NULL){
        temp = temp->edge;
        deg++;
    }

    return deg;
}

//key is the name of the vertex
vertex* getVertex(graph someGraph, String key){
    int i;
    bool isFound = false;
    vertex* returnVal;

    for (i = 0; i < someGraph.numVertices && !isFound; i++){
        if (strcpy(someGraph.adjacencyList[i].name, key) == 0){
            isFound = true;
            returnVal = &(someGraph.adjacencyList[i]);
        }

    }

    if (isFound)
        return returnVal;

    else return NULL;
}

//for debugging purposes
//traverses the linked list per vertex
int main(){
    FILE *fp = NULL;
    graph newGraph;

    fp = fopen("GRAPH.txt", "r");

    if (!fileToGraph(fp, &newGraph))
        printf("The file does not exist.\n");

    fclose(fp);

    int i;

    for (i = 0; i < newGraph.numVertices; i++){
        vertex* temp = &(newGraph.adjacencyList[i]);
        printf("Vertex %d:", i + 1);
        while (temp->edge != NULL){
            printf("%s ", temp->name);
            temp = temp->edge;
        }

        printf("%s\n", temp->name);

        printf("Degree of vertex %d: %d\n", i + 1, getDegree(&(newGraph.adjacencyList[i])));

        printf("\n");
    }



    return 0;
}
