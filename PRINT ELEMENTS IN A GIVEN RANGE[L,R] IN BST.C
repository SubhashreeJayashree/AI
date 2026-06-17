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

// Print elements in range [L, R] using inorder traversal
void printRange(struct Node* root, int L, int R) {
    if (root == NULL) return;

    // If root->data > L, then left subtree may have values in range
    if (root->data > L)
        printRange(root->left, L, R);

    // If root->data lies in range, print it
    if (root->data >= L && root->data <= R)
        printf("%d ", root->data);

    // If root->data < R, then right subtree may have values in range
    if (root->data < R)
        printRange(root->right, L, R);
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

    int L, R;
    scanf("%d %d", &L, &R);

    printRange(root, L, R);
    return 0;
}
