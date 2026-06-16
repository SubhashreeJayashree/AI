#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int data;
    struct Node* next;
} Node;


Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

Node* insertAtBeginning(Node* head, int value) {
    Node* newNode = createNode(value);
    newNode->next = head;
    return newNode;
}


void displayList(Node* head) {
    if (head == NULL) {
        printf("NULL\n");
        return;
    }
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}


int main() {
    int N, value;
    Node* head = NULL;


    scanf("%d", &N);


    for (int i = 0; i < N; i++) {
        scanf("%d", &value);
        head = insertAtBeginning(head, value);
    }


    displayList(head);

    return 0;
}
