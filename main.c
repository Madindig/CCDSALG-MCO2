#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "traversal.c"

int main(){
    FILE *fp = NULL;
    graph newGraph;
    int i;
    char filename[100];
    char start[100];
    printf("Filename: ");
    scanf("%s", filename);
    printf("Input start vertex for the traversal: ");
    scanf("%s", start);
    fp = fopen(filename, "r");
    if (!fileToGraph(fp, &newGraph))
        printf("%s not found.\n", filename);

<<<<<<< HEAD
    else if (getVertex(&newGraph, start) == NULL){
        printf("Vertex %s not found.\n", start);
    }

    else {
        fp = fopen("TRAVERSALS.txt", "w+");
        for (i = 0; i < newGraph.numVertices; i++){
            fprintf(fp, "%s %d\n", newGraph.adjacencyList[i].name, getDegree(&(newGraph.adjacencyList[i])));
=======
    fclose(fp);

    printf("\n");

    

    printf("\n");

    fp = fopen("TRAVERSALS.txt", "w+");
    for (i = 0; i < newGraph.numVertices; i++){
        fprintf(fp, "%s %d\n", newGraph.adjacencyList[i].name, getDegree(&(newGraph.adjacencyList[i])));
    }
    fprintf(fp, "\n");
    printBFS(fp, &newGraph, start);
    resetVisitStatus(&newGraph);
    fprintf(fp, "\n");
    fprintf(fp, "\n");
    printDFS(fp, &newGraph, start);
    fprintf(fp, "\n");
    fclose(fp);

    /*
    vertex* temp;

    for (i = 0; i < newGraph.numVertices; i++){
        temp = &(newGraph.adjacencyList[i]);
        printf("Vertex %d:\n", i + 1);
        while (temp != NULL){
            printf("%s ", temp->name);
            temp = temp->edge;
>>>>>>> 5b3e3e21647bd050628fb5c5e042635d7c0fe311
        }

        fprintf(fp, "\n");
        printBFS(fp, &newGraph, start);
        resetVisitStatus(&newGraph);
        fprintf(fp, "\n");
        fprintf(fp, "\n");
        printDFS(fp, &newGraph, start);
        fprintf(fp, "\n");
        fclose(fp);
    }

    return 0;
}
