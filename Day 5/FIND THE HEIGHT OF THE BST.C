#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Function to create a new BST node
Node* createNode(int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a value into the BST sequentially
Node* insert(Node* root, int val) {
    if (root == NULL) {
        return createNode(val);
    }
    if (val < root->data) {
        root->left = insert(root->left, val);
    } else {
        root->right = insert(root->right, val);
    }
    return root;
}

// Function to calculate the height of the BST
int findHeight(Node* root) {
    if (root == NULL) {
        return -1; // Height of empty tree is -1
    }
    
    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);
    
    // Find the max path and add 1 for the current edge
    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    } else {
        return rightHeight + 1;
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("-1\n");
        return 0;
    }
    
    Node* root = NULL;
    for (int i = 0; i < n; i++) {
        int val;
        if (scanf("%d", &val) == 1) {
            root = insert(root, val);
        }
    }
    
    // Calculate and print the height of the tree
    int height = findHeight(root);
    printf("%d\n", height);
    
    return 0;
}
