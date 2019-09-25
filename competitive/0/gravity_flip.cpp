#include <iostream> 
#include <vector> 
#include <algorithm>

using namespace std;
  
int main() { 
    int size;
    cin >> size;
    int nums[size];

    for (int i = 0; i < size; i++) {
        cin >> nums[i];
    }

    sort(nums, nums + size);

    for (int i = 0; i < size; i++) {
        cout << to_string(nums[i]) + " ";
    }

    cout << endl;
} 
