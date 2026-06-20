#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000007
#define MAX_N 2001
#define MAX_VAL 2001
#define MAX_K 11

// dp[i][lenParity][targetParity] = number of subsequences ending at item i
// lenParity = 0 (even), 1 (odd)
// targetParity = 0 (even count of target color), 1 (odd count)
long long dp[MAX_N][2][2];

int values[MAX_N], colors[MAX_N];

int main() {
    int N, K, C_target;
    scanf("%d %d %d", &N, &K, &C_target);

    for (int i = 0; i < N; i++) scanf("%d", &values[i]);
    for (int i = 0; i < N; i++) scanf("%d", &colors[i]);

    long long result = 0;

    for (int i = 0; i < N; i++) {
        // Start new subsequence with item i
        int lenParity = 1; // length = 1 (odd)
        int targetParity = (colors[i] == C_target) ? 1 : 0;
        dp[i][lenParity][targetParity] = (dp[i][lenParity][targetParity] + 1) % MOD;

        // Extend subsequences ending at earlier items j
        for (int j = 0; j < i; j++) {
            if (values[j] < values[i] && colors[j] != colors[i]) {
                for (int lp = 0; lp < 2; lp++) {
                    for (int tp = 0; tp < 2; tp++) {
                        long long ways = dp[j][lp][tp];
                        if (ways == 0) continue;

                        int newLenParity = lp ^ 1; // flip parity
                        int newTargetParity = tp ^ (colors[i] == C_target ? 1 : 0);

                        dp[i][newLenParity][newTargetParity] =
                            (dp[i][newLenParity][newTargetParity] + ways) % MOD;
                    }
                }
            }
        }

        // Count subsequences ending at i that satisfy rules
        result = (result + dp[i][1][0]) % MOD; // odd length, even target count
    }

    printf("%lld\n", result);
    return 0;
}
