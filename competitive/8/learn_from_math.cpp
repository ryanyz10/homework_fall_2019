#include <iostream>
#include <cmath>

bool is_prime(int n) {
    if (n <= 2) {
        return true;
    }

    if ((n & 1) == 0) {
        return false;
    }
    
    for (int i = 2; i <= std::sqrt(n); i++) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

int main() {
    int n;
    std::cin >> n;

    for (int i = 4; i <= n/2; i++) {
        if (is_prime(i)) {
            continue;
        }

        if (!is_prime(n - i)) {
            std::cout << i << " " << n - i << std::endl;
            break;
        }
    }
}
