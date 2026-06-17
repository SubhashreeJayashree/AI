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
    int size;   // keep track of the number of elements
} Queue;

// Initialize the queue
void initQueue(Queue *q) {
    q->front = q->rear = NULL;
    q->size = 0;
}

// Check if queue is empty
int isEmpty(Queue *q) {
    return q->size == 0;
}

// Return size
int Size(Queue *q) {
    return q->size;
}

// Enqueue operation
void enqueue(Queue *q, int x) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = x;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
}

// Dequeue operation
void dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("-1\n");  // Underflow case
        return;
    }
    Node* temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    q->size--;
}

// Front operation
void Front(Queue *q) {
    if (isEmpty(q)) {
        printf("-1\n");
    } else {
        printf("%d\n", q->front->data);
    }
}

int main() {
    Queue q;
    initQueue(&q);

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int op;
        scanf("%d", &op);

        if (op == 1) { // Enqueue
            int val;
            scanf("%d", &val);
            enqueue(&q, val);
        } else if (op == 2) { // Dequeue
            dequeue(&q);
        } else if (op == 3) { // Front
            Front(&q);
        } else if (op == 4) { // Size
            printf("%d\n", Size(&q));
        } else if (op == 5) { // isEmpty
            if (isEmpty(&q)) {
                printf("true\n");
            } else {
                printf("false\n");
            }
        }
    }

    return 0;
}
