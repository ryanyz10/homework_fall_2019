#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <vector>
#include <utility>
#include <limits>
 
namespace std {

    template <> 
    struct hash<std::pair<int, int>> {
        std::size_t operator()(const std::pair<int,int>& k) const {
            using std::size_t;
            using std::hash;
            using std::string;

            return ((hash<int>()(k.first) ^ (hash<int>()(k.second) << 1)) >> 1);
        }
    };
}

struct compare_pair {
    bool operator()(std::pair<int,int> p1, std::pair<int,int> p2) {
        return p1.second > p2.second;
    }
};

struct edge {
    int n1;
    int n2;
    int dist;
};

int main() {
    int n, m, s;
    std::cin >> n >> m >> s;

    std::unordered_map<int, int> neighbors[n + 1];
    std::vector<edge> edges;

    for (int i = 1; i <= n; i++) {
        neighbors[i] = std::unordered_map<int, int>();
    }

    for (int i = 0; i < m; i++) {
        int v, u, w;

        std::cin >> v >> u >> w;

        neighbors[v].insert(std::make_pair(u, w));
        neighbors[u].insert(std::make_pair(v, w));
        edges.push_back(edge {v, u, w});
    }

    int l;
    std::cin >> l;

    std::unordered_set<int> shortest_paths[n + 1];
    int min_distances[n + 1];
    bool visited[n + 1];

    for (int i = 1; i <= n; i++) {
        min_distances[i] = INT_MAX;
        visited[i] = false;
    }

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int,int>>, compare_pair> pq;
    pq.push(std::make_pair(s, 0));

    while (!pq.empty()) {
        std::pair<int,int> curr = pq.top();
        pq.pop();

        int curr_node = curr.first;
        int curr_dist = curr.second;

        if (curr_dist < min_distances[curr_node]) {
            min_distances[curr_node] = curr_dist; 
        }

        if (visited[curr_node]) {
            continue;
        }

        visited[curr_node] = true;

        for (std::pair<int, int> neighbor : neighbors[curr_node]) {
            int next_node = neighbor.first;
            int dist_to_next = neighbor.second;

            if (visited[next_node]) {
                continue;
            }

            pq.push(std::make_pair(next_node, curr_dist + dist_to_next));
        }
    }

    int silos_on_node = 0;
    int silos_on_road = 0;

    for (int i = 1; i <= n; i++) {
        int min_distance = min_distances[i];
        if (min_distance == l) {
            silos_on_node++;
        }
    }

    for (edge e : edges) {
        int u = e.n1;
        int v = e.n2;
        int w = e.dist;

        if (min_distances[u] < l && min_distances[u] + w > l) {
            int other_dist = w - l + min_distances[u];

            if (other_dist + min_distances[v] == l) {
                silos_on_road++;
                continue; 
            } else if (other_dist + min_distances[v] > l) {
                silos_on_road++; 
            }
        }

        if (min_distances[v] < l && min_distances[v] + w > l) {
            int other_dist = w - l + min_distances[v];

            if (other_dist + min_distances[u] < l) {
                continue;
            }

            silos_on_road++;
        }
    }

    std::cout << silos_on_road + silos_on_node << std::endl;
}

