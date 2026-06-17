#include <stdio.h>
#include <stdbool.h>

#define MAX 100000

typedef struct {
    int arr[MAX];
    int front, rear, size;
} Queue;

// Initialize the queue
void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

// Check if queue is empty
bool isEmpty(Queue *q) {
    return q->size == 0;
}

// Return current size
int Size(Queue *q) {
    return q->size;
}

// Enqueue operation
void enqueue(Queue *q, int x) {
    if (q->size == MAX) {
        printf("Queue Overflow\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX;
    q->arr[q->rear] = x;
    q->size++;
}

// Dequeue operation
void dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue Underflow\n");
        return;
    }
    q->front = (q->front + 1) % MAX;
    q->size--;
}

// Front operation
void Front(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue Underflow\n");
    } else {
        printf("%d\n", q->arr[q->front]);
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
