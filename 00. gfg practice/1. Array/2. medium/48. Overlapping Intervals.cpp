/*
================================================================================
PROBLEM: Overlapping Intervals (GFG - Medium)
================================================================================

Given an array of intervals arr[][] where arr[i] = [start_i, end_i].
Merge all overlapping intervals and return the result.

Examples:
1. arr = [[1, 3], [2, 4], [6, 8], [9, 10]]
   Output: [[1, 4], [6, 8], [9, 10]]
   Merge [1,3] and [2,4] → [1,4]

2. arr = [[6, 8], [1, 9], [2, 4], [4, 7]]
   Output: [[1, 9]]
   All intervals overlap with [1,9]

3. arr = [[1, 4], [4, 5]]
   Output: [[1, 5]]
   Overlapping at 4 → merge

Constraints:
- 1 ≤ arr.size() ≤ 10^5
- 0 ≤ start_i ≤ end_i ≤ 10^6

Companies: Amazon, Microsoft, Google, Nutanix, Zoho

================================================================================
APPROACH: GREEDY + SORTING
Time: O(n log n) | Space: O(1) (excluding output)
================================================================================

HOW IT WORKS:

Step 1: Sort intervals by start time
- If starts are equal, order doesn't matter
- Sorting ensures we process intervals in order

Step 2: Iterate through sorted intervals
- Initialize result with first interval
- For each new interval:
  - If it overlaps with last interval in result → merge them
  - Else → add it as new interval

Overlap check:
- Two intervals [a, b] and [c, d] overlap if: c <= b
- Merge: [a, max(b, d)]

WHY IT WORKS:
- After sorting by start, all overlapping intervals appear consecutively or nested
- Greedy merge: always merge, never split → optimal solution
- Time: dominated by sorting O(n log n)


DRY RUN: arr = [[1, 3], [2, 4], [6, 8], [9, 10]]

Step 1: Sort by start
- Already sorted: [[1, 3], [2, 4], [6, 8], [9, 10]]

Step 2: Process intervals
- result = []
- Add [1, 3] → result = [[1, 3]]

- Check [2, 4]: 2 <= 3? YES → merge
  - New interval = [1, max(3, 4)] = [1, 4]
  - result = [[1, 4]]

- Check [6, 8]: 6 <= 4? NO → add new
  - result = [[1, 4], [6, 8]]

- Check [9, 10]: 9 <= 8? NO → add new
  - result = [[1, 4], [6, 8], [9, 10]]

Output: [[1, 4], [6, 8], [9, 10]] ✓

================================================================================
EDGE CASES:
================================================================================

1. No overlapping:
   arr = [[1, 2], [3, 4], [5, 6]]
   Output: [[1, 2], [3, 4], [5, 6]]
   Each interval separate ✓

2. All overlapping:
   arr = [[1, 10], [2, 5], [3, 7]]
   Output: [[1, 10]]
   All merge into one ✓

3. One interval contains another:
   arr = [[1, 5], [2, 3]]
   Output: [[1, 5]]
   [2,3] contained in [1,5] ✓

4. Adjacent intervals:
   arr = [[1, 2], [2, 3]]
   Output: [[1, 3]]
   They touch at 2 → merge ✓

5. Single interval:
   arr = [[1, 5]]
   Output: [[1, 5]]
   Single interval → return it ✓

6. Nested intervals:
   arr = [[1, 10], [2, 3], [4, 5], [6, 7]]
   Output: [[1, 10]]
   All nested in first ✓

================================================================================
TEST CASES:
================================================================================

Test 1: arr = [[1, 3], [2, 4], [6, 8], [9, 10]]
Expected: [[1, 4], [6, 8], [9, 10]]
Result: ✓

Test 2: arr = [[6, 8], [1, 9], [2, 4], [4, 7]]
Expected: [[1, 9]]
Result: ✓

Test 3: arr = [[1, 4], [4, 5]]
Expected: [[1, 5]]
Result: ✓

Test 4: arr = [[1, 2], [3, 4], [5, 6]]
Expected: [[1, 2], [3, 4], [5, 6]]
Result: ✓

Test 5: arr = [[1, 5], [0, 0]]
Expected: [[0, 0], [1, 5]]
Result: ✓

================================================================================
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
  public:
    /*
    HOW IT WORKS:
    1. Sort intervals by start time (natural ordering of pairs)
    2. Iterate through sorted intervals
    3. For each interval:
       - If overlaps with last merged → extend the last one
       - Else → add as new interval

    COMPLEXITY:
    - Time: O(n log n) for sorting + O(n) for merging = O(n log n)
    - Space: O(1) if we don't count output array
    */
    
    vector<vector<int>> mergeIntervals(vector<vector<int>>& intervals) {
        int n = intervals.size();
        
        if (n == 0) return {};
        
        // Step 1: Sort by start time
        sort(intervals.begin(), intervals.end());
        
        // Step 2: Merge overlapping intervals
        vector<vector<int>> result;
        result.push_back(intervals[0]);
        
        for (int i = 1; i < n; i++) {
            int lastEnd = result.back()[1];
            int currStart = intervals[i][0];
            int currEnd = intervals[i][1];
            
            // Check if overlapping: currStart <= lastEnd
            if (currStart <= lastEnd) {
                // Merge: extend the end of last interval
                result.back()[1] = max(lastEnd, currEnd);
            } else {
                // Non-overlapping: add new interval
                result.push_back(intervals[i]);
            }
        }
        
        return result;
    }
};


