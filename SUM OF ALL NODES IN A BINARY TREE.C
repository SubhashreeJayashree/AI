#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node
typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

// Queue structure for building tree
typedef struct Queue {
    Node** arr;
    int front, rear, size;
} Queue;

// Initialize queue
Queue* createQueue(int n) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->arr = (Node**)malloc(sizeof(Node*) * n);
    q->front = 0;
    q->rear = -1;
    q->size = 0;
    return q;
}

// Enqueue
void enqueue(Queue* q, Node* node) {
    q->arr[++q->rear] = node;
    q->size++;
}

// Dequeue
Node* dequeue(Queue* q) {
    if (q->size == 0) return NULL;
    Node* temp = q->arr[q->front++];
    q->size--;
    return temp;
}

// Create new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Build tree from level order input
Node* buildTree(int arr[], int n) {
    if (n == 0 || arr[0] == -1) return NULL;

    Node* root = createNode(arr[0]);
    Queue* q = createQueue(n);
    enqueue(q, root);

    int i = 1;
    while (i < n) {
        Node* current = dequeue(q);

        // Left child
        if (arr[i] != -1) {
            current->left = createNode(arr[i]);
            enqueue(q, current->left);
        }
        i++;

        if (i >= n) break;

        // Right child
        if (arr[i] != -1) {
            current->right = createNode(arr[i]);
            enqueue(q, current->right);
        }
        i++;
    }
    return root;
}

// Compute sum of all nodes
int sumNodes(Node* root) {
    if (root == NULL) return 0;
    return root->data + sumNodes(root->left) + sumNodes(root->right);
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    Node* root = buildTree(arr, n);
    printf("%d\n", sumNodes(root));

    return 0;
}
