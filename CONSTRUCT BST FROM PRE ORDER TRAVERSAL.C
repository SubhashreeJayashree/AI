#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Utility function to create a new node
Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Recursive function to build BST from postorder
Node* constructBSTUtil(int post[], int* index, int min, int max, int n) {
    if (*index < 0) return NULL;

    int key = post[*index];
    Node* root = NULL;

    // Only place the key if it lies in the valid range
    if (key > min && key < max) {
        root = newNode(key);
        (*index)--;

        // Important: build right subtree first (since postorder is left-right-root)
        root->right = constructBSTUtil(post, index, key, max, n);
        root->left  = constructBSTUtil(post, index, min, key, n);
    }
    return root;
}

// Wrapper function
Node* constructBST(int post[], int n) {
    int index = n - 1;
    return constructBSTUtil(post, &index, INT_MIN, INT_MAX, n);
}

// Inorder traversal (should print sorted order for BST)
void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

int main() {
    int n;
    scanf("%d", &n);
    int post[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &post[i]);
    }

    Node* root = constructBST(post, n);

    inorder(root);
    printf("\n");

    return 0;
}
