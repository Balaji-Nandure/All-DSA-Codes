// Problem: Kadane's Algorithm - Maximum Subarray Sum & Circular Subarray Sum Variant
// Link (LeetCode 53): https://leetcode.com/problems/maximum-subarray/
// Link (LeetCode 918 Circular): https://leetcode.com/problems/maximum-sum-circular-subarray/
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/kadanes-algorithm-1587115620/1
// Difficulty: Medium
// Topic: Array, Dynamic Programming, Kadane's Algorithm

/*
Problem Statement:
Given an array `arr[]` of `n` integers. 
1. Standard Kadane: Find the maximum sum of a contiguous subarray.
2. Circular Kadane (LeetCode 918): Find the maximum sum of a non-empty subarray where the subarray 
   can wrap around the end to the beginning (circular array).

Example 1 (Standard):
Input: arr = [2, 3, -8, 7, -1, 2, 3]
Output: 11
Explanation: Subarray [7, -1, 2, 3] has the largest sum 11.

Example 2 (Circular Variant):
Input: arr = [5, -3, 5]
Output: 10
Explanation: Circular subarray [5] (tail) + [5] (head) = 10.

Example 3 (All Negatives):
Input: arr = [-3, -2, -3]
Output: -2

Constraints:
- 1 <= arr.size() <= 10^5
- -10^4 <= arr[i] <= 10^4
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - File 8 covered the fundamental Kadane algorithm and linear index tracking.
// - File 13 extends Kadane's paradigm to CIRCULAR SUBARRAYS:
//   * A circular subarray that wraps around is equivalent to: (Total Array Sum) - (Minimum Subarray Sum)!
//   * Hence, finding the max circular subarray requires running Kadane's for MAXIMUM and MINIMUM simultaneously.

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Standard Kadane's:
//   - Keep running sum `currSum`. If `currSum < 0`, reset to 0. Update `maxSum = max(maxSum, currSum)`.
//   - Complexity: O(N) time, O(1) space.
//
// Circular Kadane's:
//   - Case 1: Max subarray is non-circular (contained completely within [0 ... n - 1]).
//     * Directly given by standard Kadane: `maxKadane`.
//   - Case 2: Max subarray wraps around the ends.
//     * In this case, the elements NOT included in the circular sum form a contiguous MINIMUM subarray!
//     * Therefore: `maxCircular = totalSum - minKadane`.
//   - Edge Case (All numbers negative):
//     * If all numbers are negative, `totalSum == minKadane`, making `totalSum - minKadane = 0` (empty array).
//     * But a subarray must be non-empty! So if `maxKadane < 0`, return `maxKadane`.
//   - Result: `max(maxKadane, totalSum - minKadane)`.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // -------------------------------------------------------------------------
    // Method 1: Standard Kadane's Algorithm (O(N) Time, O(1) Space)
    // -------------------------------------------------------------------------
    long long maxSubarraySum(const vector<int>& arr) {
        long long maxSum = arr[0];
        long long currSum = 0;

        for (int x : arr) {
            currSum += x;
            maxSum = max(maxSum, currSum);
            if (currSum < 0) {
                currSum = 0;
            }
        }
        return maxSum;
    }

    // -------------------------------------------------------------------------
    // Method 2: Circular Maximum Subarray Sum (LeetCode 918 - Combined Dual Kadane)
    // -------------------------------------------------------------------------
    int maxSubarraySumCircular(const vector<int>& nums) {
        int totalSum = 0;
        int currMax = 0, maxKadane = nums[0];
        int currMin = 0, minKadane = nums[0];

        for (int x : nums) {
            totalSum += x;

            // 1. Standard Kadane for Maximum Subarray
            currMax += x;
            maxKadane = max(maxKadane, currMax);
            if (currMax < 0) currMax = 0;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // 2. Inverted Kadane for Minimum Subarray:
            // If currMin becomes positive, carrying it forward only INCREASES future minimums,
            // so we discard it and reset currMin = 0!
            currMin += x;
            minKadane = min(minKadane, currMin);
            if (currMin > 0) currMin = 0;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Special Edge Case: If all elements are negative, maxKadane is negative (the largest single negative).
        // In that case, totalSum == minKadane, which would give totalSum - minKadane = 0 (an empty subarray).
        // Since subarrays must be non-empty, we MUST return maxKadane!
        if (maxKadane < 0) {
            return maxKadane;
        }

        // Otherwise, maximum is either non-circular or circular
        return max(maxKadane, totalSum - minKadane);
    }
};

/*
Time Complexity: O(N)
- Single pass through the array to simultaneously calculate:
  1. totalSum
  2. maxKadane
  3. minKadane
- Linear time O(N).

Space Complexity: O(1) Auxiliary Space
- Uses only 5 scalar integer accumulators.

Key Insights:
1. Dual Kadane Inversion:
   - Maximizing circular wrap-around = Minimizing non-circular interior.
   - Dual Kadane calculates both bounds simultaneously in a single pass of O(N) time.
2. The All-Negative Trap:
   - Forgetting `if (maxKadane < 0) return maxKadane;` is the classic pitfall on LeetCode 918.
*/
