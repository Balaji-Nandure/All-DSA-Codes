/*
Problem: Insert Interval

GFG: https://www.geeksforgeeks.org/problems/insert-interval/

Description:
Geek has an array of non-overlapping intervals intervals[][] where intervals[i] = [starti, endi] represent the start and end of the ith event and intervals is sorted in ascending order by starti. He wants to add a new interval newInterval[] = [newStart, newEnd] where newStart and newEnd represent the start and end of this interval.
Help Geek to insert newInterval into intervals such that intervals is still sorted in ascending order by starti and intervals still does not have any overlapping intervals (merge overlapping intervals if necessary).

Examples:

Input: intervals[][] = [[1, 3], [4, 5], [6, 7], [8, 10]], newInterval[] = [5, 6]
Output: [[1, 3], [4, 7], [8, 10]]
Explanation: The newInterval [5, 6] overlaps with [4, 5] and [6, 7]. So, they are merged into one interval [4, 7].

Input: intervals[][] = [[1, 2], [3, 5], [6, 7], [8, 10], [12, 16]], newInterval[] = [4, 9]
Output: [[1, 2], [3, 10], [12, 16]]
Explanation: The new interval [4, 9] overlaps with [3, 5], [6, 7] and [8, 10]. So, they are merged into one interval [3, 10].

Constraints:
1 ≤ intervals.size() ≤ 10^5
0 ≤ starti ≤ endi ≤ 10^9
0 ≤ newStart ≤ newEnd ≤ 10^9

Approach (Three-Phase Insertion):
This is a classic interval merging problem where we need to insert a new interval into sorted, non-overlapping intervals.

Key insight:
- Intervals are already sorted by start time
- We need to merge overlapping intervals and maintain sorted order
- Process in three phases: before, overlapping, after

Algorithm:
1. Add all intervals that end before newInterval starts
2. Merge all intervals that overlap with newInterval
3. Add all remaining intervals that start after newInterval ends
4. Return merged result

Time Complexity: O(n)
Space Complexity: O(n)

Pattern: Interval Merging + Three-Phase Processing
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
THREE-PHASE INSERTION
=====================================================

TC: O(n)
SC: O(n)

🔥 THREE-PHASE APPROACH
- Phase 1: Add intervals ending before newInterval
- Phase 2: Merge overlapping intervals with newInterval
- Phase 3: Add remaining intervals starting after newInterval

🧠 KEY INSIGHT:
Since intervals are sorted by start:
1. Non-overlapping intervals before newInterval come first
2. Overlapping intervals come in middle
3. Non-overlapping intervals after newInterval come last

🎯 ALGORITHM:
1. Add intervals where end < newStart
2. Merge intervals where start <= newEnd
3. Add remaining intervals
*/

class Solution {
public:

    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        
        vector<vector<int>> result;
        int i = 0, n = intervals.size();
        
        int newStart = newInterval[0];
        int newEnd = newInterval[1];
        
        // Phase 1: Add all intervals that end BEFORE newInterval starts
        while (i < n && intervals[i][1] < newStart) {
            result.push_back(intervals[i]);
            i++;
        }
        
        // Phase 2: Merge all intervals that OVERLAP with newInterval
        while (i < n && intervals[i][0] <= newEnd) {
            
            // Merge overlapping intervals
            newStart = min(newStart, intervals[i][0]);
            newEnd = max(newEnd, intervals[i][1]);
            i++;
        }
        
        // Add the merged interval
        result.push_back({newStart, newEnd});
        
        // Phase 3: Add all remaining intervals that start AFTER newInterval ends
        while (i < n) {
            result.push_back(intervals[i]);
            i++;
        }
        
        return result;
    }
};


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever problem involves:
    INSERTING into SORTED intervals

Think immediately:
    THREE-PHASE PROCESSING

-----------------------------------------------------

KEY OBSERVATIONS:

Since intervals are sorted:
1. Non-overlapping before newInterval
2. Overlapping in middle  
3. Non-overlapping after newInterval

-----------------------------------------------------

COMMON MISTAKES:

1. Not handling all three phases
2. Incorrect overlap condition
3. Forgetting to merge newInterval itself
4. Not maintaining sorted order

-----------------------------------------------------

SIMILAR PROBLEMS

- Merge Intervals
- Insert Interval
- Non-overlapping Intervals
- Interval List Intersection

-----------------------------------------------------
*/
