/*
    Problem Name: Complete Binary Tree Traversal with Array Input
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given an integer array arr[] representing the nodes of a Complete Binary Tree in level order
    traversal, return the nodes at each level in sorted ascending order as a 2D array.
    The i-th row of the 2D array should contain the sorted values of the i-th level.

    Examples:
    Input: arr[] = [7, 6, 5, 4, 3, 2, 1]
    Output: [[7], [5, 6], [1, 2, 3, 4]]
    Explanation:
    - Level 0: [7] -> sorted: [7]
    - Level 1: [6, 5] -> sorted: [5, 6]
    - Level 2: [4, 3, 2, 1] -> sorted: [1, 2, 3, 4]

    Input: arr[] = [7, 16, 1, 4, 13]
    Output: [[7], [1, 16], [4, 13]]
    Explanation:
    - Level 0: [7] -> sorted: [7]
    - Level 1: [16, 1] -> sorted: [1, 16]
    - Level 2: [4, 13] -> sorted: [4, 13]

    Constraints:
    1 <= arr.size() <= 10^4
    1 <= arr[i] <= 10^9

    Expected Complexities:
    Time Complexity: O(N log N), where N is the size of arr[]. We sort elements level by level.
    Space Complexity: O(N), for the output 2D vector.

    Love Babbar Style Approach:
    Level-wise Slicing & Independent Sorting:

    1. INTUITION:
       - In a Complete Binary Tree represented in level order array `arr[]`:
         * Level 0 contains at most 1 element (`arr[0]`).
         * Level 1 contains at most 2 elements (`arr[1 ... 2]`).
         * Level 2 contains at most 4 elements (`arr[3 ... 6]`).
         * Level `L` contains at most $2^L$ elements starting at index `idx`.
       - We iterate through `arr[]` keeping track of the level capacity `count` (starting at 1, doubling each level).
       - Slice the elements of the current level from `arr[idx ... min(N, idx + count) - 1]`.
       - Sort the sliced level vector and append to `ans`.
       - Advance `idx` by `count` and double `count *= 2`.

    2. ALGORITHM:
       - `int n = arr.size();`
       - `int idx = 0, count = 1;`
       - `vector<vector<int>> ans;`
       - While (`idx < n`):
         * `int endIdx = min(n, idx + count);`
         * `vector<int> level(arr.begin() + idx, arr.begin() + endIdx);`
         * `sort(level.begin(), level.end());`
         * `ans.push_back(level);`
         * `idx = endIdx;`
         * `count *= 2;`
       - Return `ans`.

    Dry Run:
    arr[] = [7, 16, 1, 4, 13], n = 5
    - idx = 0, count = 1: endIdx = min(5, 1) = 1. level = [7] -> ans = [[7]]. idx = 1, count = 2.
    - idx = 1, count = 2: endIdx = min(5, 3) = 3. level = [16, 1] -> sorted [1, 16] -> ans = [[7], [1, 16]]. idx = 3, count = 4.
    - idx = 3, count = 4: endIdx = min(5, 7) = 5. level = [4, 13] -> sorted [4, 13] -> ans = [[7], [1, 16], [4, 13]]. idx = 5, count = 8.
    - Loop ends.

    Result: [[7], [1, 16], [4, 13]] ✓
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // GFG Signature - Level-wise slicing & sorting
    vector<vector<int>> levelOrder(vector<int>& arr) {
        int n = arr.size();
        int idx = 0;
        int count = 1; // Maximum nodes at level 0

        vector<vector<int>> ans;

        while (idx < n) {
            int endIdx = min(n, idx + count);

            // Slice nodes belonging to the current level
            vector<int> level(arr.begin() + idx, arr.begin() + endIdx);

            // Sort level node values in ascending order
            sort(level.begin(), level.end());

            ans.push_back(level);

            // Move index to next level and double capacity for binary tree
            idx = endIdx;
            count *= 2;
        }

        return ans;
    }
};

int main() {
    Solution ob;

    // Example 1:
    // arr[] = [7, 6, 5, 4, 3, 2, 1]
    // Expected Output: [[7], [5, 6], [1, 2, 3, 4]]
    vector<int> arr1 = {7, 6, 5, 4, 3, 2, 1};
    vector<vector<int>> res1 = ob.levelOrder(arr1);

    cout << "Example 1 Sorted Levels:\n";
    for (const auto& lvl : res1) {
        cout << "[ ";
        for (int val : lvl) cout << val << " ";
        cout << "]\n";
    }
    cout << "\n";

    // Example 2:
    // arr[] = [7, 16, 1, 4, 13]
    // Expected Output: [[7], [1, 16], [4, 13]]
    vector<int> arr2 = {7, 16, 1, 4, 13};
    vector<vector<int>> res2 = ob.levelOrder(arr2);

    cout << "Example 2 Sorted Levels:\n";
    for (const auto& lvl : res2) {
        cout << "[ ";
        for (int val : lvl) cout << val << " ";
        cout << "]\n";
    }

    return 0;
}
