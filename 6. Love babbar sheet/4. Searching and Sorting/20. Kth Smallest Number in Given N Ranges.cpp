// Problem: Find K-th Smallest Element in Given N Ranges
// Link (GFG): https://www.geeksforgeeks.org/problems/find-k-th-smallest-element-in-given-n-ranges/1
// Article: https://www.geeksforgeeks.org/dsa/find-k-th-smallest-element-in-given-n-ranges/
// Difficulty: Medium
// Topic: Searching, Interval Merging, Prefix Counting, Queries

/*
Problem Statement:
Given n ranges of the form [L, R] and an array of q queries where each query 
specifies an integer k. Find the k-th smallest element among all the integers 
present in the union of these ranges (each number counted once).
If k is greater than the total number of integers in the union of the ranges, return -1.

Example 1:
Input:
n = 2, q = 3
range = [[1, 4], [6, 8]]
queries = [2, 6, 10]
Output: [2, 7, -1]
Explanation:
The union of ranges contains: [1, 2, 3, 4, 6, 7, 8].
Query 1: 2nd smallest is 2.
Query 2: 6th smallest is 7.
Query 3: 10th smallest does not exist -> -1.

Example 2:
Input:
n = 2, q = 2
range = [[2, 6], [5, 7]]
queries = [5, 8]
Output: [6, -1]
Explanation:
Merged ranges: [2, 7] containing {2, 3, 4, 5, 6, 7}.
5th smallest is 6.
8th smallest is -1.

Constraints:
- 1 <= n <= 10^5
- 1 <= q <= 10^5
- 1 <= range[i][0] <= range[i][1] <= 10^9
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Arrays Problem 14 (Merge Intervals):
//   * We simply merged overlapping intervals into non-overlapping blocks.
// - In Problem 20 (Kth Smallest in N Ranges):
//   * The ranges can overlap arbitrarily and are NOT disjoint initially.
//   * If we naively generated all numbers, memory would explode because ranges 
//     span up to 10^9!
//   * Solution: First merge overlapping intervals into a list of disjoint blocks, 
//     then answer each query K by subtracting interval capacities in O(M) or O(log M)!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Merge Intervals + Capacity Jumping (Optimal & Chosen):
//   - Step 1: Sort ranges by start time.
//   - Step 2: Merge overlapping intervals:
//       * If `curr.start <= last.end`: `last.end = max(last.end, curr.end)`.
//       * Else: Push `curr` as a new disjoint interval.
//   - Step 3: For each query `k`:
//       * Traverse the merged disjoint intervals:
//           - Interval `[L, R]` contains `count = R - L + 1` numbers.
//           - If `k <= count`:
//               The answer is directly `L + k - 1`! Found in O(1)!
//           - Else:
//               Deduct interval capacity: `k -= count`.
//       * If all intervals are exhausted and `k > 0`: Return -1.
//   - Complexity: O(N log N) to merge, O(Q * M) to query (where M <= N).
//   - Space Complexity: O(N) auxiliary space.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    vector<vector<int>> mergeRanges(vector<vector<int>>& ranges) {
        sort(ranges.begin(), ranges.end());

        vector<vector<int>> merged;
        for (const auto& r : ranges) {
            if (merged.empty() || merged.back()[1] < r[0]) {
                merged.push_back(r);
            } else {
                merged.back()[1] = max(merged.back()[1], r[1]);
            }
        }
        return merged;
    }

public:
    vector<int> kthSmallestNum(int n, vector<vector<int>>& range, int q, vector<int> queries) {
        // Step 1: Merge overlapping ranges into strictly disjoint intervals
        vector<vector<int>> merged = mergeRanges(range);

        vector<int> result;
        result.reserve(q);

        // Step 2: Answer each query by stepping across interval capacities
        for (int k : queries) {
            int ans = -1;

            for (const auto& interval : merged) {
                int L = interval[0];
                int R = interval[1];
                long long capacity = (long long)R - L + 1;

                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // If k falls within the current interval's capacity, the answer is L + k - 1 in O(1)!
                if (k <= capacity) {
                    ans = L + k - 1;
                    break;
                }

                // Otherwise, consume all numbers in this interval and continue
                k -= capacity;
            }

            result.push_back(ans);
        }

        return result;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> range1 = {{1, 4}, {6, 8}};
    vector<int> queries1 = {2, 6, 10};

    vector<int> res1 = sol.kthSmallestNum(range1.size(), range1, queries1.size(), queries1);
    cout << "Query answers for range1: ";
    for (int x : res1) cout << x << " ";
    cout << "\n";

    vector<vector<int>> range2 = {{2, 6}, {5, 7}};
    vector<int> queries2 = {5, 8};
    vector<int> res2 = sol.kthSmallestNum(range2.size(), range2, queries2.size(), queries2);
    cout << "Query answers for range2: ";
    for (int x : res2) cout << x << " ";
    cout << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity:
  * Sorting and Merging: O(N log N).
  * Processing Q queries: O(Q * M) where M is the number of merged intervals (M <= N).
- Space Complexity: O(N) auxiliary space to store the merged disjoint intervals.

Key Takeaways:
- Disjoint interval merging collapses continuous numeric intervals into O(1) mathematical capacities,
  avoiding generation of billions of numbers.
*/
