#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

// Queue for building tree
typedef struct Queue {
    Node** arr;
    int front, rear, size;
} Queue;

Queue* createQueue(int capacity) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->arr = (Node**)malloc(capacity * sizeof(Node*));
    q->front = 0;
    q->rear = 0;
    q->size = capacity;
    return q;
}

void enqueue(Queue* q, Node* node) {
    q->arr[q->rear++] = node;
}

Node* dequeue(Queue* q) {
    return q->arr[q->front++];
}

int isQueueEmpty(Queue* q) {
    return q->front == q->rear;
}

// Global pointers to keep track of the DLL state during inorder traversal
Node* head = NULL;
Node* prev = NULL;

// In-place conversion of binary tree to DLL using inorder traversal
void bToDLL(Node* root) {
    if (root == NULL) return;

    // Recur for left subtree
    bToDLL(root->left);

    // Process current node
    if (prev == NULL) {
        head = root; // First node processed becomes the head of DLL
    } else {
        root->left = prev;
        prev->right = root;
    }
    prev = root;

    // Recur for right subtree
    bToDLL(root->right);
}

// Function to print the doubly linked list
void printList(Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->right;
    }
    printf("\n");
}

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    int* val = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &val[i]);
    }

    if (val[0] == -1) {
        free(val);
        return 0;
    }

    // Build the binary tree from level order array representation
    Node* root = (Node*)malloc(sizeof(Node));
    root->data = val[0];
    root->left = root->right = NULL;

    Queue* q = createQueue(n + 1);
    enqueue(q, root);

    int i = 1;
    while (!isQueueEmpty(q) && i < n) {
        Node* curr = dequeue(q);

        // Process left child
        if (i < n && val[i] != -1) {
            curr->left = (Node*)malloc(sizeof(Node));
            curr->left->data = val[i];
            curr->left->left = curr->left->right = NULL;
            enqueue(q, curr->left);
        }
        i++;

        // Process right child
        if (i < n && val[i] != -1) {
            curr->right = (Node*)malloc(sizeof(Node));
            curr->right->data = val[i];
            curr->right->left = curr->right->right = NULL;
            enqueue(q, curr->right);
        }
        i++;
    }

    // Convert to DLL
    bToDLL(root);

    // Print the resultant list
    printList(head);

    // Free dynamically allocated memory
    free(val);
    free(q->arr);
    free(q);

    return 0;
}
