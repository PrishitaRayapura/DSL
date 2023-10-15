#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

typedef struct Node Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

Node* createDoublyLinkedList() {
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
            newNode->prev = current;
            current = newNode;
        }
    }

    return head;
}

Node* insertNode(Node* head, int data, int position) {
    Node* newNode = createNode(data);

    if (position == 0) {
        newNode->next = head;
        head->prev = newNode;
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
    newNode->prev = current;
    if (current->next != NULL) {
        current->next->prev = newNode;
    }
    current->next = newNode;

    return head;
}

Node* deleteNode(Node* head, int position) {
    if (head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return NULL;
    }

    if (position == 0) {
        Node* temp = head;
        head = head->next;
        if (head != NULL) {
            head->prev = NULL;
        }
        free(temp);
        return head;
    }

    Node* current = head;
    for (int i = 0; i < position && current != NULL; i++) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Invalid position for deletion.\n");
        return head;
    }

    if (current->prev != NULL) {
        current->prev->next = current->next;
    }
    if (current->next != NULL) {
        current->next->prev = current->prev;
    }
    free(current);

    return head;
}

Node* reverseDoublyLinkedList(Node* head) {
    Node* current = head;
    Node* temp = NULL;

    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        if (current->prev == NULL) {
            head = current;
        }
        current = current->prev;
    }

    return head;
}

Node* concatenateDoublyLinkedLists(Node* list1, Node* list2) {
    if (list1 == NULL) {
        return list2;
    }

    if (list2 == NULL) {
        return list1;
    }

    Node* list1End = list1;
    while (list1End->next != NULL) {
        list1End = list1End->next;
    }

    list1End->next = list2;
    list2->prev = list1End;

    return list1;
}

void displayDoublyLinkedList(Node* head) {
    Node* current = head;
    printf("NULL <-> ");
    while (current != NULL) {
        printf("%d <-> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void freeDoublyLinkedList(Node* head) {
    Node* current = head;
    Node* temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    Node* list1 = NULL;
    Node* list2 = NULL;
    int choice, data, position;

    while (1) {
        printf("\n--- Menu ---\n");
        printf("1. Create a Doubly Linked List\n");
        printf("2. Insert a Node\n");
        printf("3. Delete a Node\n");
        printf("4. Reverse Doubly Linked List\n");
        printf("5. Concatenate Doubly Linked Lists\n");
        printf("6. Display Doubly Linked List\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                list1 = createDoublyLinkedList();
                printf("Doubly Linked List created successfully.\n");
                break;
            case 2:
                if (list1 == NULL) {
                    printf("Create a Doubly Linked List first.\n");
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
                    list1 = reverseDoublyLinkedList(list1);
                    printf("Doubly Linked List reversed successfully.\n");
                }
                break;
            case 5:
                list2 = createDoublyLinkedList();
                list1 = concatenateDoublyLinkedLists(list1, list2);
                printf("Doubly Linked Lists concatenated successfully.\n");
                break;
            case 6:
                displayDoublyLinkedList(list1);
                break;
            case 7:
                freeDoublyLinkedList(list1);
                freeDoublyLinkedList(list2);
                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

