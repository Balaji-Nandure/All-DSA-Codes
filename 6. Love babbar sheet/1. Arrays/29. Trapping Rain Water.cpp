// Problem: Trapping Rain Water
// Link (LeetCode 42): https://leetcode.com/problems/trapping-rain-water/
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/trapping-rain-water-1587115621/1
// Article: https://www.geeksforgeeks.org/dsa/trapping-rain-water/
// Difficulty: Hard
// Topic: Array, Two Pointers, Monotonic Stack, Dynamic Programming

/*
Problem Statement:
Given an array `arr[]` of `n` non-negative integers representing an elevation map where the width 
of each bar is 1, compute how much water it is able to trap after raining.

Example 1:
Input: arr = [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]
Output: 6
Explanation: Water trapped at:
- index 2: min(1, 3) - 0 = 1
- index 4: min(2, 3) - 1 = 1
- index 5: min(2, 3) - 0 = 2
- index 6: min(2, 3) - 1 = 1
- index 9: min(2, 2) - 1 = 1
Total = 1 + 1 + 2 + 1 + 1 = 6 units.

Example 2:
Input: arr = [4, 2, 0, 3, 2, 5]
Output: 9

Example 3:
Input: arr = [3, 0, 2, 0, 4]
Output: 7

Constraints:
- 1 <= arr.size() <= 10^5
- 0 <= arr[i] <= 10^5
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 8 (Kadane): Subarray sum accumulated directly from values.
// - In Problem 29 (Trapping Rain Water):
//   * Water trapped at any bar `i` depends on the BOTTLENECK OF TWO SEPARATE BOUNDARIES:
//     `water[i] = max(0, min(max_left_boundary, max_right_boundary) - height[i])`.
//   * Because the limiting factor is the SMALLER of the two boundaries, two pointers
//     can resolve water volume from the smaller boundary inward!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Prefix Max and Suffix Max Arrays (O(N) Time, O(N) Space)
//   - Precalculate `leftMax[i]` from left and `rightMax[i]` from right.
//   - For each bar, add `min(leftMax[i], rightMax[i]) - height[i]`.
//   - Good, but uses 2 extra arrays of size N.
//
// Approach 2: Two Pointers (OPTIMAL & CHOSEN)
//   - Pointers `left = 0`, `right = n - 1`.
//   - Variables `leftMax = 0`, `rightMax = 0`.
//   - Crucial Deduction:
//     * If `height[left] <= height[right]`:
//       We know for sure there is a bar on the right side with height >= height[left].
//       Therefore, `leftMax` is the true limiting boundary!
//       If `height[left] >= leftMax`: update `leftMax = height[left]`.
//       Else: water trapped above `left` is `leftMax - height[left]`.
//       Advance `left++`.
//     * Else (`height[left] > height[right]`):
//       Similarly, `rightMax` is the true limiting boundary!
//       If `height[right] >= rightMax`: update `rightMax = height[right]`.
//       Else: water trapped above `right` is `rightMax - height[right]`.
//       Advance `right--`.
//   - Complexity: Exactly O(N) time in a single pass, O(1) auxiliary space!

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // -------------------------------------------------------------------------
    // Method 1: Two Pointers (O(N) Time, O(1) Auxiliary Space - Optimal)
    // -------------------------------------------------------------------------
    long long trappingWater(vector<int>& arr) {
        int n = arr.size();
        if (n <= 2) return 0; // At least 3 bars needed to form a container

        int left = 0, right = n - 1;
        long long leftMax = 0, rightMax = 0;
        long long totalWater = 0;

        while (left <= right) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // The water trapped is bounded by min(leftMax, rightMax).
            // When arr[left] <= arr[right], we know there exists some bar on the right
            // that is at least as tall as arr[left].
            // Thus, rightMax cannot be the bottleneck; leftMax is the definitive limiting wall!
            if (arr[left] <= arr[right]) {
                if (arr[left] >= leftMax) {
                    leftMax = arr[left]; // New boundary wall, cannot trap water
                } else {
                    totalWater += (leftMax - arr[left]); // Water trapped above arr[left]
                }
                left++;
            } else {
                if (arr[right] >= rightMax) {
                    rightMax = arr[right]; // New boundary wall, cannot trap water
                } else {
                    totalWater += (rightMax - arr[right]); // Water trapped above arr[right]
                }
                right--;
            }
        }

        return totalWater;
    }

    // -------------------------------------------------------------------------
    // Method 2: Prefix and Suffix Max Arrays (O(N) Time, O(N) Space - Intuitive)
    // -------------------------------------------------------------------------
    long long trappingWaterPrefixSuffix(vector<int>& arr) {
        int n = arr.size();
        if (n <= 2) return 0;

        vector<int> leftMax(n);
        vector<int> rightMax(n);

        leftMax[0] = arr[0];
        for (int i = 1; i < n; i++) {
            leftMax[i] = max(leftMax[i - 1], arr[i]);
        }

        rightMax[n - 1] = arr[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            rightMax[i] = max(rightMax[i + 1], arr[i]);
        }

        long long totalWater = 0;
        for (int i = 0; i < n; i++) {
            totalWater += max(0, min(leftMax[i], rightMax[i]) - arr[i]);
        }

        return totalWater;
    }
};

/*
Time Complexity: O(N)
- Exactly one linear pass through the array. 
- Left and right pointers converge in N steps: O(N).

Space Complexity: O(1) Auxiliary Space
- Pure two-pointer traversal with 3 scalar variables (`leftMax`, `rightMax`, `totalWater`).

Key Insights:
1. Why We Don't Need the Exact `rightMax` when `arr[left] <= arr[right]`:
   - It doesn't matter if `rightMax` is 5 or 500. As long as `rightMax >= leftMax`,
     `min(leftMax, rightMax)` evaluates to `leftMax`!
   - This brilliant realization eliminates the need for the second prefix/suffix array.
*/
