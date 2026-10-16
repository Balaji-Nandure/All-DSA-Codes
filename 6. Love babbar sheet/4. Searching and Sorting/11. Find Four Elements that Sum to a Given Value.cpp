// Problem: Find Four Elements that Sum to a Given Value (4Sum)
// Link (GFG): https://www.geeksforgeeks.org/problems/find-all-four-sum-numbers1732/1
// Article: https://www.geeksforgeeks.org/dsa/find-four-numbers-with-sum-equal-to-given-sum/
// Difficulty: Medium / Hard
// Topic: Searching, Two Pointers, Sorting, K-Sum Generalization

/*
Problem Statement:
Given an array `arr` of integers and another number `k`. Find all unique quadruplets 
[arr[a], arr[b], arr[c], arr[d]] such that:
    arr[a] + arr[b] + arr[c] + arr[d] = k
    where a < b < c < d.
Return all unique quadruplets sorted lexicographically.

Example 1:
Input: arr = [0, 0, 2, 1, 1], k = 3
Output: [[0, 0, 1, 2]]

Example 2:
Input: arr = [10, 2, 3, 4, 5, 7, 8], k = 23
Output: [[2, 3, 10, 8], [2, 4, 7, 10], [3, 5, 7, 8]] (sorted quadruplets)

Constraints:
- 1 <= arr.size() <= 1000
- -10^6 <= arr[i] <= 10^6
- -10^9 <= k <= 10^9
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In 2-Sum (Arrays Problem 18):
//   * Two pointers solved the problem in O(N).
// - In 3-Sum (Arrays Problem 28):
//   * One fixed outer loop + Two pointers solved it in O(N^2).
// - In 4-Sum (Problem 11):
//   * We have FOUR elements.
//   * The brute force approach checks O(N^4) quadruplets.
//   * By fixing TWO outer elements (loops `i` and `j`) and running Convergent Two Pointers 
//     on the remaining two, we reduce the complexity to O(N^3)!
//   * Critical interview requirement: ZERO duplicate quadruplets in output without 
//     using an expensive `std::set`!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Sorting + Dual Outer Loops + Convergent Two Pointers (Optimal & Chosen):
//   - Step 1: Sort `arr` in ascending order.
//   - Step 2: Loop `i` from 0 to `n - 4`:
//       * Skip duplicates: `if (i > 0 && arr[i] == arr[i - 1]) continue;`
//   - Step 3: Loop `j` from `i + 1` to `n - 3`:
//       * Skip duplicates: `if (j > i + 1 && arr[j] == arr[j - 1]) continue;`
//   - Step 4: Two pointers `left = j + 1`, `right = n - 1`:
//       * `long long target = (long long)k - arr[i] - arr[j];`
//       * While `left < right`:
//           - `long long sum = arr[left] + arr[right];`
//           - If `sum == target`:
//               Add `[arr[i], arr[j], arr[left], arr[right]]` to result.
//               Skip duplicate values for `left` and `right`.
//               `left++; right--;`
//           - Else if `sum < target`: `left++`.
//           - Else: `right--`.
//   - Complexity: O(N^3) time, O(1) auxiliary space!
//   - Why this approach: Standard K-Sum reduction with in-place duplicate avoidance.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& arr, int k) {
        vector<vector<int>> quadruplets;
        int n = arr.size();
        if (n < 4) return quadruplets;

        // Step 1: Sort array to enable two-pointer convergence and duplicate pruning
        sort(arr.begin(), arr.end());

        for (int i = 0; i < n - 3; ++i) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Prune duplicate outer values to prevent identical quadruplets
            if (i > 0 && arr[i] == arr[i - 1]) continue;

            for (int j = i + 1; j < n - 2; ++j) {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Prune duplicate second-level values
                if (j > i + 1 && arr[j] == arr[j - 1]) continue;

                // Cast to long long to prevent integer overflow when calculating target
                long long remainingTarget = (long long)k - (long long)arr[i] - (long long)arr[j];

                int left = j + 1;
                int right = n - 1;

                while (left < right) {
                    long long currentSum = arr[left] + arr[right];

                    if (currentSum == remainingTarget) {
                        quadruplets.push_back({arr[i], arr[j], arr[left], arr[right]});

                        // Skip identical elements for left and right pointers
                        while (left < right && arr[left] == arr[left + 1]) left++;
                        while (left < right && arr[right] == arr[right - 1]) right--;

                        left++;
                        right--;
                    } else if (currentSum < remainingTarget) {
                        left++; // Need larger sum
                    } else {
                        right--; // Need smaller sum
                    }
                }
            }
        }

        return quadruplets;
    }
};

int main() {
    Solution sol;
    vector<int> arr = {10, 2, 3, 4, 5, 7, 8};
    int k = 23;

    vector<vector<int>> res = sol.fourSum(arr, k);
    cout << "Quadruplets summing to " << k << ":\n";
    for (const auto& quad : res) {
        cout << "[ ";
        for (int x : quad) cout << x << " ";
        cout << "]\n";
    }

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N^3).
  * Two nested loops take O(N^2).
  * Convergent two-pointer traversal takes O(N) inside.
  * Total time is strictly O(N^3).
- Space Complexity: O(1) auxiliary space (excluding memory for returned result).

Key Takeaways:
- Any K-Sum problem can be reduced to (K - 1)-Sum, eventually ending in O(N^(K-1)) 
  via 2-pointer convergence.
*/
