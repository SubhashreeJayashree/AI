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

// Collect nodes at level K
void collectLevel(Node* root, int K, int* arr, int* count) {
    if (root == NULL) return;

    Queue* q = createQueue(100);
    enqueue(q, root);

    int level = 1;
    while (!isEmpty(q)) {
        int size = q->rear - q->front;
        if (level == K) {
            for (int i = 0; i < size; i++) {
                Node* node = dequeue(q);
                arr[(*count)++] = node->data;
                if (node->left) enqueue(q, node->left);
                if (node->right) enqueue(q, node->right);
            }
            return;
        } else {
            for (int i = 0; i < size; i++) {
                Node* node = dequeue(q);
                if (node->left) enqueue(q, node->left);
                if (node->right) enqueue(q, node->right);
            }
            level++;
        }
    }
}

// Compare nodes at level K
int compareLevel(Node* root1, Node* root2, int K) {
    int arr1[100], arr2[100];
    int count1 = 0, count2 = 0;

    collectLevel(root1, K, arr1, &count1);
    collectLevel(root2, K, arr2, &count2);

    if (count1 != count2) return 0;
    for (int i = 0; i < count1; i++) {
        if (arr1[i] != arr2[i]) return 0;
    }
    return 1;
}

int main() {
    int n1, n2, K;

    // First tree input
    scanf("%d", &n1);
    int arr1[n1];
    for (int i = 0; i < n1; i++) scanf("%d", &arr1[i]);

    // Second tree input
    scanf("%d", &n2);
    int arr2[n2];
    for (int i = 0; i < n2; i++) scanf("%d", &arr2[i]);

    // Level to compare
    scanf("%d", &K);

    Node* root1 = buildTree(arr1, n1);
    Node* root2 = buildTree(arr2, n2);

    if (compareLevel(root1, root2, K))
        printf("Yes\n");
    else
        printf("No\n");

    return 0;
}
