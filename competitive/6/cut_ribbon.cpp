#include <iostream>

int main() {
    int n, a, b, c;
    std::cin >> n >> a >> b >> c;

    int dp[n + 1];
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        int max = -1;
        if (i >= a) {
            max = std::max(max, dp[i - a]); 
        }

        if (i >= b) {
            max = std::max(max, dp[i - b]);
        }

        if (i >= c) {
            max = std::max(max, dp[i - c]);
        }

        if (max < 0) {
            dp[i] = -1;
        } else {
            dp[i] = max + 1;
        }
    }

    std::cout << dp[n] << std::endl;
}
