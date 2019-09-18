#include <iostream>
#include <queue>
#include <limits>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <vector>
#include <utility>
using namespace std;

struct Data {
    int node;
    int prev_node; // the previous node
    int dist; // the remaining distance
    int prev_dist; // the previously traveled distance
    bool on_node;

    friend bool operator<(const Data& t1, const Data& t2) {
        return t1.dist > t2.dist;
    }
};

template <>
  struct hash<std::pair<int, int>>
  {
    std::size_t operator()(const std::pair<int,int>& k) const
    {
      using std::size_t;
      using std::hash;
      using std::string;

      return ((hash<int>()(k.first)
               ^ (hash<int>()(k.second) << 1)) >> 1);
    }
};

int main() {
    int n, m, s;

    cin >> n >> m >> s;
    
    unordered_map<int,int> neighbors[n + 1];

    for (int i = 1; i <= n; i++) {
        neighbors[i] = unordered_map<int,int>();
    }


    for (int i = 0; i < m; i++) {
        int v,u,w;
        cin >> v >> u >> w;

        neighbors[v].insert(std::make_pair(u, w));
        neighbors[u].insert(std::make_pair(v, w));
    }

    int l;
    cin >> l;

    unordered_set<int> silos_on_nodes;
    unordered_map<std::pair<int, int>, unordered_set<int>> silos_on_roads;
    int count = 0;

    std::priority_queue<Data, vector<Data>, std::less<Data>> pq;
    bool visited[n + 1];
    for (int i = 1; i <= n; i++) {
        visited[i] = false;
    }

    pq.push(Data {s, 0, l, 0, true});

    while (!pq.empty()) {
        Data curr = pq.top();
        pq.pop();

        int curr_node = curr.node;
        int curr_dist = curr.dist;
        int prev_node = curr.prev_node;
        int prev_dist = curr.prev_dist;
        bool on_node = curr.on_node;

        cout << "Node: " << curr_node << " | Dist: " << curr_dist << " | Prev Node: "  << prev_node << " | Prev Dist: " << prev_dist << " | On Node: " << (on_node ? "true" : "false") << endl;

        if (curr_dist == 0) {
            if (on_node) {
                cout << "Adding silo at node " << curr_node << "!" << endl;
                silos_on_nodes.insert(curr_node);
                visited[curr_node] = true;
            } else {
                // TODO check if silo exists at location on road
                // standardize start/end nodes
                int interval_start = std::min(curr_node, prev_node);
                int interval_end = std::max(curr_node, prev_node);
                int interval_length = neighbors[interval_start].at(interval_end);
                int interval_travel = interval_start == curr_node ? interval_length - prev_dist : prev_dist;

                std::pair<int, int> interval = std::make_pair(interval_start, interval_end);
                cout << "Testing interval (" << interval_start << ", " << interval_end << ") and travel " << interval_travel << endl;

                if (silos_on_roads.count(interval) == 0) {
                    cout << "No match found" << endl;
                    silos_on_roads.insert(std::make_pair(interval, unordered_set<int>()));
                    silos_on_roads.at(interval).insert(interval_travel);
                    cout << "Adding silo at on interval (" << interval_start << ", " << interval_end << ") and traveled " << interval_travel << endl;
                    count++;
                } else {
                    cout << "Match found with length " << interval_travel << endl;
                    if (silos_on_roads.at(interval).count(interval_travel) == 0) {
                        silos_on_roads.at(interval).insert(interval_travel);
                        cout << "Adding silo at on interval (" << interval_start << ", " << interval_end << ") and traveled " << interval_travel << endl;
                        count++;
                    } else {
                        cout << "Ignoring match" << endl;
                    }
                }
            }

            cout << endl;
            continue;
        }

        if (visited[curr_node]) {
            cout << endl;
            continue;
        }

        visited[curr_node] = true;

        for (std::pair<int, int> nb : neighbors[curr_node]) {
            int nb_node = nb.first;
            int dist_to_nb = nb.second;

            if (dist_to_nb > curr_dist) {
                if (nb_node == prev_node) {
                    cout << endl;
                    continue;
                }
                pq.push(Data {nb_node, curr_node, 0, curr_dist, false});
            } else {
                if (visited[nb_node]) {
                    cout << endl;
                    continue;
                }

                pq.push(Data {nb_node, curr_node, curr_dist - dist_to_nb, dist_to_nb, true});
            }

        }

        cout << endl;
    }

    cout << silos_on_nodes.size() + count << endl;

}
