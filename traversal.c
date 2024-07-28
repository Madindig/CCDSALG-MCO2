#include "queue.c"

//key is the name of the vertex
//returns the first vertex with a similar name
vertex* getVertexIDSensitive(graph* someGraph, String key, int idNum){
    int i;
    bool isFound = false;
    vertex* returnVal;
    vertex* temp;

    for (i = 0; i < someGraph->numVertices && !isFound; i++){
        temp = &(someGraph->adjacencyList[i]);
        //printf("Degree of current vertex: %d\n", getDegree(temp));
        //printf("Comparing %s and %s. Result: %d\n", temp->name, key, caseInsensitiveStringCompare(someGraph->adjacencyList[i].name, key));
        if (caseInsensitiveStringCompare(temp->name, key) == 0 && temp->idNum == idNum){
            isFound = true;
            returnVal = &(someGraph->adjacencyList[i]);
        }
    }

    if (isFound)
        return returnVal;

    else return NULL;
}

void markAsVisited(graph* someGraph, String key, int idNum){
    int i;
    vertex* temp;

    for (i = 0; i < someGraph->numVertices; i++){
        temp = &(someGraph->adjacencyList[i]);

        while (temp != NULL){
            if (strcmp(temp->name, key) == 0 && temp->idNum == idNum)
                temp->hasBeenVisited = true;

            temp = temp->edge;
        }
    }
}

//returns smallest adjacent vertex from the graph
vertex* getSmallestAdjacent(graph* someGraph, String key, int idNum){
    //printf("Checking for node %s\n", key);
    vertex* currentVertex = getVertexIDSensitive(someGraph, key, idNum)->edge;
    String lowestName = "";
    int lowestID;
    bool doneAssigningNameAndLowestID = false;

    while (currentVertex != NULL){
        if (!currentVertex->hasBeenVisited && !doneAssigningNameAndLowestID){
            strcpy(lowestName, currentVertex->name);
            lowestID = currentVertex->idNum;
            doneAssigningNameAndLowestID = true;
        }

        else if (!currentVertex->hasBeenVisited && strcmp(currentVertex->name, lowestName) <= 0 && currentVertex->idNum < lowestID){
            strcpy(lowestName, currentVertex->name);
            lowestID = currentVertex->idNum;
        }

        currentVertex = currentVertex->edge;
       //printf("Lowest Name: %s\n", lowestName);
    }

    return getVertexIDSensitive(someGraph, lowestName, lowestID); //uses temp to get pointer to linked list where the adjacent vertex is the head
}

bool printDFS(FILE* fp, graph* someGraph, String key){
    vertex* currentNode = getVertex(someGraph, key);
    int numVisited = 0;
    StackNode stack;

    CreateStackNode(&stack);

    if (currentNode == NULL)
        return false;

    //printf("Num of Vertices: %d\n", someGraph->numVertices);

    while (numVisited < someGraph->numVertices){
        if (!currentNode->hasBeenVisited){
            markAsVisited(someGraph, currentNode->name, currentNode->idNum);
            numVisited++;
            PushNode(&stack, currentNode);
            fprintf(fp, "%s ", currentNode->name);
        }

        if (getSmallestAdjacent(someGraph, currentNode->name, currentNode->idNum) != NULL){
            currentNode = getSmallestAdjacent(someGraph, currentNode->name, currentNode->idNum);
        } //There is an adjacent vertex yet to be visited

        else {
            PopNode(&stack);
            currentNode = TopNode(&stack);
        }
    }

    return true;
}

bool printBFS(FILE* fp, graph* someGraph, String key){
    vertex* currentNode = getVertex(someGraph, key);
    int numVisited = 0;
    QueueNode queue;

    CreateQueueNode(&queue);

    if (currentNode == NULL)
        return false;

    EnqueueNode(&queue, currentNode);
    markAsVisited(someGraph, QueueTailNode(&queue)->name, QueueTailNode(&queue)->idNum);
    while (numVisited < someGraph->numVertices){
        currentNode = DequeueNode(&queue);
        numVisited++;
        fprintf(fp, "%s ", currentNode->name);

        while (getSmallestAdjacent(someGraph, currentNode->name, currentNode->idNum) != NULL){
            EnqueueNode(&queue, getSmallestAdjacent(someGraph, currentNode->name, currentNode->idNum));
            //printf("Name of Enqueued: %s\n", getSmallestAdjacent(someGraph, currentNode->name)->name);
            //printf("Name of tail: %s\n", QueueTailNode(someGraph)->name);
            markAsVisited(someGraph, QueueTailNode(&queue)->name, QueueTailNode(&queue)->idNum);
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

    printBFS(&newGraph, "Clark");
}*/

