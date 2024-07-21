#include "stack.c"

void markAsVisited(graph* someGraph, String key){
    int i;
    vertex* temp;

    for (i = 0; i < someGraph->numVertices; i++){
        temp = &(someGraph->adjacencyList[i]);

        while (temp != NULL){
            if (strcmp(temp->name, key) == 0)
                temp->hasBeenVisited = true;

            temp = temp->edge;
        }
    }
}

//returns smallest adjacent vertex from the graph
vertex* getSmallestAdjacent(graph* someGraph, String key){
    //printf("Checking for node %s\n", key);
    vertex* currentVertex = getVertex(someGraph, key)->edge;
    String lowestName = "";
    bool doneAssigningName = false;

    while (currentVertex != NULL){
        if (!currentVertex->hasBeenVisited && !doneAssigningName){
            strcpy(lowestName, currentVertex->name);
            doneAssigningName = true;
        }

        else if (!currentVertex->hasBeenVisited && strcmp(currentVertex->name, lowestName) <= 0)
            strcpy(lowestName, currentVertex->name);

        currentVertex = currentVertex->edge;
       //printf("Lowest Name: %s\n", lowestName);
    }

    return getVertex(someGraph, lowestName); //uses temp to get pointer to linked list where the adjacent vertex is the head
}

bool printDFS(graph* someGraph, String key){
    vertex* currentNode = getVertex(someGraph, key);
    int numVisited = 0;
    StackNode stack;

    CreateStackNode(&stack);

    if (currentNode == NULL)
        return false;

    //printf("Num of Vertices: %d\n", someGraph->numVertices);

    while (numVisited < someGraph->numVertices){
        if (!currentNode->hasBeenVisited){
            markAsVisited(someGraph, currentNode->name);
            numVisited++;
            PushNode(&stack, currentNode);
            printf("%s ", currentNode->name);
        }

        if (getSmallestAdjacent(someGraph, currentNode->name) != NULL){
            currentNode = getSmallestAdjacent(someGraph, currentNode->name);
        } //There is an adjacent vertex yet to be visited

        else {
            PopNode(&stack);
            currentNode = TopNode(&stack);
        }
    }

    return true;
}

/*
int main(){
    FILE *fp = NULL;
    graph newGraph;

    fp = fopen("GRAPH.txt", "r");

    if (!fileToGraph(fp, &newGraph))
        printf("The file does not exist.\n");

    fclose(fp);

    printf("Name of node: %s\n", getSmallestAdjacent(&newGraph, "Clark")->name);
    markAsVisited(&newGraph, "Diana");
    printf("Name of node: %s\n", getSmallestAdjacent(&newGraph, "Clark")->name);
}*/

