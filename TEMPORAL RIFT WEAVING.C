#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000007

// DP table: dp[c][e] = number of ways to reach cell (r, c) with energy e.
// We use two arrays (for the current and previous row) to optimize space.
// The energy 'e' is mapped to an index using an offset.
long long dp[75][3001]; // Max C=75, Max E range = 2*1500+1 = 3001
long long prev_dp[75][3001];

int main() {
    int R, C, E_max;
    scanf("%d %d %d", &R, &C, &E_max);

    int T[R][C];
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            scanf("%d", &T[i][j]);
        }
    }

    // The energy 'e' can range from -E_max to +E_max.
    // We use an offset to map this range to array indices [0, 2*E_max].
    int offset = E_max;
    int energy_range = 2 * E_max + 1;

    // --- Base Case: Start at (0, 0) ---
    // At (0,0), the energy is 0. There's 1 way to be here.
    // Check if |0| <= E_max, which is always true for E_max >= 0.
    dp[0][0 + offset] = 1;

    // --- DP Iteration ---
    // Iterate through each cell of the grid
    for (int r = 0; r < R; r++) {
        // For the first row (r=0), we only need to handle moves from the left.
        // For subsequent rows, we handle moves from above and left.
        if (r > 0) {
             // For r > 0, the dp state from the previous row becomes prev_dp
             // and the current row's dp is reset.
             memcpy(prev_dp, dp, sizeof(dp));
             memset(dp, 0, sizeof(dp));
        }

        for (int c = 0; c < C; c++) {
            // --- Transition from Above (r-1, c) -> (r, c) ---
            if (r > 0) {
                int delta_E = T[r][c] - T[r-1][c];
                // Iterate through all possible energy states from the cell above
                for (int e = -E_max; e <= E_max; e++) {
                    if (prev_dp[c][e + offset] > 0) {
                        int new_E = e + delta_E;
                        // Check Paradox Avoidance condition
                        if (abs(new_E) <= E_max) {
                            dp[c][new_E + offset] = (dp[c][new_E + offset] + prev_dp[c][e + offset]) % MOD;
                        }
                    }
                }
            }

            // --- Transition from Left (r, c-1) -> (r, c) ---
            if (c > 0) {
                int delta_E = T[r][c] - T[r][c-1];
                 // Iterate through all possible energy states from the cell to the left
                for (int e = -E_max; e <= E_max; e++) {
                    if (dp[c-1][e + offset] > 0) {
                        int new_E = e + delta_E;
                        // Check Paradox Avoidance condition
                        if (abs(new_E) <= E_max) {
                            dp[c][new_E + offset] = (dp[c][new_E + offset] + dp[c-1][e + offset]) % MOD;
                        }
                    }
                }
            }
        }
    }

    // --- Final Answer ---
    // The result is the number of ways to reach the destination (R-1, C-1)
    // with a final energy of exactly 0.
    long long final_ways = dp[C-1][0 + offset];
    
    printf("%lld\n", final_ways);

    return 0;
}
