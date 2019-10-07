#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <vector>
#include <utility>
#include <limits>
#include <stdint.h>

int main() {
    uint64_t N, M, K;

    std::cin >> N >> M >> K;

    uint64_t lo = 1;
    uint64_t hi = N * M;

    if (K == 1) {
        std::cout << 1 << std::endl;
        return 0;
    }

    if (K == hi) {
        std::cout << hi << std::endl;
        return 0;
    }

    while (lo < hi) {
        uint64_t mid = (lo + hi) >> 1;

        uint64_t count = 0;

        for (uint64_t i = 1; i <= N; i++) {
            uint64_t tmp = mid / i;

            if (tmp == 0) {
                break;
            }

            count += tmp > M ? M : tmp;
        }

        if (count >= K) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    std::cout << lo << std::endl;

}
