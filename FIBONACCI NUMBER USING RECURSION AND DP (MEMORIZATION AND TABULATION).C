#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000
long long memo[MAXN+1];   // for memoization

// Recursive version (safe for N <= 40)
long long fibRec(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibRec(n-1) + fibRec(n-2);
}

// Memoization (Top-Down)
long long fibMemo(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (memo[n] != -1) return memo[n];
    memo[n] = fibMemo(n-1) + fibMemo(n-2);
    return memo[n];
}

// Tabulation (Bottom-Up)
long long fibTab(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    long long *dp = (long long*)malloc((n+1) * sizeof(long long));
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    long long ans = dp[n];
    free(dp);
    return ans;
}

int main() {
    int N;
    scanf("%d", &N);

    // Recursion (only safe for small N)
    if (N <= 40) {
        printf("Recursion: %lld\n", fibRec(N));
    } else {
        printf("Recursion: Not computed (N too large)\n");
    }

    // Memoization
    for (int i = 0; i <= N; i++) memo[i] = -1;
    printf("Memoization: %lld\n", fibMemo(N));

    // Tabulation
    printf("Tabulation: %lld\n", fibTab(N));

    return 0;
}
