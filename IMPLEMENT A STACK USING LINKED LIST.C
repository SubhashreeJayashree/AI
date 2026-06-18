#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define Node type using typedef
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Top pointer for stack
Node* top = NULL;

// Check if stack is empty
int isEmpty() {
    return top == NULL;
}

// Push operation
void push(int x) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = x;
    newNode->next = top;
    top = newNode;
}

// Pop operation
void pop() {
    if (isEmpty()) {
        printf("Stack Underflow\n");
        return;
    }
    Node* temp = top;
    top = top->next;
    free(temp);
}

// Peek operation
void peek() {
    if (isEmpty()) {
        printf("Stack Underflow\n");
        return;
    }
    printf("%d\n", top->data);
}

int main() {
    int n;
    scanf("%d", &n);

    char operation[10];
    int value;

    for (int i = 0; i < n; i++) {
        scanf("%s", operation);
        if (strcmp(operation, "PUSH") == 0) {
            scanf("%d", &value);
            push(value);
        } else if (strcmp(operation, "POP") == 0) {
            pop();
        } else if (strcmp(operation, "PEEK") == 0) {
            peek();
        }
    }

    // Optional: free remaining nodes to avoid memory leaks
    while (!isEmpty()) {
        pop();
    }

    return 0;
}
