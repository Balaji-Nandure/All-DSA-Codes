/*
 * Problem: All Indices of Occurrence
 *
 * Find all indices where element x occurs in array using recursion.
 * Store all indices in a vector.
 *
 * Time: O(n) - visit each element once
 * Space: O(n) - recursion stack depth is n
 */

#include <iostream>
#include <vector>
using namespace std;

// Find all indices where x occurs
void allIndices(int arr[], int n, int idx, int x, vector<int>& indices) {
    // Base case: reached end of array
    if (idx == n) return;

    // If current element matches x, add its index
    if (arr[idx] == x) {
        indices.push_back(idx);
    }
    // Continue searching in remaining array
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
