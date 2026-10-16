// Problem: Row with Maximum Number of 1s
// Link (GFG): https://www.geeksforgeeks.org/problems/row-with-max-1s0023/1
// Article: https://www.geeksforgeeks.org/dsa/find-the-row-with-maximum-number-1s/
// Difficulty: Medium
// Topic: Matrix, Binary Search, Two Pointers (Top-Right Ladder)

/*
Problem Statement:
Given a boolean 2D array of n x m dimensions where each row is sorted 
(all 0s appear first, followed by all 1s).
Find the 0-based index of the first row that has the maximum number of 1s.
If no row has any 1, return -1.

Example 1:
Input: 
n = 4, m = 4
arr = [[0, 1, 1, 1],
       [0, 0, 1, 1],
       [1, 1, 1, 1],
       [0, 0, 0, 0]]
Output: 2
Explanation: Row 2 has 4 ones, which is the maximum among all rows.

Example 2:
Input: 
n = 2, m = 2
arr = [[0, 0], 
       [1, 1]]
Output: 1
Explanation: Row 1 has 2 ones.

Example 3:
Input:
n = 2, m = 2
arr = [[0, 0],
       [0, 0]]
Output: -1
Explanation: No 1s present in the entire matrix.

Constraints:
- 1 <= n, m <= 10^3
- 0 <= arr[i][j] <= 1
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 2 (Search in a Matrix):
//   * We stopped as soon as a single target value was found.
// - In Problem 4 (Row with Maximum 1s):
//   * We must find the ARGMAX (which row index has the highest count of 1s).
//   * Because rows are sorted (all 0s then all 1s), the number of 1s in a row is 
//     completely determined by the position of its FIRST occurrence of 1!
//   * Instead of resetting the search column for every row (which would take O(N * log M)),
//     we can maintain the `col` index across rows! Once a row has 1s up to `col`, any future 
//     row only beats it if it has a 1 strictly to the left of `col`!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Brute Force Count
//   - Sum all elements row by row.
//   - Complexity: O(N * M) time.
//   - Why Suboptimal: Completely wastes the fact that rows are sorted.
//
// Approach 2: Binary Search per Row
//   - For each row, find the first '1' using `lower_bound`. Number of 1s = M - first_1_idx.
//   - Complexity: O(N * log M) time, O(1) space.
//   - Why Suboptimal: Still checks all N rows independently without carrying forward 
//     the threshold benchmark.
//
// Approach 3: Top-Right Ladder Traversal (Optimal & Chosen)
//   - Start at the top-right corner: `row = 0`, `col = M - 1`.
//   - While `row < N && col >= 0`:
//     * If `mat[row][col] == 1`:
//         This row has at least `M - col` ones, which beats or matches previous record!
//         Update `maxRowIdx = row`.
//         To see if this row (or any later row) has even MORE 1s, step left: `col--`.
//     * If `mat[row][col] == 0`:
//         This row cannot provide any more 1s to the left!
//         Step down to the next row to see if it can beat current `col`: `row++`.
//   - Complexity: O(N + M) time, O(1) auxiliary space!
//   - Why this approach: It visits at most N rows and M columns total. It is the absolute 
//     fastest possible algorithm.

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int rowWithMax1s(vector<vector<int>>& mat) {
        if (mat.empty() || mat[0].empty()) return -1;

        int n = mat.size();
        int m = mat[0].size();

        int maxRowIdx = -1;
        int row = 0;
        int col = m - 1;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Ladder walk: We only move LEFT when we find a 1, and DOWN when we hit a 0.
        // Because `col` NEVER resets back to m-1, the total steps cannot exceed (N + M)!
        while (row < n && col >= 0) {
            if (mat[row][col] == 1) {
                maxRowIdx = row; // Found a row with 1 at least as far left as `col`
                col--;           // Greedily check if this row has a 1 even further left
            } else {
                row++;           // Encountered 0; this row has no 1s at or left of `col`, move down
            }
        }

        return maxRowIdx;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> mat = {
        {0, 1, 1, 1},
        {0, 0, 1, 1},
        {1, 1, 1, 1},
        {0, 0, 0, 0}
    };

    cout << "Row with maximum number of 1s: " << sol.rowWithMax1s(mat) << "\n";
    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N + M). In each step of the while loop, either `row` increases or `col` decreases.
  * Maximum row increments: N.
  * Maximum col decrements: M.
  * Total loop iterations: at most N + M.
- Space Complexity: O(1) auxiliary space.

Key Takeaways:
- Maintaining persistent search boundaries across outer loop iterations reduces O(N * log M) to O(N + M).
*/
