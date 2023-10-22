#include <stdio.h>
#include <stdlib.h>

// Define a structure to represent a node in the adjacency list
struct Node {
    int data;
    struct Node* next;
};

// Define a structure to represent the adjacency list
struct Graph {
    int numVertices;
    struct Node** adjLists;
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

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }

    return graph;
}

// Function to add an edge between two nodes
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Function to delete a node from the graph
void deleteNode(struct Graph* graph, int node) {
    for (int i = 0; i < graph->numVertices; i++) {
        struct Node* current = graph->adjLists[i];
        struct Node* prev = NULL;

        while (current != NULL) {
            if (current->data == node) {
                if (prev != NULL) {
                    prev->next = current->next;
                    free(current);
                    current = prev->next;
                } else {
                    struct Node* temp = current;
                    current = current->next;
                    graph->adjLists[i] = current;
                    free(temp);
                }
            } else {
                prev = current;
                current = current->next;
            }
        }
    }
}

// Function to print the adjacency list representation of the graph
void printGraph(struct Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        struct Node* current = graph->adjLists[i];
        printf("Adjacency list of vertex %d: ", i);
        while (current != NULL) {
            printf("%d -> ", current->data);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int vertices = 5;
    struct Graph* graph = createGraph(vertices);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 3);

    printf("Graph after adding edges:\n");
    printGraph(graph);

    deleteNode(graph, 2);

    printf("Graph after deleting node 2:\n");
    printGraph(graph);

    return 0;
}

