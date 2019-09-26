#include <iostream> 
#include <vector> 
#include <unordered_set>
#include <algorithm>
#include <stdint.h>

int main() {
    int n;
    std::cin >> n;
    
    uint64_t adj_matrix[n + 1][n + 1];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            std::cin >> adj_matrix[i][j];
        }
    }

    bool removed[n + 1];
    for (int i = 1; i <=n; i++) {
        removed[i] = false;
    }

    int remove_order[n + 1];
    for (int i = n; i >= 1; i--) {
        std::cin >> remove_order[i];
    }

    uint64_t sums[n + 1];
    for (int i = 1; i <= n; i++) {
        sums[i] = 0;
    }

    for (int k = 1; k <= n; k++) {
        int vertex = remove_order[k];
        removed[vertex] = true;
        for (int v = 1; v <= n; v++) {
            for (int w = 1; w <= n; w++) {
                if (adj_matrix[v][w] > adj_matrix[v][vertex] + adj_matrix[vertex][w]) {
                    adj_matrix[v][w] = adj_matrix[v][vertex] + adj_matrix[vertex][w];
                }

                if (removed[v] && removed[w]) {
                    sums[k] += adj_matrix[v][w];
                }
            }
        }
    }

    for (int i = n; i >= 1; i--) {
        std::cout << sums[i] << " ";
    }

    std::cout << std::endl;

}

