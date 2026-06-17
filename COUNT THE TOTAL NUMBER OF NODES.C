#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Create a new node
Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Build binary tree from level order input
Node* insertLevelOrder(int arr[], int i, int n) {
    if (i >= n) return NULL;
    Node* root = createNode(arr[i]);
    root->left = insertLevelOrder(arr, 2 * i + 1, n);
    root->right = insertLevelOrder(arr, 2 * i + 2, n);
    return root;
}

// Count total nodes recursively
int countNodes(Node* root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    Node* root = insertLevelOrder(arr, 0, n);
    int total = countNodes(root);
    printf("Total Nodes: %d\n", total);
    return 0;
}
