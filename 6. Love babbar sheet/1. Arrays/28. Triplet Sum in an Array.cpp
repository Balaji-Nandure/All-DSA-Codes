// Problem: Triplet Sum in Array (3Sum Problem)
// Link (LeetCode 15): https://leetcode.com/problems/3sum/
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/triplet-sum-in-array-1587115621/1
// Article: https://www.geeksforgeeks.org/dsa/find-a-triplet-that-sum-to-a-given-value/
// Difficulty: Medium
// Topic: Array, Two Pointers, Sorting

/*
Problem Statement:
Given an array `arr[]` of integers and an integer `target`. 
Determine if there exists a triplet of distinct elements `(arr[i], arr[j], arr[k])` with `i != j != k`
such that:
    `arr[i] + arr[j] + arr[k] == target`
Return `true` if exists, otherwise `false`.

Also covers LeetCode 15: Find all UNIQUE triplets that sum to 0.

Example 1:
Input: arr = [1, 4, 45, 6, 10, 8], target = 13
Output: true
Explanation: The triplet {1, 4, 8} has sum = 1 + 4 + 8 = 13.

Example 2:
Input: arr = [1, 2, 4, 3, 6, 7], target = 10
Output: true
Explanation: Triplet {1, 2, 7} or {1, 3, 6} sums to 10.

Example 3:
Input: arr = [40, 20, 10, 3, 6, 7], target = 24
Output: false

Constraints:
- 3 <= arr.size() <= 10^4
- -10^5 <= arr[i], target <= 10^5
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 18 (2Sum): We found pairs `x + y = target` in O(N) using a hash map.
// - In Problem 28 (3Sum):
//   * A 3-element combination `x + y + z = target`.
//   * Brute force is O(N^3).
//   * A hash map approach takes O(N^2) time and O(N) space.
//   * By SORTING FIRST, we can reduce 3Sum to N independent Two-Pointer searches in O(N^2) time with O(1) space!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Brute Force O(N^3)
//   - 3 nested loops: O(N^3). Completely infeasible for N = 10^4.
//
// Approach 2: Sorting + Two Pointers (OPTIMAL & CHOSEN)
//   - Step 1: Sort `arr` ascending: O(N log N).
//   - Step 2: Loop index `i` from `0` to `n - 3` (fixing the first number `arr[i]`):
//     * Convert remaining problem to 2Sum: Find a pair in `[i + 1 ... n - 1]` summing to `target - arr[i]`.
//     * Initialize two pointers: `left = i + 1`, `right = n - 1`.
//     * While `left < right`:
//       - `sum = arr[i] + arr[left] + arr[right]`.
//       - If `sum == target`: Triplet found! Return true.
//       - If `sum < target`: We need a larger sum, increment `left++`.
//       - If `sum > target`: We need a smaller sum, decrement `right--`.
//   - Complexity: Exactly O(N^2) time, O(1) auxiliary space!

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // -------------------------------------------------------------------------
    // Method 1: Boolean Existence Check (GFG Style - O(N^2) Time, O(1) Space)
    // -------------------------------------------------------------------------
    bool hasTripletSum(vector<int>& arr, int target) {
        int n = arr.size();
        if (n < 3) return false;

        // Step 1: Sort the array to enable monotonic two-pointer convergence
        sort(arr.begin(), arr.end());

        // Step 2: Fix the first element arr[i]
        for (int i = 0; i < n - 2; i++) {
            int left = i + 1;
            int right = n - 1;

            while (left < right) {
                int sum = arr[i] + arr[left] + arr[right];

                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // In a sorted array, if sum < target, increasing left is guaranteed to
                // increase or maintain the sum. If sum > target, decreasing right decreases sum.
                // This eliminates the need for a 3rd nested loop, pruning O(N^3) down to O(N^2)!
                if (sum == target) {
                    return true;
                } else if (sum < target) {
                    left++;
                } else {
                    right--;
                }
            }
        }

        return false;
    }

    // -------------------------------------------------------------------------
    // Method 2: Return All UNIQUE Triplets Summing to Zero (LeetCode 15)
    // -------------------------------------------------------------------------
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());

        for (int i = 0; i < n - 2; i++) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Skip duplicate values for the first element to prevent identical triplet sets
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            // Early exit: if smallest element > 0, three positive numbers can never sum to 0!
            if (nums[i] > 0) break;

            int left = i + 1;
            int right = n - 1;

            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];

                if (sum == 0) {
                    result.push_back({nums[i], nums[left], nums[right]});

                    // Skip duplicate elements for left and right pointers
                    while (left < right && nums[left] == nums[left + 1]) left++;
                    while (left < right && nums[right] == nums[right - 1]) right--;

                    left++;
                    right--;
                } else if (sum < 0) {
                    left++;
                } else {
                    right--;
                }
            }
        }

        return result;
    }
};

/*
Time Complexity: O(N^2)
- Sorting takes O(N log N).
- Outer loop runs (N - 2) times. Inside, two pointers traverse at most (N - i) elements: O(N).
- Total Time Complexity: O(N log N + N^2) = O(N^2).

Space Complexity: O(1) Auxiliary Space
- Method 1 uses O(1) extra space.
- Method 2 only uses space for returning the output triplets.

Key Insights:
1. Two Pointers over Hash Map for 3Sum:
   - While a hash map solves 2Sum in O(N), for 3Sum, hash map would take O(N^2) time and O(N) space,
     plus messy duplicate de-duplication using sets of vectors.
   - Sorting + Two Pointers achieves O(N^2) time with ZERO extra memory and trivial duplicate skipping!
*/
