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

Node* createCircularLinkedList() {
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

    if (head) {
        current->next = head; // Make the list circular
    }

    return head;
}

Node* insertNode(Node* head, int data, int position) {
    Node* newNode = createNode(data);

    if (head == NULL) {
        newNode->next = newNode;
        return newNode;
    }

    if (position == 0) {
        newNode->next = head->next;
        head->next = newNode;
        return head;
    }

    Node* current = head;
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;

    return head;
}

Node* deleteNode(Node* head, int data) {
    if (head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return NULL;
    }

    if (head->data == data) {
        Node* temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    Node* current = head;
    while (current->next != head && current->next->data != data) {
        current = current->next;
    }

    if (current->next == head) {
        printf("Data not found in the list.\n");
    } else {
        Node* temp = current->next;
        current->next = current->next->next;
        free(temp);
    }

    return head;
}

Node* reverseCircularLinkedList(Node* head) {
    if (head == NULL || head->next == head) {
        return head;
    }

    Node* prev = NULL;
    Node* current = head;
    Node* next;

    do {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    } while (current != head);

    head->next = prev;
    head = prev;

    return head;
}

Node* concatenateCircularLinkedLists(Node* list1, Node* list2) {
    if (list1 == NULL) {
        return list2;
    }

    if (list2 == NULL) {
        return list1;
    }

    Node* list1End = list1->next;
    Node* list2End = list2->next;

    list1End->next = list2;
    list2End->next = list1;

    return list1;
}

void displayCircularLinkedList(Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node* current = head;

    do {
        printf("%d -> ", current->data);
        current = current->next;
    } while (current != head);

    printf(" (Back to head)\n");
}

void freeCircularLinkedList(Node* head) {
    if (head == NULL) {
        return;
    }

    Node* current = head;
    Node* temp;

    do {
        temp = current;
        current = current->next;
        free(temp);
    } while (current != head);
}

int main() {
    Node* list1 = NULL;
    Node* list2 = NULL;
    int choice, data, position;

    while (1) {
        printf("\n--- Menu ---\n");
        printf("1. Create a Circular Linked List\n");
        printf("2. Insert a Node\n");
        printf("3. Delete a Node\n");
        printf("4. Reverse Circular Linked List\n");
        printf("5. Concatenate Circular Linked Lists\n");
        printf("6. Display Circular Linked List\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                list1 = createCircularLinkedList();
                printf("Circular Linked List created successfully.\n");
                break;
            case 2:
                if (list1 == NULL) {
                    printf("Create a Circular Linked List first.\n");
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
                    printf("Enter the data to delete: ");
                    scanf("%d", &data);
                    list1 = deleteNode(list1, data);
                }
                break;
            case 4:
                if (list1 == NULL) {
                    printf("List is empty. Nothing to reverse.\n");
                } else {
                    list1 = reverseCircularLinkedList(list1);
                    printf("Circular Linked List reversed successfully.\n");
                }
                break;
            case 5:
                list2 = createCircularLinkedList();
                list1 = concatenateCircularLinkedLists(list1, list2);
                printf("Circular Linked Lists concatenated successfully.\n");
                break;
            case 6:
                displayCircularLinkedList(list1);
                break;
            case 7:
                freeCircularLinkedList(list1);
                freeCircularLinkedList(list2);
                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

