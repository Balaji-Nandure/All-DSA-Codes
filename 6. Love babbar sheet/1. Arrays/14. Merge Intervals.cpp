// Problem: Merge Overlapping Intervals
// Link (LeetCode 56): https://leetcode.com/problems/merge-intervals/
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/overlapping-intervals--170633/1
// Article: https://www.geeksforgeeks.org/dsa/merging-intervals/
// Difficulty: Medium
// Topic: Array, Sorting, Intervals

/*
Problem Statement:
Given an array of intervals where `intervals[i] = [starti, endi]`, merge all overlapping intervals, 
and return an array of the non-overlapping intervals that cover all the intervals in the input.

Example 1:
Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].

Example 2:
Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.

Constraints:
- 1 <= intervals.length <= 10^5
- intervals[i].length == 2
- 0 <= starti <= endi <= 10^4
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In previous problems, elements were scalar values (single integers).
// - In Problem 14, elements are 2D RANGES / INTERVALS `[start, end]`:
//   * Two dimensions introduce partial ordering (ordering by start vs end).
//   * By sorting by `start`, all intervals that could possibly overlap become ADJACENT in order!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Brute Force O(N^2)
//   - Compare every interval against all other intervals and merge if overlapping: O(N^2). Wastes time.
//
// Approach 2: Sorting by Start Time + Linear Scan - OPTIMAL & CHOSEN
//   - Step 1: Sort all intervals by their `start` time: `intervals[0] <= intervals[1] ...`
//   - Step 2: Initialize `merged` list with the first interval.
//   - Step 3: Iterate through remaining intervals:
//     * Let `last = merged.back()`, `curr = intervals[i]`.
//     * If `curr[0] <= last[1]`: They OVERLAP!
//       Merge them by extending the end: `last[1] = max(last[1], curr[1])`.
//     * Else (`curr[0] > last[1]`): NO overlap!
//       Push `curr` as a new disjoint interval into `merged`.
//   - Complexity: O(N log N) time, O(1) extra space (ignoring output).

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.empty()) return {};

        // Step 1: Sort intervals by start time
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Sorting by start time ensures that any interval that could possibly overlap with
        // an earlier interval MUST appear either next to it or be merged into it!
        sort(intervals.begin(), intervals.end());

        vector<vector<int>> merged;
        merged.push_back(intervals[0]);

        for (int i = 1; i < (int)intervals.size(); i++) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Check if current interval's start <= previous merged interval's end.
            // If true, an overlap exists!
            if (intervals[i][0] <= merged.back()[1]) {
                // Extend the merged interval's end to cover the maximum extent
                merged.back()[1] = max(merged.back()[1], intervals[i][1]);
            } else {
                // Disjoint interval: push as a new independent interval
                merged.push_back(intervals[i]);
            }
        }

        return merged;
    }
};

/*
Time Complexity: O(N log N)
- Sorting the intervals array of size N takes O(N log N).
- Linear pass through the sorted intervals takes O(N).
- Overall Time Complexity: O(N log N).

Space Complexity: O(1) Auxiliary Space
- Ignoring the output array, only O(1) scalar pointers and comparisons are used.

Key Insights:
1. Why `max(merged.back()[1], intervals[i][1])` is necessary:
   - Example: [1, 5] followed by [2, 4].
   - Even though [2, 4] starts after 1, its end (4) is SMALLER than 5!
   - Simply setting `merged.back()[1] = intervals[i][1]` would shrink the interval to [1, 4] (BUG!).
   - Using `max()` correctly keeps the end as 5 -> [1, 5].
*/
