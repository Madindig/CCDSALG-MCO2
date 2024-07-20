#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

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

//for debugging purposes
//traverses the linked list per vertex
int main(){
    FILE *fp = NULL;
    graph newGraph;

    fp = fopen("GRAPH.txt", "r");

    fileToGraph(fp, &newGraph);

    int i;

    for (i = 0; i < newGraph.numVertices; i++){
        vertex* temp = &(newGraph.adjacencyList[i]);
        printf("Vertex %d:\n", i + 1);
        while (temp->edge != NULL){
            printf("%s ", temp->name);
            temp = temp->edge;
        }

        printf("%s", temp->name);

        printf("\n");
    }

    fclose(fp);

    return 0;
}
