#include <stdio.h>
#include <stdlib.h>

// Define binary tree node
typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

// Queue for level-order build
typedef struct Queue {
    Node** arr;
    int front, rear, capacity;
} Queue;

// Queue functions
Queue* createQueue(int capacity) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->arr = (Node**)malloc(sizeof(Node*) * capacity);
    q->front = q->rear = 0;
    q->capacity = capacity;
    return q;
}

int isEmpty(Queue* q) {
    return q->front == q->rear;
}

void enqueue(Queue* q, Node* node) {
    if (q->rear == q->capacity) return;
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

// Mirror the tree
void mirrorTree(Node* root) {
    if (root == NULL) return;
    Node* temp = root->left;
    root->left = root->right;
    root->right = temp;
    mirrorTree(root->left);
    mirrorTree(root->right);
}

// Inorder traversal
void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    Node* root = buildTree(arr, n);
    mirrorTree(root);
    inorder(root);
    printf("\n");

    return 0;
}
