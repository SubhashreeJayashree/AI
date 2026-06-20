#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF LLONG_MAX

long long min(long long a, long long b) {
    return (a < b) ? a : b;
}

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    long long L;
    int N;
    scanf("%lld", &L);
    scanf("%d", &N);

    int cuts[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &cuts[i]);
    }

    // Sort cuts
    qsort(cuts, N, sizeof(int), cmp);

    // Extended cuts array: add 0 and L
    int extended[N+2];
    extended[0] = 0;
    for (int i = 0; i < N; i++) {
        extended[i+1] = cuts[i];
    }
    extended[N+1] = (int)L;

    int M = N + 2; // total length of extended array

    // DP table
    long long dp[M][M];
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            dp[i][j] = 0;
        }
    }

    // Build DP table by increasing gap
    for (int gap = 2; gap < M; gap++) {
        for (int i = 0; i + gap < M; i++) {
            int j = i + gap;
            dp[i][j] = INF;
            for (int k = i+1; k < j; k++) {
                long long cost = dp[i][k] + dp[k][j] + (extended[j] - extended[i]);
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    printf("%lld\n", dp[0][M-1]);
    return 0;
}
