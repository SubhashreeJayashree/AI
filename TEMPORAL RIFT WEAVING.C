#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000007

// DP tables: dp[c][e] = number of ways to reach cell (r,c) with energy e
// We use two arrays (current row and previous row) to optimize space
long long dp[75][3001];
long long prev_dp[75][3001];

int main() {
    int R, C, Emax;
    scanf("%d %d %d", &R, &C, &Emax);

    int T[75][75];
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            scanf("%d", &T[i][j]);
        }
    }

    int offset = Emax; // map energy [-Emax..Emax] to index [0..2*Emax]
    int maxRange = 2 * Emax + 1;

    // Initialize DP for first cell (0,0) with energy = 0
    memset(prev_dp, 0, sizeof(prev_dp));
    prev_dp[0][offset] = 1;

    // Process row by row
    for (int r = 0; r < R; r++) {
        memset(dp, 0, sizeof(dp));
        for (int c = 0; c < C; c++) {
            for (int e = 0; e < maxRange; e++) {
                long long ways = prev_dp[c][e];
                if (ways == 0) continue;

                int energy = e - offset;

                // Move Right
                if (c + 1 < C) {
                    int newEnergy = energy + (T[r][c+1] - T[r][c]);
                    if (newEnergy >= -Emax && newEnergy <= Emax) {
                        dp[c+1][newEnergy + offset] = 
                            (dp[c+1][newEnergy + offset] + ways) % MOD;
                    }
                }

                // Move Down
                if (r + 1 < R) {
                    int newEnergy = energy + (T[r+1][c] - T[r][c]);
                    if (newEnergy >= -Emax && newEnergy <= Emax) {
                        prev_dp[c][newEnergy + offset] = 
                            (prev_dp[c][newEnergy + offset] + ways) % MOD;
                    }
                }
            }
        }
        // Copy current row dp into prev_dp for next row
        memcpy(prev_dp, dp, sizeof(dp));
    }

    // Answer: number of ways to reach (R-1,C-1) with energy = 0
    printf("%lld\n", prev_dp[C-1][offset] % MOD);
    return 0;
}
