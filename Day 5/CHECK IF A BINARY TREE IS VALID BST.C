#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure for a binary tree node
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// Function to create a new node
Node* createNode(int val) {
    if (val == -1) return NULL;
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Helper function to validate BST properties using min/max constraints
int isBSTUtil(Node* node, long long min, long long max) {
    if (node == NULL) return 1;

    // False if this node violates the min/max constraints
    if (node->data <= min || node->data >= max) return 0;

    // Check the subtrees recursively with updated constraints
    return isBSTUtil(node->left, min, node->data) &&
           isBSTUtil(node->right, node->data, max);
}

int isBST(Node* root) {
    // Use LLONG_MIN and LLONG_MAX to avoid integer overflow issues
    return isBSTUtil(root, LLONG_MIN, LLONG_MAX);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 0;
    }

    int *arr = (int*)malloc(sizeof(int) * 2005); // Allocate safe extra size for inputs
    int count = 0;
    int val;
    
    // Read elements until we fill the tree nodes (or safely read the stream)
    while (scanf("%d", &val) != EOF) {
        arr[count++] = val;
    }

    if (count == 0 || arr[0] == -1) {
        printf("Yes\n");
        free(arr);
        return 0;
    }

    // Level-order reconstruction using a queue
    Node* root = createNode(arr[0]);
    Node** queue = (Node**)malloc(sizeof(Node*) * 2005);
    int head = 0, tail = 0;
    
    queue[tail++] = root;
    int i = 1;

    while (head < tail && i < count) {
        Node* current = queue[head++];

        if (current != NULL) {
            // Assign left child
            if (i < count) {
                current->left = createNode(arr[i]);
                if (arr[i] != -1) {
                    queue[tail++] = current->left;
                }
                i++;
            }
            // Assign right child
            if (i < count) {
                current->right = createNode(arr[i]);
                if (arr[i] != -1) {
                    queue[tail++] = current->right;
                }
                i++;
            }
        }
    }

    // Validate the reconstructed tree
    if (isBST(root)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    // Clean up allocated memory
    free(arr);
    free(queue);
    return 0;
}
