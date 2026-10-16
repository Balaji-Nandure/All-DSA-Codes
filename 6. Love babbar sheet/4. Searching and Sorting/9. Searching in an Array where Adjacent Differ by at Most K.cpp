// Problem: Searching in an Array Where Adjacent Differ by at Most K
// Link (GFG): https://www.geeksforgeeks.org/problems/searching-in-an-array-where-adjacent-differ-by-at-most-k0456/1
// Article: https://www.geeksforgeeks.org/dsa/searching-array-adjacent-differ-k/
// Difficulty: Easy
// Topic: Searching, Greedy Jump, Mathematical Bound Skip

/*
Problem Statement:
A step array is an array of integers where each element has a difference of 
AT MOST `k` with its immediate neighbor (i.e. `|arr[i] - arr[i-1]| <= k`).
Given a key `x` and step size `k`, find the index of the FIRST occurrence of `x` in the array.
If `x` is not present, return -1.

Example 1:
Input: arr = [4, 5, 6, 7, 6], k = 1, x = 6
Output: 2
Explanation: First occurrence of 6 is at index 2.

Example 2:
Input: arr = [20, 40, 50, 70, 70, 60], k = 20, x = 60
Output: 5

Constraints:
- 1 <= arr.size() <= 10^5
- 1 <= k <= 100
- 1 <= arr[i], x <= 10^6
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Standard Linear Search:
//   * We check elements one by one (`i++`), which takes exactly N steps in the worst case.
// - In Step Array Search (|arr[i] - arr[i-1]| <= k):
//   * The maximum possible rate of change per index is bounded by `k`.
//   * If `arr[i] != x`, the difference between current element and target is `|arr[i] - x|`.
//   * Since each step can change the value by at most `k`, the target `x` CANNOT POSSIBLY 
//     occur in fewer than `|arr[i] - x| / k` steps!
//   * Therefore, instead of `i++`, we can safely JUMP forward by `max(1, |arr[i] - x| / k)`!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Variable Jump Search (Optimal & Chosen):
//   - Start at `i = 0`.
//   - While `i < n`:
//       * If `arr[i] == x`: Return `i` (first match found).
//       * Compute jump distance: `jump = abs(arr[i] - x) / k`.
//       * To guarantee forward progress even if `abs(arr[i] - x) < k`, take `max(1, jump)`.
//       * Advance `i += max(1, jump)`.
//   - Return -1 if loop ends.
//   - Complexity: Best/Average O(N / K) sub-linear, Worst case O(N), Space O(1).
//   - Why this approach: Exploits the maximum-rate-of-change Lipschitz condition.

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
public:
    int search(vector<int>& arr, int n, int x, int k) {
        int i = 0;

        while (i < n) {
            // Target found
            if (arr[i] == x) {
                return i;
            }

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Mathematical Jump Invariant: Since adjacent elements differ by at most k,
            // the target x is guaranteed to be at least |arr[i] - x| / k indices away!
            // max(1, ...) ensures we always advance by at least 1 index.
            int jump = max(1, abs(arr[i] - x) / k);
            i += jump;
        }

        return -1; // Not found
    }
};

int main() {
    Solution sol;
    vector<int> arr1 = {4, 5, 6, 7, 6};
    int k1 = 1, x1 = 6;
    cout << "Index of " << x1 << " in arr1: " 
         << sol.search(arr1, arr1.size(), x1, k1) << "\n";

    vector<int> arr2 = {20, 40, 50, 70, 70, 60};
    int k2 = 20, x2 = 60;
    cout << "Index of " << x2 << " in arr2: " 
         << sol.search(arr2, arr2.size(), x2, k2) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity:
  * Best / Average Case: O(N / K). When values differ significantly from target, large jumps skip elements.
  * Worst Case: O(N).
- Space Complexity: O(1) auxiliary space.

Key Takeaways:
- Lipschitz continuity / bounded step differences allow provably safe multi-step skipping
  in unsorted sequences.
*/
