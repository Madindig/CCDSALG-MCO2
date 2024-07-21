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
