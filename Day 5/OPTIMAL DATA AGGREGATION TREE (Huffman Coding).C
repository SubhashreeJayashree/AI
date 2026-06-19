#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

// Adjacency list for the tree structure (to store children)
typedef struct {
    int* items;
    int size;
    int capacity;
} AdjList;

void initAdjList(AdjList* list) {
    list->size = 0;
    list->capacity = 4;
    list->items = (int*)malloc(list->capacity * sizeof(int));
}

void appendAdjList(AdjList* list, int item) {
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        list->items = (int*)realloc(list->items, list->capacity * sizeof(int));
    }
    list->items[list->size++] = item;
}

// Min-Heap structure for Huffman merging
typedef struct {
    ll* data;
    int size;
} MinHeap;

void heapifyObj(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->data[left] < heap->data[smallest])
        smallest = left;
    if (right < heap->size && heap->data[right] < heap->data[smallest])
        smallest = right;

    if (smallest != idx) {
        ll temp = heap->data[idx];
        heap->data[idx] = heap->data[smallest];
        heap->data[smallest] = temp;
        heapifyObj(heap, smallest);
    }
}

void insertHeap(MinHeap* heap, ll val) {
    heap->data[heap->size] = val;
    int i = heap->size;
    heap->size++;

    while (i != 0 && heap->data[(i - 1) / 2] > heap->data[i]) {
        ll temp = heap->data[i];
        heap->data[i] = heap->data[(i - 1) / 2];
        heap->data[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

ll extractMin(MinHeap* heap) {
    if (heap->size <= 0) return 0;
    if (heap->size == 1) {
        heap->size--;
        return heap->data[0];
    }

    ll root = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapifyObj(heap, 0);

    return root;
}

// Global tree structures
AdjList* adj;
ll* subtree_size;
ll total_merge_cost = 0;

// Dynamic heap storage to avoid repetitive reallocations
ll* heap_buffer;

// DFS to calculate subtree sizes and compute the local merge costs
void dfs(int u) {
    int num_children = adj[u].size;
    
    // Bottom-up traversal: process children first
    for (int i = 0; i < num_children; i++) {
        dfs(adj[u].items[i]);
        subtree_size[u] += subtree_size[adj[u].items[i]];
    }
    
    // If the node has more than 1 child, compute the optimal merge cost
    if (num_children > 1) {
        MinHeap heap;
        heap.data = heap_buffer; 
        heap.size = 0;
        
        for (int i = 0; i < num_children; i++) {
            insertHeap(&heap, subtree_size[adj[u].items[i]]);
        }
        
        while (heap.size > 1) {
            ll first = extractMin(&heap);
            ll second = extractMin(&heap);
            ll cost = first + second;
            total_merge_cost += cost;
            insertHeap(&heap, cost);
        }
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    adj = (AdjList*)malloc((n + 1) * sizeof(AdjList));
    subtree_size = (ll*)calloc((n + 1), sizeof(ll));
    heap_buffer = (ll*)malloc((n + 1) * sizeof(ll));

    for (int i = 1; i <= n; i++) {
        initAdjList(&adj[i]);
    }

    // Read tree relationships
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        if (scanf("%d %d", &u, &v) == 2) {
            appendAdjList(&adj[u], v);
        }
    }

    int l;
    if (scanf("%d", &l) != 1) return 0;

    // Read leaf specifications
    for (int i = 0; i < l; i++) {
        int leaf_id;
        ll leaf_size;
        if (scanf("%d %lld", &leaf_id, &leaf_size) == 2) {
            subtree_size[leaf_id] = leaf_size;
        }
    }

    // Traverse the tree starting from the root node (1)
    dfs(1);

    // Output the total calculated optimal cost
    printf("%lld\n", total_merge_cost);

    // Free resources
    for (int i = 1; i <= n; i++) {
        free(adj[i].items);
    }
    free(adj);
    free(subtree_size);
    free(heap_buffer);

    return 0;
}
