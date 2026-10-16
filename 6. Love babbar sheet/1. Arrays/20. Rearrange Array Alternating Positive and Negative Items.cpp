// Problem: Rearrange Array in Alternating Positive & Negative Items (and Rearrange Array Alternately)
// Link (Article): https://www.geeksforgeeks.org/dsa/rearrange-array-alternating-positive-negative-items-o1-extra-space/
// Link (LeetCode 2149): https://leetcode.com/problems/rearrange-array-elements-by-sign/
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/-rearrange-array-alternately-1587115620/1
// Difficulty: Medium / Hard
// Topic: Array, Two Pointers, In-place Rearrangement, Mathematical Encoding

/*
Problem Statement:
Variation 1 (Alternating Positive & Negative with Order Preserved - LeetCode 2149):
Given an array `nums` of even length consisting of an equal number of positive and negative integers.
Rearrange the array such that every consecutive pair has alternating signs, starting with positive:
    [pos0, neg0, pos1, neg1, pos2, neg2, ...]
Preserve the relative order of positive and negative integers.

Variation 2 (GFG In-place with O(1) Extra Space):
Same as above, but with O(1) extra space. (Uses right-rotation on out-of-place elements).

Variation 3 (GFG Practice "Rearrange Array Alternately"):
Given a sorted array of positive integers, rearrange it alternately:
    [max1, min1, max2, min2, max3, min3, ...]
Must be done in O(N) time and O(1) auxiliary space (using modulo encoding!).

Example 1 (Alternating Signs):
Input: nums = [3, 1, -2, -5, 2, -4]
Output: [3, -2, 1, -5, 2, -4]

Example 2 (Max-Min Alternately):
Input: arr = [1, 2, 3, 4, 5, 6]
Output: [6, 1, 5, 2, 4, 3]

Constraints:
- 1 <= nums.length <= 10^5
- -10^5 <= nums[i] <= 10^5
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 5: We segregated negatives and positives into two separate contiguous halves.
// - In Problem 20:
//   * Elements cannot just be segregated; they must be INTERLEAVED in an alternating pattern!
//   * Even indices (0, 2, 4...) get positives, odd indices (1, 3, 5...) get negatives.
//   * In Variation 3, we encode TWO numbers at a SINGLE index using modular arithmetic!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1 (Alternating Signs - LeetCode 2149 / Optimal O(N) Time & Space):
//   - Initialize `posIdx = 0` (even slots) and `negIdx = 1` (odd slots).
//   - Iterate through `nums`:
//     * If `nums[i] > 0`: place at `ans[posIdx]`, `posIdx += 2`.
//     * If `nums[i] < 0`: place at `ans[negIdx]`, `negIdx += 2`.
//   - Complexity: O(N) time in a single pass, O(N) space.
//
// Approach 2 (Max-Min Alternately - GFG O(1) Space Modular Encoding):
//   - We need to place `arr[max_idx]` at even positions and `arr[min_idx]` at odd positions.
//   - Mathematical Trick: Any index `i` can store BOTH the old and new value using:
//       `arr[i] = arr[i] + (newValue % M) * M`
//     where `M > max_element_in_array`.
//   - To retrieve old value: `arr[i] % M`.
//   - To retrieve new value: `arr[i] / M`.
//   - Complexity: O(N) time, O(1) space!

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // -------------------------------------------------------------------------
    // Method 1: Alternating Signs by Index (LeetCode 2149 - O(N) Time, O(N) Space)
    // -------------------------------------------------------------------------
    vector<int> rearrangeArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);
        int posIdx = 0; // Even positions: 0, 2, 4, ...
        int negIdx = 1; // Odd positions:  1, 3, 5, ...

        for (int x : nums) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Rather than separating into two arrays and then zipping them,
            // we place each number into its exact final alternating index directly!
            if (x > 0) {
                ans[posIdx] = x;
                posIdx += 2;
            } else {
                ans[negIdx] = x;
                negIdx += 2;
            }
        }

        return ans;
    }

    // -------------------------------------------------------------------------
    // Method 2: Rearrange Array Alternately [Max, Min, 2nd Max, ...] (GFG Practice)
    // In-Place O(N) Time, O(1) Space using Division/Modulo Encoding Trick
    // -------------------------------------------------------------------------
    void rearrangeMaxMinInPlace(vector<long long>& arr) {
        int n = arr.size();
        int maxIdx = n - 1;
        int minIdx = 0;

        // M must be strictly greater than any element in the array
        long long maxElem = arr[n - 1] + 1;

        for (int i = 0; i < n; i++) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Formula: arr[i] = arr[i] + (newValue % maxElem) * maxElem.
            // Even indices get max elements, odd indices get min elements.
            // Using % maxElem extracts the ORIGINAL unmodified value of arr[maxIdx] / arr[minIdx].
            if (i % 2 == 0) {
                arr[i] += (arr[maxIdx] % maxElem) * maxElem;
                maxIdx--;
            } else {
                arr[i] += (arr[minIdx] % maxElem) * maxElem;
                minIdx++;
            }
        }

        // Decode the new values by dividing by maxElem
        for (int i = 0; i < n; i++) {
            arr[i] /= maxElem;
        }
    }
};

/*
Time Complexity:
- Method 1 (Alternating Signs): O(N) single pass.
- Method 2 (Max-Min Encoding): O(N) — two linear passes (one to encode, one to decode).

Space Complexity:
- Method 1: O(N) space for the resulting array.
- Method 2: O(1) Auxiliary Space — strictly in-place modification using arithmetic encoding!

Key Insights:
1. The Modulo Encoding Super-Power:
   - When restricted to O(1) space on positive integers, encoding two values into one:
     `stored = old_val + new_val * M` allows accessing `old_val` via `% M` and `new_val` via `/ M`.
   - This trick is universally applicable across array in-place transformation problems.
*/
