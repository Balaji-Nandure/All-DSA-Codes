/*
    Problem Name: Count Greater on Right Queries
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given an array arr[] and Q queries of indices. For each query indices[i], determine
    the count of elements in arr that are strictly greater than arr[indices[i]] to its right
    (after the position indices[i]).

    Examples:
    Input: arr[] = [3, 4, 2, 7, 5, 8, 10, 6], indices[] = [0, 5]
    Output: [6, 1]
    Explanation:
    - Index 0 (val 3): Greater elements to the right are 4, 7, 5, 8, 10, 6 (count = 6).
    - Index 5 (val 8): Greater element to the right is 10 (count = 1).

    Input: arr[] = [1, 2, 3, 4, 1], indices[] = [0, 3]
    Output: [3, 0]

    Constraints:
    1 <= n <= 10^4
    1 <= arr[i] <= 10^5
    1 <= queries <= 100
    0 <= indices[i] <= n - 1

    Expected Complexities:
    Time Complexity: O(Q * N), where Q is the number of queries (Q <= 100) and N is the size of arr (N <= 10^4).
                     Overall operations <= 10^6, easily passes within time limits.
    Space Complexity: O(1) auxiliary space (excluding output array).

    Love Babbar Style Approach:
    Direct Simulation per Query:

    1. INTUITION:
       - Since Q <= 100 is very small, for each query index `idx = indices[i]`:
         * We iterate from `j = idx + 1` to `n - 1`.
         * Count elements `arr[j]` where `arr[j] > arr[idx]`.
         * Append the count to `ans`.

    2. ALGORITHM:
       - For each `idx` in `indices`:
         * `cnt = 0`
         * Loop `j` from `idx + 1` to `arr.size() - 1`:
           - `if (arr[j] > arr[idx]) cnt++;`
         * `ans.push_back(cnt);`
       - Return `ans`.

    Dry Run:
    arr[] = [3, 4, 2, 7, 5, 8, 10, 6], indices[] = [0, 5]

    Query 1 (indices[0] = 0, arr[0] = 3):
    - Compare with arr[1..7]: 4(>3), 2(<=3), 7(>3), 5(>3), 8(>3), 10(>3), 6(>3)
    - Count = 6.

    Query 2 (indices[1] = 5, arr[5] = 8):
    - Compare with arr[6..7]: 10(>8), 6(<=8)
    - Count = 1.

    Output: [6, 1] ✓
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // GFG Signature
    vector<int> countGreater(vector<int>& arr, vector<int>& indices) {
        vector<int> ans;

        for (int i : indices) {
            int cnt = 0;
            for (int j = i + 1; j < arr.size(); j++) {
                if (arr[j] > arr[i]) {
                    cnt++;
                }
            }
            ans.push_back(cnt);
        }

        return ans;
    }
};

int main() {
    Solution ob;

    // Example 1:
    // arr[] = [3, 4, 2, 7, 5, 8, 10, 6], indices[] = [0, 5]
    // Expected Output: 6 1
    vector<int> arr1 = {3, 4, 2, 7, 5, 8, 10, 6};
    vector<int> indices1 = {0, 5};

    vector<int> res1 = ob.countGreater(arr1, indices1);
    cout << "Example 1 Output: ";
    for (int val : res1) cout << val << " ";
    cout << "\n";

    // Example 2:
    // arr[] = [1, 2, 3, 4, 1], indices[] = [0, 3]
    // Expected Output: 3 0
    vector<int> arr2 = {1, 2, 3, 4, 1};
    vector<int> indices2 = {0, 3};

    vector<int> res2 = ob.countGreater(arr2, indices2);
    cout << "Example 2 Output: ";
    for (int val : res2) cout << val << " ";
    cout << "\n";

    return 0;
}
