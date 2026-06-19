#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode(int val) {
    if (val == -1) return NULL;
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = val;
    node->left = node->right = NULL;
    return node;
}

// Queue structure to build tree from level order
typedef struct Queue {
    Node** arr;
    int front, rear, size;
} Queue;

Queue* createQueue(int size) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->arr = (Node**)malloc(sizeof(Node*) * size);
    q->front = q->rear = 0;
    q->size = size;
    return q;
}

void enqueue(Queue* q, Node* node) {
    q->arr[q->rear++] = node;
}

Node* dequeue(Queue* q) {
    return q->arr[q->front++];
}

int isEmpty(Queue* q) {
    return q->front == q->rear;
}

// Build binary tree from level order input
Node* buildTree(int* arr, int n) {
    if (n == 0) return NULL;
    Node* root = createNode(arr[0]);
    Queue* q = createQueue(n);
    enqueue(q, root);
    int i = 1;
    while (!isEmpty(q) && i < n) {
        Node* curr = dequeue(q);
        if (curr) {
            curr->left = createNode(arr[i++]);
            if (curr->left) enqueue(q, curr->left);
            if (i < n) {
                curr->right = createNode(arr[i++]);
                if (curr->right) enqueue(q, curr->right);
            }
        }
    }
    return root;
}

// Check if tree is a valid BST
int isBSTUtil(Node* root, int min, int max) {
    if (!root) return 1;
    if (root->data <= min || root->data >= max) return 0;
    return isBSTUtil(root->left, min, root->data) &&
           isBSTUtil(root->right, root->data, max);
}

int main() {
    int n;
    scanf("%d", &n);
    int* values = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &values[i]);
    }

    Node* root = buildTree(values, n);

    if (isBSTUtil(root, INT_MIN, INT_MAX))
        printf("Yes\n");
    else
        printf("No\n");

    free(values);
    return 0;
}
