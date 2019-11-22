#include <iostream>
#include <unordered_set>
#include <limits>

struct Point {
    int x;
    int y;

    Point(int x, int y): x(x), y(y) {}
};

int main() {
    int n, x_0, y_0;
    std::cin >> n >> x_0 >> y_0;
    
    int shots = 0;
    std::unordered_set<double> slopes;

    for (int i = 0; i < n; i++) {
        int x, y;
        std::cin >> x >> y;

        double slope;
        if (x - x_0 == 0) {
            slope = std::numeric_limits<double>::infinity(); 
        } else {
            slope = ((double)(y - y_0)) / (x - x_0);
        }

        // std::cout << "Slope: " << slope << std::endl;

        if (slopes.find(slope) == slopes.end()) {
            // std::cout << "Firing new shot" << std::endl;
            shots += 1;
            slopes.insert(slope);
        }
    }

    std::cout << shots << std::endl;
}
