#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <vector>
#include <utility>
#include <limits>
 
template <> struct std::hash<std::pair<int, int>> {
    std::size_t operator()(const std::pair<int,int>& k) const {
        using std::size_t;
        using std::hash;
        using std::string;

        return ((hash<int>()(k.first) ^ (hash<int>()(k.second) << 1)) >> 1);
    }
};

struct ComparePair {
    bool operator() (std::pair<int, int> p1, std::pair<int, int> p2) {
        return p1.second > p2.second;
    }
};

int main() {
    int n, m, s;
    std::cin >> n >> m >> s;

    std::unordered_map<int,int> neighbors[n + 1];
    for (int i = 1; i <= n; i++) {
        neighbors[i] = std::unordered_map<int, int>();
    }

    for (int i = 0; i < m; i++) {
        int v, u, w;
        std::cin >> v >> u >> w;

        neighbors[v].insert(std::make_pair(u, w));
        neighbors[u].insert(std::make_pair(v, w));
    }

    int l;
    std::cin >> l;

    int min_distances[n + 1]; // min distances from S to each node
    bool visited[n + 1];

    for (int i = 1; i <= n; i++) {
        visited[i] = false;
        min_distances[i] = INT_MAX;
    }

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, ComparePair> pq;
    pq.push(std::make_pair(s, 0));

    while (!pq.empty()) {
        std::pair<int,int> curr = pq.top();
        pq.pop();

        int curr_node = curr.first;
        int curr_dist = curr.second;

        std::cout << "Popped node " << curr_node << " with distance " << curr_dist << std::endl;

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


    for (int i = 1; i <= n; i++) {
        std::cout << min_distances[i] << " ";
    }

    std::cout << std::endl;

    int silos_on_node = 0;
    std::unordered_map<std::pair<int,int>, std::unordered_set<int>> silos_on_road;
    int silos_on_road_count = 0;

    for (int i = 1; i <= n; i++) {
        int min_distance = min_distances[i];
        if (min_distance == l) {
            std::cout << "Adding silo at node " << i << std::endl;
            silos_on_node++;
        } else {
            // loop through neighbors and try each edge
            for (std::pair<int, int> neighbor : neighbors[i]) {
                int neighbor_node = neighbor.first;
                int neighbor_dist = neighbor.second;

                if (min_distance < l && min_distance + neighbor_dist > l) {
                    int interval_start = std::min(neighbor_node, i);
                    int interval_end = std::max(neighbor_node, i);
                    int interval_travel = interval_start == i ? l - min_distance : neighbor_dist - l + min_distance;
                    std::cout << "Testing interval (" << interval_start << ", " << interval_end << ") and travel " << interval_travel << std::endl;

                    std::pair<int, int> interval = std::make_pair(interval_start, interval_end);

                    if (!silos_on_road.count(interval)) {
                        silos_on_road.insert(std::make_pair(interval, std::unordered_set<int>()));
                        silos_on_road.at(interval).insert(interval_travel);
                        silos_on_road_count++;
                    } else {
                        if (!silos_on_road.at(interval).count(interval_travel)) {
                            silos_on_road.at(interval).insert(interval_travel); 
                            silos_on_road_count++;
                        }
                    }
                }
            }
        }
    }

    std::cout << silos_on_node + silos_on_road_count << std::endl;
}

