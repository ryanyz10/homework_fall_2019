#include <iostream>

int twoFactors(int n) {
    if (n == 0) {
        return 0;
    }

    int count = 0;
    while ((n & 1) == 0) {
        n = n >> 1;
        count++;
    }

    return count;
}

int fiveFactors(int n) {
    if (n == 0) {
        return 0;
    }

    int count = 0;

    while (n % 5 == 0) {
        n /= 5;
        count++;
    }

    return count;
}

int main() {
    int n;
    std::cin >> n;

    // FIXME: twos, fives are at most 9. If we get OOM we can replace int with short
    int twos[n][n];
    int fives[n][n];
    std::string path[n][n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int curr;
            std::cin >> curr;
            twos[i][j] = twoFactors(curr);
            fives[i][j] = fiveFactors(curr);
        }
    }

    /*
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << "(" << twos[i][j] << ", " << fives[i][j] << ")";
        }

        std::cout << std::endl;
    }
    */

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (r == 0 && c == 0) {
                continue;
            }

            if (r == 0) {
                // right
                twos[r][c] += twos[r][c - 1];
                fives[r][c] += fives[r][c - 1];
                path[r][c] = path[r][c - 1] + 'R';
            } else if (c == 0) {
                // down
                twos[r][c] += twos[r - 1][c];
                fives[r][c] += fives[r - 1][c];
                path[r][c] = path[r - 1][c] + 'D';
            } else {
                int n2 = twos[r][c];
                int n5 = fives[r][c];
                int left = std::min(n2 + twos[r][c - 1], n5 + fives[r][c - 1]);
                int up = std::min(n2 + twos[r - 1][c], n5 + fives[r - 1][c]);

                if (left < up) {
                    twos[r][c] += twos[r][c - 1];
                    fives[r][c] += fives[r][c - 1];
                    path[r][c] = path[r][c - 1] + 'R';
                } else {
                    twos[r][c] += twos[r - 1][c];
                    fives[r][c] += fives[r - 1][c];
                    path[r][c] = path[r - 1][c] + 'D';
                }
            }

        }
    }

    /*
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << "\"" << path[i][j] << "\"" << " ";
        }

        std::cout << std::endl;
    }
    */

    std::cout << std::min(twos[n - 1][n - 1], fives[n - 1][n - 1]) << std::endl;
    std::cout << path[n - 1][n - 1] << std::endl;
}
