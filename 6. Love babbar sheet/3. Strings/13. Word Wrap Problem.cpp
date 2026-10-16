// Problem: Word Wrap Problem [VERY IMP]
// Link (GFG): https://www.geeksforgeeks.org/problems/word-wrap1646/1
// Article: https://www.geeksforgeeks.org/dsa/word-wrap-problem-dp-19/
// Difficulty: Hard
// Topic: String, Dynamic Programming, Partition DP

/*
Problem Statement:
Given an array `nums[]` of size `n`, where `nums[i]` denotes the number of characters 
in the i-th word. You are also given an integer `k` which is the maximum limit of characters 
that can be accommodated in a single line.
A single space must be placed between two consecutive words on the same line.

The total spaces occupied by words from index `i` to `j` is:
    occupied = sum(nums[i .. j]) + (j - i) (where (j - i) accounts for the single space between words).

If words from index `i` to `j` are placed on a line:
- The line is valid if `occupied <= k`.
- The extra spaces remaining at the end of the line are `extra = k - occupied`.
- The cost of the line is defined as `extra * extra` (squared penalty).
- SPECIAL RULE: The LAST line has a cost of 0 (extra spaces on the final line incur no penalty).

Find the minimum total cost to wrap all words into lines.

Example 1:
Input: nums = [3, 2, 2, 5], k = 6
Output: 10
Explanation:
Line 1: Word 0 and Word 1 (length 3 + 1 space + 2 = 6). Extra spaces = 0. Cost = 0^2 = 0.
Line 2: Word 2 (length 2). Extra spaces = 6 - 2 = 4. Cost = 4^2 = 16. (Wait, let's test):
Optimal arrangement:
Line 1: Word 0 (length 3). Extra spaces = 6 - 3 = 3. Cost = 3^2 = 9.
Line 2: Word 1 and Word 2 (2 + 1 space + 2 = 5). Extra spaces = 6 - 5 = 1. Cost = 1^2 = 1.
Line 3: Word 3 (5). Extra spaces = 6 - 5 = 1. Last line cost = 0.
Total cost = 9 + 1 + 0 = 10.

Example 2:
Input: nums = [3, 2, 2], k = 4
Output: 5
Explanation:
Line 1: [3] -> extra = 1, cost = 1^2 = 1.
Line 2: [2] -> extra = 2, cost = 2^2 = 4.
Line 3: [2] -> last line, cost = 0.
Total cost = 1 + 4 = 5.

Constraints:
- 1 <= nums.length <= 1000
- 1 <= nums[i] <= 1000
- max(nums[i]) <= k <= 2000
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Split Binary String (Problem 12):
//   * A greedy local decision at the earliest balance point was globally optimal.
// - In Word Wrap Problem:
//   * A GREEDY choice (packing as many words as possible on the current line) FAILS!
//     Packing too many words now can leave a tiny fragment on the next line, causing an 
//     enormous squared penalty (e.g., 4^2 = 16 vs 2^2 + 2^2 = 8).
//   * Furthermore, the last line has a cost of 0, creating an asymmetric boundary condition.
//   * Therefore, we must use Dynamic Programming (Partition DP) to explore all valid line breaks.

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: 1D Suffix Dynamic Programming (Optimal & Chosen)
//   - Let `dp[i]` be the minimum cost to arrange words from index `i` to `n - 1`.
//   - Base case: `dp[n] = 0` (no words left, cost is 0).
//   - For each start index `i` from `n - 1` down to 0:
//     * Try placing words from `i` up to `j` on the current line (while `totalLen <= k`).
//     * If `j == n - 1` (this line contains all remaining words up to the end):
//         This becomes the LAST LINE -> line cost is 0!
//         `cost = 0 + dp[j + 1]` = 0.
//     * If `j < n - 1` (interior line):
//         `extra = k - totalLen`
//         `cost = extra * extra + dp[j + 1]`
//     * `dp[i] = min(dp[i], cost)`.
//   - Return `dp[0]`.
//   - Complexity: O(N * k) worst case O(N^2) time, O(N) auxiliary space.
//   - Why this approach: Eliminates recursive re-computation and models the last-line 0 cost 
//     perfectly.

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int solveWordWrap(vector<int>& nums, int k) {
        int n = nums.size();

        // dp[i] stores the minimum cost of word wrapping starting from word index i to n-1
        vector<int> dp(n + 1, 0);

        // Fill from right to left (bottom-up)
        for (int i = n - 1; i >= 0; --i) {
            int currentLength = 0;
            int minCost = INT_MAX;

            for (int j = i; j < n; ++j) {
                // Word length + 1 space if not the first word on this line
                currentLength += nums[j] + (j > i ? 1 : 0);

                // If line exceeds capacity k, cannot fit any more words on this line
                if (currentLength > k) {
                    break;
                }

                int lineCost = 0;

                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Critical Rule: If words reach the end (j == n - 1), this is the FINAL line.
                // The cost of remaining spaces on the last line is strictly 0!
                // For intermediate lines (j < n - 1), penalty is the square of the unused spaces.
                if (j == n - 1) {
                    lineCost = 0;
                } else {
                    int extraSpaces = k - currentLength;
                    lineCost = extraSpaces * extraSpaces + dp[j + 1];
                }

                minCost = min(minCost, lineCost);
            }

            dp[i] = minCost;
        }

        return dp[0];
    }
};

int main() {
    Solution sol;
    vector<int> nums1 = {3, 2, 2, 5};
    int k1 = 6;
    cout << "Word wrap minimum cost (nums1): " << sol.solveWordWrap(nums1, k1) << "\n";

    vector<int> nums2 = {3, 2, 2};
    int k2 = 4;
    cout << "Word wrap minimum cost (nums2): " << sol.solveWordWrap(nums2, k2) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N * min(N, k)).
  * Outer loop runs N times.
  * Inner loop terminates as soon as `currentLength > k` (at most k iterations).
  * For N = 1000, runs in a couple of milliseconds.
- Space Complexity: O(N) auxiliary space for the `dp` vector.

Key Takeaways:
- Non-linear penalty functions (like squaring) completely break greedy strategies;
  Dynamic Programming is strictly required.
*/
