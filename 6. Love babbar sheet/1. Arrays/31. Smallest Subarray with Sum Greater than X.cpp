// Problem: Smallest Subarray with Sum Greater than a Given Value
// Link (LeetCode 209): https://leetcode.com/problems/minimum-size-subarray-sum/
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/smallest-subarray-with-sum-greater-than-x5651/1
// Article: https://www.geeksforgeeks.org/dsa/minimum-length-subarray-sum-greater-given-value/
// Difficulty: Medium / Easy
// Topic: Array, Sliding Window, Two Pointers

/*
Problem Statement:
Given an array of positive integers `arr[]` and a positive integer `x`.
Find the minimum length of a contiguous subarray whose sum is strictly greater than `x` (i.e. sum > x).
If no such subarray exists, return 0.

(Note: On LeetCode 209, the condition is sum >= target. The logic is identical).

Example 1:
Input: x = 51, arr = [1, 4, 45, 6, 0, 19]
Output: 3
Explanation: Subarray [4, 45, 6] has sum = 55 > 51, length = 3.

Example 2:
Input: x = 100, arr = [1, 10, 5, 2, 7]
Output: 0
Explanation: Total array sum = 25, which is not greater than 100.

Example 3:
Input: x = 7, arr = [2, 3, 1, 2, 4, 3]
Output: 2
Explanation: Subarray [4, 3] has sum = 7, length = 2 (for >= condition).

Constraints:
- 1 <= arr.size() <= 10^5
- 1 <= arr[i] <= 10^9
- 1 <= x <= 10^9
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 30: The sliding window size was FIXED to `m`.
// - In Problem 31:
//   * The window size is DYNAMIC / VARIABLE (caterpillar crawl).
//   * Because all numbers are strictly positive, expanding the window monotonically INCREASES the sum,
//     and shrinking the window monotonically DECREASES the sum!
//   * This monotonic property enables a linear O(N) two-pointer sliding window.

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Brute Force O(N^2)
//   - Check all subarrays (i, j): O(N^2). TLE for N = 10^5.
//
// Approach 2: Sliding Window / Two Pointers (OPTIMAL & CHOSEN)
//   - Pointers `left = 0`, `right = 0`.
//   - Running accumulator: `currentSum = 0`.
//   - Expansion Phase: Expand `right` from 0 to n - 1, adding `arr[right]` to `currentSum`.
//   - Contraction Phase: Whenever `currentSum > x`:
//     * Record length: `minLen = min(minLen, right - left + 1)`.
//     * Shrink window from the left: `currentSum -= arr[left]`, `left++`.
//   - Why strictly O(N): Both `left` and `right` advance at most N times. Total iterations <= 2N.
//   - Complexity: Exactly O(N) time, O(1) space!

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // -------------------------------------------------------------------------
    // Method 1: Sliding Window for Sum > X (GFG Specification)
    // -------------------------------------------------------------------------
    int smallestSubWithSum(int x, vector<int>& arr) {
        int n = arr.size();
        int left = 0;
        long long currentSum = 0;
        int minLen = INT_MAX;

        for (int right = 0; right < n; right++) {
            currentSum += arr[right];

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Once the window sum exceeds x, we greedily shrink it from the left
            // as much as possible while maintaining currentSum > x!
            // Each contraction tests if a shorter prefix still satisfies the condition.
            while (currentSum > x && left <= right) {
                minLen = min(minLen, right - left + 1);
                currentSum -= arr[left];
                left++;
            }
        }

        return (minLen == INT_MAX) ? 0 : minLen;
    }

    // -------------------------------------------------------------------------
    // Method 2: Sliding Window for Sum >= Target (LeetCode 209 Specification)
    // -------------------------------------------------------------------------
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int left = 0;
        long long currentSum = 0;
        int minLen = INT_MAX;

        for (int right = 0; right < n; right++) {
            currentSum += nums[right];

            while (currentSum >= target) {
                minLen = min(minLen, right - left + 1);
                currentSum -= nums[left];
                left++;
            }
        }

        return (minLen == INT_MAX) ? 0 : minLen;
    }
};

/*
Time Complexity: O(N)
- The `right` pointer increments from 0 to N - 1 (N steps).
- The `left` pointer increments at most N times across the entire execution.
- Total pointer movements = 2 * N = O(N) amortized linear time.

Space Complexity: O(1) Auxiliary Space
- Pure scalar variable tracking (`left`, `right`, `currentSum`, `minLen`).

Key Insights:
1. Positivity Requirement for Sliding Window:
   - This O(N) sliding window relies on all numbers being positive (`arr[i] > 0`).
   - If negative numbers were allowed, shrinking from the left might INCREASE the sum,
     destroying monotonicity (requiring a Prefix Sum + Monotonic Deque or Hash Map in that case).
*/
