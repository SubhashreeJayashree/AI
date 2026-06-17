#include <stdio.h>
#include <stdlib.h>

// Node structure for the linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Queue structure using linked list
typedef struct {
    Node *front, *rear;
    int size;
} Queue;

// Function to initialize the queue
void initQueue(Queue* q) {
    q->front = q->rear = NULL;
    q->size = 0;
}

// Function to check if the queue is empty
int isEmpty(Queue* q) {
    return (q->size == 0);
}

// Function to get the size of the queue
int size(Queue* q) {
    return q->size;
}

// Function to enqueue (insert) an element
void enqueue(Queue* q, int value) {
    Node* temp = (Node*)malloc(sizeof(Node));
    if (!temp) return; // Memory allocation failed
    temp->data = value;
    temp->next = NULL;
    if (q->rear == NULL) { // If queue is empty
        q->front = q->rear = temp;
    } else {
        q->rear->next = temp;
        q->rear = temp;
    }
    q->size++;
}

// Function to dequeue (remove) an element
void dequeue(Queue* q) {
    if (isEmpty(q)) return; // Queue is empty
    Node* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL; // Queue becomes empty
    free(temp);
    q->size--;
}

// Function to get the front element of the queue
int front(Queue* q) {
    if (isEmpty(q)) return -1; // Queue is empty
    return q->front->data;
}

// Driver function to handle input and execute operations
int main() {
    Queue q;
    initQueue(&q);

    int N, operation, value;
    scanf("%d", &N); // Read number of operations

    while (N--) {
        scanf("%d", &operation);
        if (operation == 1) { // Enqueue
            scanf("%d", &value);
            enqueue(&q, value);
        } else if (operation == 2) { // Dequeue
            dequeue(&q);
        } else if (operation == 3) { // Front
            printf("%d\n", front(&q));
        } else if (operation == 4) { // Size
            printf("%d\n", size(&q));
        } else if (operation == 5) { // IsEmpty
            printf("%d\n", isEmpty(&q));
        }
    }
    return 0;
}
