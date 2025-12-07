/*
 * Problem: Print All Permutations of Array or String
 * 
 * Given an array or string, print all possible permutations.
 * 
 * Example 1:
 * Input: arr = [1, 2, 3]
 * Output: 
 * [1,2,3] [1,3,2] [2,1,3] [2,3,1] [3,1,2] [3,2,1]
 * 
 * Example 2:
 * Input: str = "ABC"
 * Output:
 * ABC ACB BAC BCA CAB CBA
 */

#include <bits/stdc++.h>
using namespace std;


// METHOD 1: Swap Method (for both array and string)
// Hypothesis: At each step, fix one position and swap it with all possible remaining elements, 
// generating all permutations by recursion.
//  On reaching the end, record the permutation.

void permute_swap(int ind, vector<int>& arr, vector<vector<int>>& result) {
    if (ind == arr.size()) {
        result.push_back(arr);
        return;
    }
    for (int i = ind; i < arr.size(); i++) {
        swap(arr[ind], arr[i]);
        permute_swap(ind + 1, arr, result);
        swap(arr[ind], arr[i]);
    }
}

// METHOD 2: Using next_permutation (STL method for reference)

vector<vector<int>> permute_stl(vector<int>& arr) {
    vector<vector<int>> result;
    sort(arr.begin(), arr.end()); // sort first
    
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
