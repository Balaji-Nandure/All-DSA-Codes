// Problem: Minimum Number of Swaps Required to Sort the Array
// Link (GFG): https://www.geeksforgeeks.org/problems/minimum-swaps/1
// Article: https://www.geeksforgeeks.org/dsa/minimum-number-swaps-required-sort-array/
// Difficulty: Medium
// Topic: Sorting, Graph Theory, Permutation Cycle Decomposition

/*
Problem Statement:
Given an array of n distinct elements. Find the minimum number of swaps 
required to sort the array in strictly ascending order.
Note: You can swap ANY two elements in the array (not restricted to adjacent swaps).

Example 1:
Input: nums = [2, 8, 5, 4]
Output: 1
Explanation: Swap 8 and 4 -> [2, 4, 5, 8], which is sorted. Total swaps = 1.

Example 2:
Input: nums = [10, 19, 6, 3, 5]
Output: 2
Explanation:
Swap 10 and 3 -> [3, 19, 6, 10, 5]
Swap 19 and 5 -> [3, 5, 6, 10, 19], which is sorted. Total swaps = 2.

Constraints:
- 1 <= n <= 10^5
- 1 <= nums[i] <= 10^6
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Strings Problem 30 (Minimum Adjacent Swaps for Bracket Balancing):
//   * Swaps were restricted to ADJACENT indices (`swap(i, i+1)`), which took sum of displacement distances.
// - In Problem 17 (Arbitrary Index Swaps):
//   * Any two elements can be swapped regardless of distance in a SINGLE swap!
//   * We model the array as a DIRECTED GRAPH of index mappings:
//     An edge `i -> j` indicates that the element currently at index `i` needs to move to index `j`.
//   * Every permutation decomposes into a collection of DISJOINT CYCLES!
//   * A cycle of length `L` requires EXACTLY `L - 1` swaps to resolve!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Permutation Cycle Decomposition (Optimal & Chosen):
//   - Step 1: Pair each element with its initial index: `pair<int, int> arrPos[i] = {nums[i], i}`.
//   - Step 2: Sort `arrPos` by value:
//       Now, `arrPos[i]` represents which element SHOULD be at index `i` in the sorted array.
//   - Step 3: Maintain boolean array `visited[n] = {false}`.
//   - Step 4: For each index `i` from 0 to `n - 1`:
//       * If `visited[i]` or `arrPos[i].second == i` (already in correct place): skip.
//       * Trace the cycle starting from `i`:
//           `cycleSize = 0; j = i;`
//           `while (!visited[j]):`
//               `visited[j] = true;`
//               `j = arrPos[j].second;`
//               `cycleSize++;`
//       * Add `(cycleSize - 1)` to `totalSwaps`.
//   - Formula: `Total Swaps = Sum(cycle_size - 1) = N - (number of cycles)`.
//   - Complexity: O(N log N) time, O(N) space.
//   - Why this approach: Mathematically provable minimum number of transpositions.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();

        // Pair stores {value, originalIndex}
        vector<pair<int, int>> arrPos(n);
        for (int i = 0; i < n; ++i) {
            arrPos[i] = {nums[i], i};
        }

        // Sort by value to discover where each element belongs in the sorted array
        sort(arrPos.begin(), arrPos.end());

        vector<bool> visited(n, false);
        int totalSwaps = 0;

        for (int i = 0; i < n; ++i) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // If element is already visited or already at its correct sorted position, skip
            if (visited[i] || arrPos[i].second == i) {
                continue;
            }

            // Find the size of the cycle
            int cycleSize = 0;
            int j = i;

            while (!visited[j]) {
                visited[j] = true;
                // Move to the index where the current element was originally located
                j = arrPos[j].second;
                cycleSize++;
            }

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Fundamental Permutation Theorem: A cycle of length L requires exactly (L - 1) swaps.
            if (cycleSize > 1) {
                totalSwaps += (cycleSize - 1);
            }
        }

        return totalSwaps;
    }
};

int main() {
    Solution sol;
    vector<int> nums1 = {2, 8, 5, 4};
    cout << "Min swaps for nums1: " << sol.minSwaps(nums1) << "\n";

    vector<int> nums2 = {10, 19, 6, 3, 5};
    cout << "Min swaps for nums2: " << sol.minSwaps(nums2) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N log N) to sort the pairs, followed by O(N) cycle traversal 
  (each element is visited at most once in the graph).
- Space Complexity: O(N) auxiliary space for `arrPos` and `visited` vector.

Key Takeaways:
- Cycle decomposition in permutation graphs is the definitive technique for arbitrary-position swap minimization.
*/
