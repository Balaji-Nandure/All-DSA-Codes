vector<vector<int>> mergeIntervals(vector<vector<int>>& intervals) {
    /*
    Problem:
    Merge all overlapping intervals.

    Approach:
    1. Sort intervals based on starting time.
    2. Initialize result with the first interval.
    3. Traverse remaining intervals:
       - If current.start <= last.end → overlap exists:
         merge by updating last.end = max(last.end, current.end)
       - Else:
         push current interval to result.
    4. Result contains all merged non-overlapping intervals.

    Time: O(n log n)
    Space: O(n) (for output)
    */

    if (intervals.empty()) return {};

    // Step 1: sort by start time
    sort(intervals.begin(), intervals.end());

    vector<vector<int>> result;
    result.push_back(intervals[0]);

    // Step 2: merge overlapping intervals
    for (int i = 1; i < intervals.size(); i++) {
        if (intervals[i][0] <= result.back()[1]) {
            result.back()[1] = max(result.back()[1], intervals[i][1]);
        } else {
            result.push_back(intervals[i]);
        }
    }

    return result;
}

/*
GeeksforGeeks:
https://practice.geeksforgeeks.org/problems/overlapping-intervals/1

LeetCode:
https://leetcode.com/problems/merge-intervals/
*/
