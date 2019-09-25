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

}

