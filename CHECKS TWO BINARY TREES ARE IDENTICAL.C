#include <stdio.h>
#include <stdlib.h>

// Define binary tree node
typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

// Queue for level-order build
typedef struct Queue {
    Node **arr;
    int front, rear, size;
} Queue;

// Queue functions
Queue* createQueue(int size) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->arr = (Node**)malloc(sizeof(Node*) * size);
    q->front = q->rear = 0;
    q->size = size;
    return q;
}

int isEmpty(Queue* q) {
    return q->front == q->rear;
}

void enqueue(Queue* q, Node* node) {
    if (q->rear == q->size) return;
    q->arr[q->rear++] = node;
}

Node* dequeue(Queue* q) {
    if (isEmpty(q)) return NULL;
    return q->arr[q->front++];
}

// Create a new tree node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Build tree from level-order input
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

        // Right child
        if (i < n && arr[i] != -1) {
            current->right = createNode(arr[i]);
            enqueue(q, current->right);
        }
        i++;
    }
    return root;
}

// Check if two trees are identical
int areIdentical(Node* root1, Node* root2) {
    if (root1 == NULL && root2 == NULL) return 1;
    if (root1 == NULL || root2 == NULL) return 0;
    return (root1->data == root2->data) &&
           areIdentical(root1->left, root2->left) &&
           areIdentical(root1->right, root2->right);
}

int main() {
    int n1, n2;

    // First tree input
    scanf("%d", &n1);
    int arr1[n1];
    for (int i = 0; i < n1; i++) scanf("%d", &arr1[i]);

    // Second tree input
    scanf("%d", &n2);
    int arr2[n2];
    for (int i = 0; i < n2; i++) scanf("%d", &arr2[i]);

    Node* root1 = buildTree(arr1, n1);
    Node* root2 = buildTree(arr2, n2);

    if (areIdentical(root1, root2))
        printf("Yes\n");
    else
        printf("No\n");

    return 0;
}
