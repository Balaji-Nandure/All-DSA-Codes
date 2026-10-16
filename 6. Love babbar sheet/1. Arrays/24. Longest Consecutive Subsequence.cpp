// Problem: Longest Consecutive Subsequence
// Link (LeetCode 128): https://leetcode.com/problems/longest-consecutive-sequence/
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/longest-consecutive-subsequence2449/1
// Article: https://www.geeksforgeeks.org/dsa/longest-consecutive-subsequence/
// Difficulty: Medium
// Topic: Array, Hash Table, Union-Find

/*
Problem Statement:
Given an unsorted array of integers `nums`, return the length of the longest consecutive elements sequence.
The sequence elements need NOT be contiguous in the original array (they can be a subsequence).

You must write an algorithm that runs in O(N) time.

Example 1:
Input: nums = [100, 4, 200, 1, 3, 2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Its length is 4.

Example 2:
Input: nums = [0, 3, 7, 2, 5, 8, 4, 6, 0, 1]
Output: 9
Explanation: Sequence is [0, 1, 2, 3, 4, 5, 6, 7, 8], length is 9.

Constraints:
- 0 <= nums.length <= 10^5
- -10^9 <= nums[i] <= 10^9
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 8 & 23: We searched for CONTIGUOUS SUBARRAYS (indices must be adjacent).
// - In Problem 24:
//   * We are searching for CONSECUTIVE SUBSEQUENCES (values must differ by 1, e.g. x, x+1, x+2...).
//   * Elements can appear at completely arbitrary indices anywhere in the array.
//   * Sorting takes O(N log N), but the problem strictly mandates an O(N) solution!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Sorting O(N log N)
//   - Sort the array, remove duplicates, count consecutive steps: O(N log N).
//   - Why Rejected: Violates the explicit O(N) requirement of the problem.
//
// Approach 2: Hash Set with "Sequence Starter" Detection (OPTIMAL & CHOSEN)
//   - Insert all elements into an `unordered_set<int>` (takes O(N) time).
//   - Iterate through each number `x` in the set:
//     * Check if `x - 1` is in the set:
//       - If `x - 1` exists: `x` CANNOT be the start of a sequence (it is part of an ongoing sequence).
//         SKIP IT immediately!
//       - If `x - 1` does NOT exist: `x` IS THE FIRST ELEMENT OF A CONSECUTIVE SEQUENCE!
//         Start counting: `x + 1`, `x + 2`, `x + 3` ... until the sequence breaks.
//   - Why is this strictly O(N) and not O(N^2)?
//     * Every element is visited in the outer loop: N times.
//     * An element is visited in the inner `while` loop ONLY IF it is part of a sequence whose starter
//       is being evaluated. Each element is part of at most ONE sequence!
//     * Total operations = N (outer) + N (inner) = 2N = O(N)!

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.empty()) return 0;

        // Insert all numbers into hash set for O(1) membership lookups
        unordered_set<int> numSet(nums.begin(), nums.end());
        int longestStreak = 0;

        for (int x : numSet) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Check if (x - 1) is present in the set.
            // If (x - 1) exists, x is NOT the start of the sequence. We do NOTHING.
            // If (x - 1) does NOT exist, x is GUARANTEED to be the absolute minimum of its sequence!
            // This single 'if' check prevents re-scanning streaks and guarantees O(N) overall time!
            if (numSet.find(x - 1) == numSet.end()) {
                int currentNum = x;
                int currentStreak = 1;

                // Count forward as long as consecutive numbers exist
                while (numSet.find(currentNum + 1) != numSet.end()) {
                    currentNum++;
                    currentStreak++;
                }

                longestStreak = max(longestStreak, currentStreak);
            }
        }

        return longestStreak;
    }
};

/*
Time Complexity: O(N)
- Inserting N elements into `unordered_set`: O(N) average time.
- Outer loop runs over at most N unique elements: O(N).
- Inner `while` loop only triggers for "sequence starter" elements (those without `x - 1`).
- Since each number in the array belongs to exactly one consecutive streak, each number is visited
  at most twice (once in outer loop, once in inner loop).
- Overall Time Complexity: O(2N) = O(N) linear time!

Space Complexity: O(N) Auxiliary Space
- Unordered set storing up to N distinct elements: O(N).

Key Insights:
1. Why `x - 1` Check is the Magic Key:
   - Without `if (numSet.find(x - 1) == numSet.end())`:
     Given array [1, 2, 3, 4, 5], you would scan from 1 (len 5), then from 2 (len 4), then 3 (len 3)...
     taking 5 + 4 + 3 + 2 + 1 = O(N^2) time!
   - WITH the check: Only 1 qualifies as a starter. 2, 3, 4, and 5 are immediately skipped in O(1)!
*/
