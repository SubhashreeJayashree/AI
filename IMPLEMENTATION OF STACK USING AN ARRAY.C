#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 5  // Change this for larger stack

// Stack structure
typedef struct {
    int arr[MAX_SIZE];
    int top;
} Stack;

// Function to initialize stack
void initStack(Stack *s) {
    s->top = -1;
}

// Check if stack is empty
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Check if stack is full
int isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

// Push operation
void push(Stack *s, int x) {
    if (isFull(s)) {
        printf("Stack Overflow\n");
    } else {
        s->arr[++s->top] = x;
    }
}

// Pop operation
void pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow\n");
    } else {
        s->top--;
    }
}

// Peek operation
void peek(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow\n");
    } else {
        printf("%d\n", s->arr[s->top]);
    }
}

int main() {
    Stack s;
    initStack(&s);

    int n;
    scanf("%d", &n);
    char operation[10];
    int value;

    for (int i = 0; i < n; i++) {
        scanf("%s", operation);

        if (strcmp(operation, "PUSH") == 0) {
            scanf("%d", &value);
            push(&s, value);
        } else if (strcmp(operation, "POP") == 0) {
            pop(&s);
        } else if (strcmp(operation, "PEEK") == 0) {
            peek(&s);
        }
    }

    return 0;
}
