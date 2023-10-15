#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

typedef struct Node Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Node* createLinkedList() {
    int n, data;
    Node* head = NULL;
    Node* current = NULL;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &data);
        Node* newNode = createNode(data);

        if (head == NULL) {
            head = newNode;
            current = head;
        } else {
            current->next = newNode;
            current = newNode;
        }
    }

    return head;
}

Node* insertNode(Node* head, int data, int position) {
    Node* newNode = createNode(data);

    if (position == 0) {
        newNode->next = head;
        return newNode;
    }

    Node* current = head;
    for (int i = 0; i < position - 1 && current != NULL; i++) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Invalid position for insertion.\n");
        free(newNode);
        return head;
    }

    newNode->next = current->next;
    current->next = newNode;

    return head;
}

Node* deleteNode(Node* head, int position) {
    if (head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return NULL;
    }

    if (position == 0) {
        Node* temp = head->next;
        free(head);
        return temp;
    }

    Node* current = head;
    Node* prev = NULL;

    for (int i = 0; i < position && current != NULL; i++) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Invalid position for deletion.\n");
        return head;
    }

    prev->next = current->next;
    free(current);

    return head;
}

Node* reverseLinkedList(Node* head) {
    Node* prev = NULL;
    Node* current = head;
    Node* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;
}

Node* concatenateLinkedLists(Node* list1, Node* list2) {
    if (list1 == NULL) {
        return list2;
    }

    Node* current = list1;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = list2;

    return list1;
}

void displayLinkedList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void freeLinkedList(Node* head) {
    Node* current = head;
    Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    Node* list1 = NULL;
    Node* list2 = NULL;
    int choice, data, position;

    while (1) {
        printf("\n--- Menu ---\n");
        printf("1. Create a Linked List\n");
        printf("2. Insert a Node\n");
        printf("3. Delete a Node\n");
        printf("4. Reverse Linked List\n");
        printf("5. Concatenate Linked Lists\n");
        printf("6. Display Linked List\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                list1 = createLinkedList();
                printf("Linked List created successfully.\n");
                break;
            case 2:
                if (list1 == NULL) {
                    printf("Create a Linked List first.\n");
                } else {
                    printf("Enter the data to insert: ");
                    scanf("%d", &data);
                    printf("Enter the position to insert: ");
                    scanf("%d", &position);
                    list1 = insertNode(list1, data, position);
                }
                break;
            case 3:
                if (list1 == NULL) {
                    printf("List is empty. Nothing to delete.\n");
                } else {
                    printf("Enter the position to delete: ");
                    scanf("%d", &position);
                    list1 = deleteNode(list1, position);
                }
                break;
            case 4:
                if (list1 == NULL) {
                    printf("List is empty. Nothing to reverse.\n");
                } else {
                    list1 = reverseLinkedList(list1);
                    printf("Linked List reversed successfully.\n");
                }
                break;
            case 5:
                list2 = createLinkedList();
                list1 = concatenateLinkedLists(list1, list2);
                printf("Linked Lists concatenated successfully.\n");
                break;
            case 6:
                if (list1 == NULL) {
                    printf("List is empty.\n");
                } else {
                    printf("Linked List: ");
                    displayLinkedList(list1);
                }
                break;
            case 7:
                freeLinkedList(list1);
                freeLinkedList(list2);
                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

