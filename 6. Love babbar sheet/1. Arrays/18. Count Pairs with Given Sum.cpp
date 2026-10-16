// Problem: Count Pairs with Given Sum (Two Sum Variations)
// Link (LeetCode 1): https://leetcode.com/problems/two-sum/
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/count-pairs-with-given-sum5022/1
// Article: https://www.geeksforgeeks.org/dsa/count-pairs-with-given-sum/
// Difficulty: Easy
// Topic: Array, Hash Map, Two Pointers

/*
Problem Statement:
Given an array of integers `arr[]` and an integer `target`.
Find the total number of pairs `(i, j)` with `i < j` such that:
    `arr[i] + arr[j] == target`

Also covers LeetCode 1 (Return the indices of the two numbers that add up to target).

Example 1:
Input: arr = [1, 5, 7, 1], target = 6
Output: 2
Explanation: Pairs are (1, 5) at indices (0, 1) and (1, 5) at indices (1, 3).

Example 2:
Input: arr = [1, 1, 1, 1], target = 2
Output: 6
Explanation: Any pair of 1s sums to 2. Total pairs = 4 * 3 / 2 = 6.

Example 3:
Input: arr = [10, 12, 10, 15, -1], target = 125
Output: 0

Constraints:
- 1 <= arr.size() <= 10^5
- -10^4 <= arr[i], target <= 10^4
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 2 & 17: We tracked a single minimum / maximum value.
// - In Problem 18:
//   * We are matching COMPLEMENTARY PAIRS: `x + y = target => y = target - x`.
//   * Because multiple instances of the same value can exist, we must use a FREQUENCY MAP
//     to count all combinatorial pairings in a single pass.

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Brute Force O(N^2)
//   - Check all pairs (i, j) with nested loops: O(N^2). TLE for N = 10^5.
//
// Approach 2: Sorting + Two Pointers O(N log N)
//   - Sort the array, use `left` and `right` pointers.
//   - Complicated when there are duplicate elements (requires counting duplicate frequencies at both pointers).
//
// Approach 3: Hash Map Frequency Counter (OPTIMAL & CHOSEN)
//   - Maintain an `unordered_map<int, int> freq`.
//   - As we iterate through each element `x`:
//     * Calculate required complement: `complement = target - x`.
//     * If `complement` has been seen before, add `freq[complement]` to `pairCount`.
//     * Add `x` to `freq`: `freq[x]++`.
//   - Complexity: Exactly O(N) average time in 1 pass, O(N) space.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // -------------------------------------------------------------------------
    // Method 1: Hash Map Frequency Counting (GFG Style - Total Pair Count)
    // -------------------------------------------------------------------------
    int getPairsCount(const vector<int>& arr, int target) {
        unordered_map<int, int> freq;
        int pairCount = 0;

        for (int x : arr) {
            int complement = target - x;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // By checking for complement BEFORE inserting x into freq:
            // 1. We guarantee i < j (only matches with elements seen prior to current index).
            // 2. We prevent an element from matching with itself (e.g. target = 6, x = 3)!
            // 3. All previous occurrences of complement are counted in O(1) time.
            if (freq.find(complement) != freq.end()) {
                pairCount += freq[complement];
            }

            // Register current element into frequency map
            freq[x]++;
        }

        return pairCount;
    }

    // -------------------------------------------------------------------------
    // Method 2: Return Indices of the Single Pair (LeetCode 1 - Two Sum)
    // -------------------------------------------------------------------------
    vector<int> twoSum(const vector<int>& nums, int target) {
        unordered_map<int, int> seen; // value -> index

        for (int i = 0; i < (int)nums.size(); i++) {
            int complement = target - nums[i];

            if (seen.find(complement) != seen.end()) {
                return {seen[complement], i};
            }

            seen[nums[i]] = i;
        }

        return {};
    }
};

/*
Time Complexity: O(N)
- Exactly one linear pass through the array.
- Unordered map insertions and lookups take O(1) on average.
- Overall Time Complexity: O(N).

Space Complexity: O(N) Auxiliary Space
- Hash map stores at most N distinct values in the worst case: O(N).

Key Insights:
1. Online Frequency Accumulation:
   - Doing `pairCount += freq[target - x]` and then `freq[x]++` in the same loop avoids the classic
     two-pass bug of dividing by 2 or subtracting self-matches (`x + x == target`).
*/
