#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure for a node in the adjacency list
struct Node {
    int data;
    struct Node* next;
};

// Structure for the adjacency list
struct Graph {
    int numVertices;
    struct Node** adjLists;
    bool* visited;
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with a given number of vertices
struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->adjLists = (struct Node**)malloc(vertices * sizeof(struct Node*));
    graph->visited = (bool*)malloc(vertices * sizeof(bool));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false;
    }

    return graph;
}

// Function to add an edge between two nodes
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

// Depth First Search (DFS) implementation
void DFS(struct Graph* graph, int vertex) {
    graph->visited[vertex] = true;
    printf("%d ", vertex);

    struct Node* adjList = graph->adjLists[vertex];
    while (adjList != NULL) {
        int connectedVertex = adjList->data;
        if (!graph->visited[connectedVertex]) {
            DFS(graph, connectedVertex);
        }
        adjList = adjList->next;
    }
}

// Breadth First Search (BFS) implementation
void BFS(struct Graph* graph, int startVertex) {
    struct Node* queue[graph->numVertices];
    int front = 0, rear = 0;

    graph->visited[startVertex] = true;
    printf("%d ", startVertex);
    queue[rear++] = graph->adjLists[startVertex];

    while (front < rear) {
        struct Node* currentVertex = queue[front++];
        while (currentVertex != NULL) {
            int adjacentVertex = currentVertex->data;
            if (!graph->visited[adjacentVertex]) {
                printf("%d ", adjacentVertex);
                graph->visited[adjacentVertex] = true;
                queue[rear++] = graph->adjLists[adjacentVertex];
            }
            currentVertex = currentVertex->next;
        }
    }
}

int main() {
    int vertices = 6;
    struct Graph* graph = createGraph(vertices);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 5);

    printf("Depth First Search (DFS) starting from vertex 0: ");
    DFS(graph, 0);
    printf("\n");

    // Reset visited flags
    for (int i = 0; i < vertices; i++) {
        graph->visited[i] = false;
    }

    printf("Breadth First Search (BFS) starting from vertex 0: ");
    BFS(graph, 0);
    printf("\n");

    return 0;
}

