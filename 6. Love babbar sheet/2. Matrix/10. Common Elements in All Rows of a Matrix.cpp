// Problem: Common Elements in All Rows of a Given Matrix
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/common-elements1132/1
// Article: https://www.geeksforgeeks.org/dsa/common-elements-in-all-rows-of-a-given-matrix/
// Difficulty: Medium
// Topic: Matrix, Hash Map, Set Intersection

/*
Problem Statement:
Given an m x n matrix, find all common elements present in all rows of the matrix.
The matrix elements are NOT necessarily sorted.
The algorithm must run in O(m * n) time and handle duplicate elements within 
the same row correctly (i.e. an element should not be counted multiple times 
within the same row).

Example 1:
Input:
m = 4, n = 5
mat = [[1, 2, 1, 4, 8],
       [3, 7, 8, 5, 1],
       [8, 7, 7, 3, 1],
       [8, 1, 2, 7, 9]]
Output: [1, 8]
Explanation: 1 and 8 are the only elements present in every single row.

Example 2:
Input:
m = 2, n = 3
mat = [[1, 2, 3],
       [4, 5, 6]]
Output: []
Explanation: No common elements present in all rows.

Constraints:
- 1 <= m, n <= 1000
- -10^5 <= mat[i][j] <= 10^5
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 19 of Arrays (Common Elements in 3 Sorted Arrays):
//   * The arrays were already sorted, enabling 3-pointer synchronized marching in O(1) space.
// - In Problem 10 of Matrix (Common Elements in ALL Rows of Unsorted Matrix):
//   * The rows are UNSORTED and there can be arbitrary M rows (not just 3).
//   * Multiple identical values can exist within the SAME row (e.g., [1, 2, 1, 4, 8] has two 1s).
//   * If we just count frequencies globally, multiple duplicates in row 0 could artificially 
//     reach frequency M even if missing in other rows!
//   * Solution: We map each element not to a count, but to the LAST ROW INDEX where it was confirmed.
//     An element can only advance to row `i` if it was already confirmed in row `i - 1`!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Sort each row + Binary Search
//   - Sort all M rows: O(M * N log N).
//   - Check presence: O(M * N log N).
//   - Why Suboptimal: Sorting mutates the matrix and adds a log N overhead.
//
// Approach 2: Row-Index Chaining with Hash Map (Optimal & Chosen)
//   - Create `unordered_map<int, int> lastSeenRow`.
//   - Step 1: Initialize map with all elements of row 0: `lastSeenRow[mat[0][j]] = 0`.
//   - Step 2: For each subsequent row `i` from 1 to `m - 1`:
//       * For each column `j` from 0 to `n - 1`:
//           If `lastSeenRow[mat[i][j]] == i - 1`:
//             - This means the element was confirmed in ALL rows up to `i - 1`!
//             - Advance its status: `lastSeenRow[mat[i][j]] = i`.
//             - If `i == m - 1`: it has survived all rows, add to `result`!
//   - Why this handles duplicates in the same row gracefully:
//     * When the second duplicate in row `i` is encountered, `lastSeenRow` is ALREADY `i`.
//     * Since `i != i - 1`, the `if` check evaluates to false! Duplicate avoided in O(1) without sets!
//   - Complexity: O(M * N) time, O(N) auxiliary space.

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> findCommonElements(const vector<vector<int>>& mat) {
        vector<int> result;
        if (mat.empty() || mat[0].empty()) return result;

        int m = mat.size();
        int n = mat[0].size();

        // Single row matrix: all unique elements of that row are common
        if (m == 1) {
            unordered_map<int, bool> seen;
            for (int val : mat[0]) {
                if (!seen[val]) {
                    seen[val] = true;
                    result.push_back(val);
                }
            }
            return result;
        }

        // Map stores: element -> last row index where it was verified
        unordered_map<int, int> lastSeenRow;

        // Initialize with row 0
        for (int j = 0; j < n; ++j) {
            lastSeenRow[mat[0][j]] = 0;
        }

        // Process rows 1 to m-1
        for (int i = 1; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int val = mat[i][j];

                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // An element is only promoted to row `i` if it was verified in row `i - 1`.
                // If the same element appears a second time in row `i`, its lastSeenRow is 
                // already `i`, which fails `== i - 1`. This provides automatic O(1) duplicate suppression!
                if (lastSeenRow.find(val) != lastSeenRow.end() && lastSeenRow[val] == i - 1) {
                    lastSeenRow[val] = i; // Promote to current row

                    // If it reaches the final row, it is present in ALL rows!
                    if (i == m - 1) {
                        result.push_back(val);
                    }
                }
            }
        }

        return result;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> mat = {
        {1, 2, 1, 4, 8},
        {3, 7, 8, 5, 1},
        {8, 7, 7, 3, 1},
        {8, 1, 2, 7, 9}
    };

    vector<int> common = sol.findCommonElements(mat);
    cout << "Common Elements in All Rows: ";
    for (int x : common) cout << x << " ";
    cout << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(M * N). Every element of the matrix is visited exactly once with O(1) hash map operations.
- Space Complexity: O(N) auxiliary space. The hash map only holds distinct elements from row 0 (at most N elements).

Key Takeaways:
- Tracking state transitions (`== i - 1`) instead of simple counting prevents duplicate counting 
  within a single row without allocating extra sets per row.
*/
