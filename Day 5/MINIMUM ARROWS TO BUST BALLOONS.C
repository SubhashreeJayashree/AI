#include <stdio.h>
#include <stdlib.h>

// Structure to store the x-interval coordinates of a balloon
typedef struct {
    int start;
    int end;
} Balloon;

// Comparator function to sort balloons by their end coordinate safely
int compareBalloons(const void *a, const void *b) {
    Balloon *balloonA = (Balloon *)a;
    Balloon *balloonB = (Balloon *)b;
    
    // Explicit comparison prevents integer overflow/underflow issues
    if (balloonA->end < balloonB->end) return -1;
    if (balloonA->end > balloonB->end) return 1;
    
    // If end coordinates match, sort by start coordinates
    if (balloonA->start < balloonB->start) return -1;
    if (balloonA->start > balloonB->start) return 1;
    
    return 0;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("0\n");
        return 0;
    }

    // Allocate memory for N balloons dynamically
    Balloon *balloons = (Balloon *)malloc(sizeof(Balloon) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &balloons[i].start, &balloons[i].end);
    }

    // Sort balloons based on their end coordinates
    qsort(balloons, n, sizeof(Balloon), compareBalloons);

    // Initial arrow counting logic
    int arrows = 1;
    int last_arrow_pos = balloons[0].end;

    for (int i = 1; i < n; i++) {
        // If the current balloon starts after the last shot arrow position,
        // it cannot be burst by the previous arrow. We need a new one.
        if (balloons[i].start > last_arrow_pos) {
            arrows++;
            last_arrow_pos = balloons[i].end; // Position the new arrow at the current balloon's end coordinate
        }
    }

    // Print final result
    printf("%d\n", arrows);

    // Deallocate memory
    free(balloons);
    return 0;
}
