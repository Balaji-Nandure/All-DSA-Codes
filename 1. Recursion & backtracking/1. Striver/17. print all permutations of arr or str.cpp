/*
 * Problem: Print All Permutations of Array or String
 * 
 * LeetCode 46: Permutations
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/permutations-of-a-given-string/0
 *
 * Generate all possible permutations of an array or string.
 * 
 * Example: arr = [1, 2, 3]
 * Output: [1,2,3] [1,3,2] [2,1,3] [2,3,1] [3,1,2] [3,2,1]
 *
 * Time: O(n! * n) - n! permutations, each copied in O(n)
 * Space: O(n) - recursion stack depth
 */

#include <bits/stdc++.h>
using namespace std;

// Method 1: Swap-based approach
// Fix position 'ind', swap with all remaining positions, recurse
void permute_swap(int ind, vector<int>& arr, vector<vector<int>>& result) {
    // Base case: fixed all positions, add current permutation
    if (ind == arr.size()) {
        result.push_back(arr);
        return;
    }
    // Try each element at position 'ind' by swapping
    for (int i = ind; i < arr.size(); i++) {
        // Swap arr[ind] with arr[i] to try arr[i] at position ind
        swap(arr[ind], arr[i]);
        // Recurse to fix next position
        permute_swap(ind + 1, arr, result);
        // Backtrack: restore original order
        swap(arr[ind], arr[i]);
    }
}

// Method 2: Using STL next_permutation (for reference)
vector<vector<int>> permute_stl(vector<int>& arr) {
    vector<vector<int>> result;
    sort(arr.begin(), arr.end()); // Must sort first for next_permutation
    
    // Generate all permutations using STL
    do {
        result.push_back(arr);
    } while (next_permutation(arr.begin(), arr.end()));
    
    return result;
}

// MAIN FUNCTION

int main() {
    // Test with array
    cout << "=== Testing with Array ===\n";
    vector<int> arr = {1, 2, 3};
    int n = arr.size();

    cout << "Input: arr = [";
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]\n\n";

    cout << "Using Swap Method:\n";
    vector<vector<int>> res1;
    vector<int> arr1 = arr; // copy for swap method
    permute_swap(0, arr1, res1);
    for (auto& perm : res1) {
        cout << "[";
        for (int i = 0; i < (int)perm.size(); i++) {
            cout << perm[i];
            if (i < (int)perm.size() - 1) cout << ",";
        }
        cout << "] ";
    }
    cout << "\n\n";

    cout << "Using STL next_permutation:\n";
    vector<int> arr3 = arr; // copy for STL method
    vector<vector<int>> res3 = permute_stl(arr3);
    for (auto& perm : res3) {
        cout << "[";
        for (int i = 0; i < (int)perm.size(); i++) {
            cout << perm[i];
            if (i < (int)perm.size() - 1) cout << ",";
        }
        cout << "] ";
    }
    cout << "\n\n";

    // Test with string
    // NOTE: other string permutation methods were removed, so omit their tests.

    return 0;
}
