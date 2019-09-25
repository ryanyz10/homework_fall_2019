#include <iostream> 
#include <vector> 
#include <unordered_set>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    
    int adj_matrix[n + 1][n + 1];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            std::cin >> adj_matrix[i][j];
        }
    }

    int distances[n + 1][n + 1];
    std::unordered_set<int> nodes;

    for (int i = 1; i <= n; i++) {
        nodes.insert(i);
    }


    for (int i = 0; i < n; i++) {
        int vertex_to_remove;
        std::cin >> vertex_to_remove;
        for (int i : nodes) {
            for (int j : nodes) {
                if (i == j) {
                    distances[i][j] = 0;
                } else {
                    distances[i][j] = adj_matrix[i][j];
                }
            }
        }

        for (int k : nodes) {
            for (int v : nodes) {
                for (int w : nodes) {
                    if (distances[v][w] > distances[v][k] + distances[k][w]) {
                        distances[v][w] = distances[v][k] + distances[k][w];
                    }
                }
            }
        }

        long sum = 0;
        for (int i : nodes) {
            for (int j : nodes) {
                sum += distances[i][j];
            }
        }

        std::cout << sum << " ";
        nodes.erase(vertex_to_remove);
    }

    std::cout << std::endl;
}

