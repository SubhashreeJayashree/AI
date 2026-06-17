#include <stdio.h>
#include <stdlib.h>

// Define BST node
struct Node {
    int data;
    struct Node *left, *right;
};

// Utility function to create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Insert into BST
struct Node* insert(struct Node* root, int data) {
    if (root == NULL) return newNode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else
        root->right = insert(root->right, data);
    return root;
}

// Find LCA in BST
struct Node* LCA(struct Node* root, int n1, int n2) {
    if (root == NULL) return NULL;

    // If both values are smaller, go left
    if (n1 < root->data && n2 < root->data)
        return LCA(root->left, n1, n2);

    // If both values are greater, go right
    if (n1 > root->data && n2 > root->data)
        return LCA(root->right, n1, n2);

    // Otherwise, root is the LCA
    return root;
}

int main() {
    int n;
    scanf("%d", &n);
    struct Node* root = NULL;

    // Read node values
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        root = insert(root, val);
    }

    int n1, n2;
    scanf("%d %d", &n1, &n2);

    struct Node* lca = LCA(root, n1, n2);
    if (lca != NULL)
        printf("%d\n", lca->data);

    return 0;
}
