#include <iostream>
#include <vector>
using namespace std;

// Recursive function to find all indices where x occurs in arr
void allIndices(int arr[], int n, int idx, int x, vector<int>& indices) {
    if (idx == n) return;

    if (arr[idx] == x) {
        indices.push_back(idx);
    }
    allIndices(arr, n, idx + 1, x, indices);
}

int main() {
    int arr[] = {3, 7, 1, 7, 7, 5, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 7;

    vector<int> indices;
    allIndices(arr, n, 0, x, indices);

    if (indices.size() == 0) {
        cout << "Not found" << endl;
    } else {
        for (int i : indices) {
            cout << i << " ";
        }
        cout << endl;
    }
    return 0;
}
