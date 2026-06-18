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
    // If data == root->data, do nothing (no duplicates)
    return root;
}

// Inorder traversal (Left → Root → Right)
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    int n, value;
    Node* root = NULL;

    // Read number of initial nodes
    scanf("%d", &n);

    // Insert initial nodes
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        root = insert(root, value);
    }

    // Insert additional node
    scanf("%d", &value);
    root = insert(root, value);

    // Print inorder traversal
    inorder(root);
    printf("\n");

    return 0;
}
