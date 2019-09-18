#include <iostream> 
#include <queue>
#include <limits>
#include <unordered_set>
using namespace std;

struct Info {
    int num;
    int ops;

    Info(int num, int ops) : num(num), ops(ops) {} 
};
  
int main() { 
    int n, m;
    cin >> n;
    cin >> m;

    queue<Info> queue;
    queue.push(Info(n, 0));

    unordered_set<int> visited;

    while (!queue.empty()) {
        Info info = queue.front();
        int num = info.num;
        int ops = info.ops;
        queue.pop();

        if (num == m) {
            cout << ops << endl;
            break;
        }

        visited.insert(num);
        if (num < m && visited.find(num << 1) == visited.end()) {
            queue.push(Info(num << 1, ops + 1));
        }

        if (visited.find(num - 1) == visited.end()) {
            queue.push(Info(num - 1, ops + 1));
        }
    }
}
