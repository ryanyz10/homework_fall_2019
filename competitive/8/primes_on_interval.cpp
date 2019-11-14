#include <iostream>
#include <cmath>

bool is_prime(int n) {
    for (int i = 2; i <= std::sqrt(n); i++) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

int main() {
    int a, b, k;
    std::cin >> a >> b >> k;

    int num_primes[b - a + 1];

    for (int i = a; i <= b; i++) {
        if (i - a == 0) {
            num_primes[i - a] = is_prime(i) ? 1 : 0;
        } else {
            num_primes[i - a] = num_primes[i - a - 1] + (is_prime(i) ? 1 : 0);
        }
    }

    int result = b - a + 1;
    int low = a;
    int high = b;

    while (low < high) {
        int mid = low + (high - low) / 2;
        bool mid_prime = is_prime(mid);

        // find l
        bool valid = false;
        int l;
        for (l = 1; l <= b - a + 1 - mid; l++) {
            int total_primes = num_primes[mid + l - a] - num_primes[mid - a] + (mid_prime ? 1 : 0);

            if (total_primes == k) {
                valid = true;
                break;
            }
        }

        if (valid) {
            if (l < result) {
                result = l;
            }
        }

        if (!valid) {
            // no result was found
            high = mid - 1;
        } else {
            low = mid;
        }
    }

    std::cout << low << std::endl;
}
