// Problem: Largest Sum Contiguous Subarray (Kadane's Algorithm)
// Link (LeetCode 53): https://leetcode.com/problems/maximum-subarray/
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/kadanes-algorithm-1587115620/1
// Article: https://www.geeksforgeeks.org/dsa/largest-sum-contiguous-subarray/
// Difficulty: Medium
// Topic: Array, Dynamic Programming, Kadane's Algorithm

/*
Problem Statement:
Given an integer array `arr[]`, find the contiguous subarray (containing at least one number) 
which has the largest sum and return its sum.

Also print/return the starting and ending indices of this maximum subarray (Common Follow-up).

Example 1:
Input: arr = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
Output: 6
Explanation: The subarray [4, -1, 2, 1] has the largest sum = 6.

Example 2:
Input: arr = [1]
Output: 1

Example 3 (All Negative Numbers):
Input: arr = [-5, -2, -8, -1]
Output: -1
Explanation: Subarray [-1] has the largest sum = -1.

Constraints:
- 1 <= arr.size() <= 10^5
- -10^4 <= arr[i] <= 10^4
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - Problems 1-7 dealt with individual element comparisons, partitions, and rotations.
// - Problem 8 introduces the concept of a CONTIGUOUS SUBARRAY optimization:
//   * There are O(N^2) total contiguous subarrays.
//   * A brute force check takes O(N^3) or O(N^2) time.
//   * Kadane's algorithm leverages Dynamic Programming to solve it in a single pass O(N) time with O(1) space!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Brute Force / Cubic O(N^3)
//   - Try all pairs (i, j) and compute sum from i to j: O(N^3). Wastes massive time.
//
// Approach 2: Prefix Sums / Quadratic O(N^2)
//   - Fix start index i, expand j from i to n - 1 keeping a running sum: O(N^2). TLE for N = 10^5.
//
// Approach 3: Kadane's Algorithm (Linear DP in O(N)) - OPTIMAL & CHOSEN
//   - Key Dynamic Programming Principle:
//     * At each index `i`, we have two choices:
//       1. Extend the previous subarray sum: `currentSum + arr[i]`
//       2. Start a fresh new subarray at `arr[i]`: `arr[i]`
//     * In simple terms: If `currentSum < 0`, carrying it forward only hurts any subsequent sum!
//       Therefore, whenever `currentSum < 0`, reset `currentSum = 0`.
//   - Edge Case (All Negative Elements):
//     * Initialize `maxSum = arr[0]` (or `INT_MIN`), NOT `0`! 
//     * If all numbers are negative, the answer is the largest single negative number.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // -------------------------------------------------------------------------
    // Method 1: Kadane's Algorithm for Maximum Subarray Sum (O(N) Time, O(1) Space)
    // -------------------------------------------------------------------------
    long long maxSubarraySum(const vector<int>& arr) {
        long long maxSum = arr[0];
        long long currentSum = 0;

        for (int x : arr) {
            currentSum += x;

            // Update global maximum if current running sum is greater
            if (currentSum > maxSum) {
                maxSum = currentSum;
            }

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // If currentSum becomes negative, it cannot contribute positively to any
            // future subarray! Carrying forward a negative sum will strictly REDUCE
            // the sum of whatever comes next.
            // Hence, we discard the current subarray and reset currentSum = 0!
            if (currentSum < 0) {
                currentSum = 0;
            }
        }

        return maxSum;
    }

    // -------------------------------------------------------------------------
    // Method 2: Kadane's with Subarray Index Tracking (Interview Follow-Up)
    // -------------------------------------------------------------------------
    tuple<long long, int, int> maxSubarrayWithIndices(const vector<int>& arr) {
        long long maxSum = arr[0];
        long long currentSum = 0;

        int startIdx = 0, endIdx = 0;
        int tempStart = 0;

        for (int i = 0; i < (int)arr.size(); i++) {
            currentSum += arr[i];

            if (currentSum > maxSum) {
                maxSum = currentSum;
                startIdx = tempStart; // Lock in the start of this optimal subarray
                endIdx = i;          // Current index is the end
            }

            if (currentSum < 0) {
                currentSum = 0;
                tempStart = i + 1; // Potential start of the next subarray
            }
        }

        return {maxSum, startIdx, endIdx};
    }
};

/*
Time Complexity: O(N)
- Exactly one linear pass through the array. 
- Performs constant number of operations at each element: O(N).

Space Complexity: O(1) Auxiliary Space
- Requires only scalar tracking variables (`maxSum`, `currentSum`). Zero heap/stack buffers.

Key Insights:
1. Negative Sum Reset Order:
   - Always update `maxSum` BEFORE checking `if (currentSum < 0) currentSum = 0`.
   - If an array contains all negative numbers (e.g. [-5, -2, -8]), updating `maxSum` first
     ensures we capture `-2` before resetting `currentSum` to 0.
2. Subarray Recovery:
   - Tracking `tempStart = i + 1` whenever `currentSum < 0` enables printing the exact subarray
     `[startIdx ... endIdx]` with zero extra runtime cost.
*/
