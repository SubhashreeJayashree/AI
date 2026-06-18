#include <stdio.h>
#include <stdlib.h>

// Structure for a DLL node
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to append a node at the end of DLL
void appendNode(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Function to traverse DLL in forward direction with strict spacing
void traverseForward(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) {
            printf(" "); // Only prints space if there's a next node
        }
        temp = temp->next;
    }
    printf("\n");
}

// Function to traverse DLL in backward direction with strict spacing
void traverseBackward(struct Node* head) {
    if (head == NULL) {
        printf("\n");
        return;
    }
    
    struct Node* temp = head;
    // Move to the last node
    while (temp->next != NULL) {
        temp = temp->next;
    }
    
    // Traverse backward using the prev pointer
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->prev != NULL) {
            printf(" "); // Only prints space if there's a previous node
        }
        temp = temp->prev;
    }
    printf("\n");
}

int main() {
    int n, data;
    struct Node* head = NULL;

    // Read number of nodes
    if (scanf("%d", &n) != 1) return 0;

    // Read node data and build DLL
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &data) == 1) {
            appendNode(&head, data);
        }
    }

    // Traverse and print DLL in both directions
    traverseForward(head);
    traverseBackward(head);

    return 0;
}