/*
================================================================================
DRY RUN - DETAILED:
================================================================================

Example 1: intervals = [[1, 3], [2, 4], [6, 8], [9, 10]]

After sort: [[1, 3], [2, 4], [6, 8], [9, 10]] (already sorted)

result = [[1, 3]]

i=1: curr = [2, 4]
- lastEnd = 3, currStart = 2, currEnd = 4
- 2 <= 3? YES → overlap
- Merge: result.back()[1] = max(3, 4) = 4
- result = [[1, 4]]

i=2: curr = [6, 8]
- lastEnd = 4, currStart = 6, currEnd = 8
- 6 <= 4? NO → no overlap
- Add new: result.push_back([6, 8])
- result = [[1, 4], [6, 8]]

i=3: curr = [9, 10]
- lastEnd = 8, currStart = 9, currEnd = 10
- 9 <= 8? NO → no overlap
- Add new: result.push_back([9, 10])
- result = [[1, 4], [6, 8], [9, 10]]

Output: [[1, 4], [6, 8], [9, 10]] ✓

--------------------------------------------------

Example 2: intervals = [[6, 8], [1, 9], [2, 4], [4, 7]]

After sort: [[1, 9], [2, 4], [4, 7], [6, 8]]

result = [[1, 9]]

i=1: curr = [2, 4]
- lastEnd = 9, currStart = 2, currEnd = 4
- 2 <= 9? YES → overlap
- Merge: result.back()[1] = max(9, 4) = 9
- result = [[1, 9]]

i=2: curr = [4, 7]
- lastEnd = 9, currStart = 4, currEnd = 7
- 4 <= 9? YES → overlap
- Merge: result.back()[1] = max(9, 7) = 9
- result = [[1, 9]]

i=3: curr = [6, 8]
- lastEnd = 9, currStart = 6, currEnd = 8
- 6 <= 9? YES → overlap
- Merge: result.back()[1] = max(9, 8) = 9
- result = [[1, 9]]

Output: [[1, 9]] ✓

================================================================================
COMPLEXITY ANALYSIS:
================================================================================

Time Complexity:
- Sorting: O(n log n)
- Merging loop: O(n)
- Total: O(n log n) dominated by sort

Space Complexity:
- O(1) extra space (not counting output array)
- Sorting uses O(log n) for recursion stack
- Result array stores merged intervals

Best case: O(n) when no merging needed (still need to sort)
Worst case: O(n log n) same as general case

================================================================================
PATTERN RECOGNITION:
================================================================================

Classic interval problems:
1. Merge intervals → Sort + Greedy
2. Meeting rooms → Sort + Single pass check
3. Task scheduler → Need different approach
4. Interval scheduling → Greedy based on end time

Key insight: Sorting makes problem linear!
- Before sort: O(n^2) brute force
- After sort: O(n) linear scan

================================================================================
INTERVIEW DISCUSSION POINTS:
================================================================================

Q: Why sort?
A: Ensures we process overlapping intervals consecutively. If interval A and B
   overlap, after sorting by start, we'll encounter them in order.

Q: How to check overlap?
A: If next.start <= last.end → overlapping
   Because intervals are sorted by start!

Q: Why greedy merge?
A: Merging two overlapping intervals never creates opportunities to un-merge.
   So greedy approach is optimal.

Q: Can we skip sorting?
A: Yes, but would need O(n^2) comparison or hash set. Sorting is cleaner.

Q: What if intervals are [1,3] and [3,5]?
A: 3 <= 3 is true → overlap → merge to [1,5]. Correct!

Q: Space complexity?
A: O(1) extra, but typically O(n) to store result intervals.

================================================================================
VARIATIONS:
================================================================================

1. Only count merged intervals:
   Same approach, just count instead of storing

2. Insert a new interval:
   Sort all including new one, merge once

3. Find if two intervals overlap:
   Just check: start1 <= end2 AND start2 <= end1

4. Remove overlapping (keep largest):
   Add custom comparator, or multiple passes

================================================================================
*/
