#include <stdio.h>
#include <stdlib.h>

// Define BST node using typedef
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node into BST
Node* insert(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    // Ignore duplicates
    return root;
}

// Function to find minimum element in BST
int findMin(Node* root) {
    if (root == NULL) {
        printf("Tree is empty\n");
        exit(1);
    }
    Node* current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current->data;
}

int main() {
    int n, value;
    Node* root = NULL;

    // Read number of nodes
    scanf("%d", &n);

    // Insert nodes into BST
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        root = insert(root, value);
    }

    // Find and print minimum element
    printf("%d\n", findMin(root));

    return 0;
}
