#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "traversal.c"
//for debugging purposes
//traverses the linked list per vertex
int main(){
    FILE *fp = NULL;
    graph newGraph;

    fp = fopen("GRAPH.txt", "r");

    if (!fileToGraph(fp, &newGraph))
        printf("The file does not exist.\n");

    fclose(fp);

    printf("DFS traversal: ");
    printDFS(&newGraph, "Clark");
    printf("\n");

    int i;
    vertex* temp;

    /*
    for (i = 0; i < newGraph.numVertices; i++){
        temp = &(newGraph.adjacencyList[i]);
        printf("Vertex %d:\n", i + 1);
        while (temp != NULL){
            printf("%s ", temp->name);
            temp = temp->edge;
        }

        printf("\n");
        printf("Degree of vertex %d: %d\n", i + 1, getDegree(&(newGraph.adjacencyList[i])));
    }*/

    return 0;
}
