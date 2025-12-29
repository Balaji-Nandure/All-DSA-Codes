bool isOverlapping(vector<vector<int>>& intervals) {
    /*
    Problem:
    Check if any two intervals overlap.

    Approach:
    1. Sort all intervals by their starting time.
    2. Traverse intervals from left to right.
    3. For consecutive intervals:
       - If current.start < previous.end → overlap exists.
    4. If traversal completes with no overlap → return false.

    Time: O(n log n)
    Space: O(1)
    */

    if (intervals.size() < 2) return false;

    // Sort intervals by start time
    sort(intervals.begin(), intervals.end());

    // Check overlap with previous interval
    for (int i = 1; i < intervals.size(); i++) {
        if (intervals[i][0] <= intervals[i - 1][1]) {
            return true;
        }
    }

    return false;
}

/*
GeeksforGeeks:
https://practice.geeksforgeeks.org/problems/overlapping-intervals/0

LeetCode:
https://leetcode.com/problems/meeting-rooms/
*/
