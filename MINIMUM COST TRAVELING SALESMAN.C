#include <stdio.h>
#include <limits.h>

#define MAXN 18
#define INF LLONG_MAX

long long dp[1 << MAXN][MAXN];
int cost[MAXN][MAXN];
int N;

long long min(long long a, long long b) {
    return (a < b) ? a : b;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    int totalMasks = 1 << N;

    // Initialize DP table
    for (int mask = 0; mask < totalMasks; mask++) {
        for (int i = 0; i < N; i++) {
            dp[mask][i] = INF;
        }
    }

    // Base case: starting at city 0
    dp[1][0] = 0;

    // Fill DP table
    for (int mask = 1; mask < totalMasks; mask++) {
        for (int u = 0; u < N; u++) {
            if (!(mask & (1 << u))) continue; // city u not visited
            if (dp[mask][u] == INF) continue;

            for (int v = 0; v < N; v++) {
                if (mask & (1 << v)) continue; // already visited
                int nextMask = mask | (1 << v);
                dp[nextMask][v] = min(dp[nextMask][v], dp[mask][u] + cost[u][v]);
            }
        }
    }

    // Final answer: all cities visited, return to city 0
    int allVisitedMask = (1 << N) - 1;
    long long ans = INF;
    for (int i = 0; i < N; i++) {
        if (dp[allVisitedMask][i] != INF) {
            ans = min(ans, dp[allVisitedMask][i] + cost[i][0]);
        }
    }

    printf("%lld\n", ans);
    return 0;
}
