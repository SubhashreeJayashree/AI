#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the DLL
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to append a node at the end of the DLL
Node* appendNode(Node* head, int data) {
    Node* newNode = createNode(data);
    if (head == NULL) {
        return newNode; // First node becomes head
    }
    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
    return head;
}

// Function to traverse the DLL forward
void traverseForward(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) printf(" "); // space only between numbers
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int n, value;
    Node* head = NULL;

    // Read number of nodes
    scanf("%d", &n);

    // Insert nodes
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        head = appendNode(head, value);
    }

    // Traverse forward
    traverseForward(head);

    return 0;
}
