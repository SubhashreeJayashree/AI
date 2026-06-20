#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007
#define MAX_F 151       // Max possible final frequency (100 + 50)
#define MAX_B 2501      // Max possible total boost

static int dp[51][MAX_B][MAX_F];   // dp[i][sum][freq]

int main() {
    int N, Bmax, Btotal;
    scanf("%d %d %d", &N, &Bmax, &Btotal);

    int F[51];
    for (int i = 0; i < N; i++) scanf("%d", &F[i]);

    // Base case: amplifier 0
    for (int b = 0; b <= Bmax; b++) {
        int f = F[0] + b;
        dp[0][b][f] = 1;
    }

    // Transition
    for (int i = 0; i < N - 1; i++) {
        for (int s = 0; s <= Btotal; s++) {
            for (int f = 1; f < MAX_F; f++) {
                if (dp[i][s][f] == 0) continue;
                for (int b = 0; b <= Bmax; b++) {
                    int ns = s + b;
                    if (ns > Btotal) continue;
                    int nf = F[i+1] + b;
                    if (nf % f == 0) {
                        dp[i+1][ns][nf] = (dp[i+1][ns][nf] + dp[i][s][f]) % MOD;
                    }
                }
            }
        }
    }

    // Answer: sum over all final frequencies at last amplifier with total boost = Btotal
    long long ans = 0;
    for (int f = 1; f < MAX_F; f++) {
        ans = (ans + dp[N-1][Btotal][f]) % MOD;
    }

    printf("%lld\n", ans);
    return 0;
}
