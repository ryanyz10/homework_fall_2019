#include <iostream>

int bus(int a, int b, int f, int k) {
    int location = 0;
    int refuels = 0;
    int tank = b;
    int journeys = 0;

    while (journeys < k) {
        if (location == a) {
            if (tank >= a + f) {
                tank -= a;
                journeys += 1;
                location = 0;
            } else if (tank >= a - f) {
                if (journeys + 1 == k && tank >= a) {
                    journeys += 1;
                    tank -= a;
                    location = 0;
                } else {
                    if (b >= f) {
                        refuels += 1;
                        location = 0;
                        tank = b - f;
                        journeys += 1;
                    } else {
                        return -1;
                    }
                }
            } else {
                return -1;
            }
        } else {
            if (tank >= 2*a - f) {
                location = a;
                tank -= a;
                journeys += 1;
            } else if (tank >= f) {
                if (journeys + 1 == k && tank >= a) {
                    journeys += 1;
                    tank -= a;
                    location = a;
                } else {
                    if (b >= a - f) {
                        refuels += 1;
                        location = a;
                        tank = b - a + f;
                        journeys += 1;
                    } else {
                        return -1;
                    }
                }
            } else {
                return -1;
            }
        }

    }


    return refuels;
}

int main() {
    int a, b, f, k;
    std::cin >> a >> b >> f >> k;
    std::cout << bus(a, b, f, k) << std::endl;
}
