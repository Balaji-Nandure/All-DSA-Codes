/*
Problem: Non-overlapping Intervals

GFG: https://www.geeksforgeeks.org/problems/non-overlapping-intervals/1
LeetCode: https://leetcode.com/problems/non-overlapping-intervals/

Description:
Given a 2D array intervals[][], where intervals[i] = [starti, endi]. Return the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.

Note: Two intervals are considered non-overlapping if the end time of one interval is less than or equal to the start time of the next interval.

Examples:

Input: intervals[][] = [[1, 2], [2, 3], [3, 4], [1, 3]]
Output: 1
Explanation: [1, 3] can be removed and the rest of the intervals are non-overlapping.

Input: intervals[][] = [[1, 3], [1, 3], [1, 3]]
Output: 2
Explanation: You need to remove two [1, 3] to make the rest of the intervals non-overlapping.

Input: intervals[][] = [[1, 2], [5, 10], [18, 35], [40, 45]]
Output: 0
Explanation: All intervals are already non-overlapping.

Constraints:
1 ≤ intervals.size() ≤ 10^5
0 ≤ starti < endi ≤ 5*10^4

Approach (Greedy Interval Scheduling):
This is a classic interval scheduling problem where we need to maximize non-overlapping intervals.

Key insight:
- Instead of finding which intervals to remove, find maximum intervals we can keep
- Sort intervals by ending time (greedy choice)
- Keep intervals that don't overlap with previous kept interval
- Answer = total intervals - kept intervals

Algorithm:
1. Sort intervals by ending time ascending
2. Keep track of previous interval's end time
3. For each interval:
   - If current start >= previous end: keep it
   - Else: remove it (increment counter)
4. Return removal count

Time Complexity: O(n log n)
Space Complexity: O(1)

Pattern: Greedy + Interval Scheduling
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
GREEDY INTERVAL SCHEDULING
=====================================================

TC: O(n log n)
SC: O(1)

🔥 GREEDY APPROACH
- Sort intervals by ending time
- Keep intervals that don't overlap
- Count removals for overlapping intervals

🧠 KEY INSIGHT:
To maximize kept intervals:
- Always choose interval with smaller end time
- This leaves maximum space for future intervals
- Classic activity selection problem

🎯 ALGORITHM:
1. Sort intervals by end time ascending
2. Track previous interval's end
3. Keep non-overlapping intervals
4. Count removals for overlaps

⚡ GREEDY LOGIC:
If current.start < previous.end
-> Overlap, remove current
Else
-> No overlap, keep current, update previous.end
*/

class Solution {
public:

    static bool cmp(vector<int>& a,
                    vector<int>& b) {

        return a[1] < b[1];
    }

    // TC: O(n log n)
    // SC: O(1)

    int eraseOverlapIntervals(vector<vector<int>>& intervals) {

        sort(intervals.begin(),
             intervals.end(),
             cmp);

        int removals = 0;

        int prevEnd = intervals[0][1];

        for(int i = 1; i < intervals.size(); i++) {

            int start = intervals[i][0];

            int end = intervals[i][1];

            // Overlapping interval
            if(start < prevEnd) {

                removals++;
            }
            else {

                // Safe to keep
                prevEnd = end;
            }
        }

        return removals;
    }
};


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever problem involves:
    MINIMIZE REMOVALS
    + NON-OVERLAPPING INTERVALS
    + SCHEDULING

Think immediately:
    GREEDY - MAXIMIZE KEPT INTERVALS

-----------------------------------------------------

KEY OBSERVATIONS:

1. Minimizing removals = maximizing kept intervals
2. Sort by end time for optimal greedy choice
3. Smaller end intervals leave more space for future
4. Classic activity selection problem

-----------------------------------------------------

COMMON MISTAKES:

1. Sorting by start time instead of end time
2. Using wrong overlap condition (<= vs <)
3. Forgetting to update prevEnd correctly
4. Not understanding greedy proof

-----------------------------------------------------

SIMILAR PROBLEMS

- Activity selection problem
- Interval scheduling
- Maximum non-overlapping intervals

-----------------------------------------------------

🎯 REUSABLE PATTERN:

Whenever:
- Minimize removals for non-overlapping
- Interval scheduling optimization

Think:
Greedy by Ending Time

Algorithm:
1. Sort by end time
2. Keep non-overlapping intervals
3. Count removals

Overlap condition:
current.start < previous.end
(NOT <= because end == start is allowed)

-----------------------------------------------------
*/
