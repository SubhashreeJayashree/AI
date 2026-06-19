#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Use long long for costs and times to avoid overflow
typedef long long ll;

// Structure for a module/job
typedef struct {
    int id;
    ll t, w;
    double ratio; // w / t
} Module;

// --- Heap and DSU Structures ---
typedef struct {
    int id;
    ll t, w;
} HeapNode;

HeapNode heap[200005];
int heap_size = 0;
int heap_pos[200005]; // Tracks where a module's latest representation sits in the heap

// Function to compare two heap nodes (Max-Heap based on density w/t)
// w1/t1 > w2/t2  =>  w1 * t2 > w2 * t1
int compare_nodes(HeapNode a, HeapNode b) {
    ll val1 = a.w * b.t;
    ll val2 = b.w * a.t;
    if (val1 != val2) {
        return val1 > val2 ? 1 : -1;
    }
    return a.id < b.id ? 1 : -1;
}

void swap_nodes(int i, int j) {
    HeapNode temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
    heap_pos[heap[i].id] = i;
    heap_pos[heap[j].id] = j;
}

void push(HeapNode node) {
    heap[++heap_size] = node;
    heap_pos[node.id] = heap_size;
    int now = heap_size;
    while (now > 1 && compare_nodes(heap[now], heap[now / 2]) > 0) {
        swap_nodes(now, now / 2);
        now /= 2;
    }
}

void pop() {
    if (heap_size == 0) return;
    heap_pos[heap[1].id] = 0;
    heap[1] = heap[heap_size--];
    if (heap_size > 0) heap_pos[heap[1].id] = 1;
    int now = 1;
    while (now * 2 <= heap_size) {
        int next = now * 2;
        if (next + 1 <= heap_size && compare_nodes(heap[next + 1], heap[next]) > 0) {
            next++;
        }
        if (compare_nodes(heap[next], heap[now]) > 0) {
            swap_nodes(now, next);
            now = next;
        } else {
            break;
        }
    }
}

// DSU Find with path compression
int find_set(int v, int* parent_dsu) {
    if (v == parent_dsu[v])
        return v;
    return parent_dsu[v] = find_set(parent_dsu[v], parent_dsu);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    ll* t = (ll*)malloc((n + 1) * sizeof(ll));
    ll* w = (ll*)malloc((n + 1) * sizeof(ll));
    int* parent_tree = (int*)malloc((n + 1) * sizeof(int));
    int* parent_dsu = (int*)malloc((n + 1) * sizeof(int));

    ll total_cost = 0;

    for (int i = 1; i <= n; ++i) {
        scanf("%lld %lld", &t[i], &w[i]);
        total_cost += t[i] * w[i]; // Base self-completion cost
        parent_dsu[i] = i;
    }

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        parent_tree[v] = u;
    }

    // Push all non-root elements into our max-heap
    for (int i = 2; i <= n; ++i) {
        HeapNode node = {i, t[i], w[i]};
        push(node);
    }

    while (heap_size > 0) {
        HeapNode top = heap[1];
        pop();

        int u = top.id;
        // Verify if this is the canonical representing element of the DSU block
        if (find_set(u, parent_dsu) != u || t[u] != top.t || w[u] != top.w) {
            continue;
        }

        // Find the block containing the absolute parent dependency
        int p = find_set(parent_tree[u], parent_dsu);

        // Accumulate the cost incurred by delaying module u by the total duration of block p
        total_cost += t[p] * w[u];

        // Merge component u into component p
        parent_dsu[u] = p;
        t[p] += t[u];
        w[p] += w[u];

        // If the newly merged target parent block is not the primary tree root, update/re-push it
        if (p != 1) {
            HeapNode merged_node = {p, t[p], w[p]};
            push(merged_node);
        }
    }

    printf("%lld\n", total_cost);

    // Clean up memory allocations
    free(t);
    free(w);
    free(parent_tree);
    free(parent_dsu);

    return 0;
}
