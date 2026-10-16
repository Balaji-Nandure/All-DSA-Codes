// Problem: Find a Specific Pair in Matrix
// Link: NA (Direct GFG Article Problem)
// Article: https://www.geeksforgeeks.org/dsa/find-a-specific-pair-in-matrix/
// Difficulty: Hard
// Topic: Matrix, Dynamic Programming, 2D Suffix Extrema

/*
Problem Statement:
Given an n x n matrix `mat` of integers, find the maximum value of:
    mat[c][d] - mat[a][b]
over all possible indices such that:
    c > a  AND  d > b.

In words, find two cells such that the first cell (a, b) is strictly to the top-left 
of the second cell (c, d), and the difference `mat[c][d] - mat[a][b]` is maximized.

Example 1:
Input:
mat = [
  [ 1,  2, -1, -4, -20],
  [-8, -3,  4,  2,   1],
  [ 3,  8,  6,  1,   3],
  [-4, -1,  1,  7,  -6],
  [ 0, -4, 10, -5,   1]
]
Output: 18
Explanation: 
Cell (c, d) = (4, 2) has value 10.
Cell (a, b) = (1, 0) has value -8.
Here c > a (4 > 1) and d > b (2 > 0).
Difference = 10 - (-8) = 18 (Maximum possible).

Constraints:
- 2 <= n <= 1000
- -10^5 <= mat[i][j] <= 10^5
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In 1D Best Time to Buy and Sell Stock (Problem 17 in Arrays):
//   * We maximized `prices[j] - prices[i]` with 1D index constraint `j > i`.
//   * A simple running minimum from left-to-right solved it in O(N).
// - In 2D Matrix Pair:
//   * The condition is 2-DIMENSIONAL: BOTH row and column must be strictly greater (`c > a && d > b`).
//   * This means for a chosen (a, b), the candidate (c, d) must come from the sub-matrix 
//     bounded by rows `[a+1 .. n-1]` and columns `[b+1 .. n-1]`.
//   * A 1D running prefix/suffix is not enough; we need a 2D Suffix Maximum Table.

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Brute Force (4 Nested Loops)
//   - Try every (a, b) and every (c, d) with c > a and d > b.
//   - Complexity: O(N^4) time. For N = 1000, N^4 = 10^12 operations (TLE).
//
// Approach 2: 2D Suffix Maximum Precomputation (Optimal & Chosen)
//   - Define `maxArr[i][j]` as the maximum value in the submatrix from (i, j) to (n-1, n-1).
//   - Recurrence relation for 2D suffix max:
//       `maxArr[i][j] = max({ mat[i][j], maxArr[i+1][j], maxArr[i][j+1] })`
//   - Fill `maxArr` starting from bottom-right (n-1, n-1) upwards and leftwards:
//     1. Base cell: `maxArr[n-1][n-1] = mat[n-1][n-1]`.
//     2. Last row: `maxArr[n-1][j] = max(mat[n-1][j], maxArr[n-1][j+1])`.
//     3. Last col: `maxArr[i][n-1] = max(mat[i][n-1], maxArr[i+1][n-1])`.
//     4. General cells: `maxArr[i][j] = max(mat[i][j], max(maxArr[i+1][j], maxArr[i][j+1]))`.
//   - Now for every (a, b) where `a < n - 1` and `b < n - 1`:
//     The maximum possible `mat[c][d]` is simply `maxArr[a+1][b+1]`!
//     Candidate difference = `maxArr[a+1][b+1] - mat[a][b]`.
//   - Complexity: O(N^2) time, O(N^2) auxiliary space.
//   - Why this approach: Reduces O(N^4) to O(N^2), solving in a few milliseconds.

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int findMaxValue(const vector<vector<int>>& mat, int n) {
        if (n < 2) return 0;

        // maxArr[i][j] stores the maximum value in submatrix mat[i..n-1][j..n-1]
        vector<vector<int>> maxArr(n, vector<int>(n, 0));

        // 1. Initialize the bottom-right corner
        maxArr[n - 1][n - 1] = mat[n - 1][n - 1];

        // 2. Preprocess the last row (can only take max from the right)
        for (int j = n - 2; j >= 0; --j) {
            maxArr[n - 1][j] = max(mat[n - 1][j], maxArr[n - 1][j + 1]);
        }

        // 3. Preprocess the last column (can only take max from below)
        for (int i = n - 2; i >= 0; --i) {
            maxArr[i][n - 1] = max(mat[i][n - 1], maxArr[i + 1][n - 1]);
        }

        int maxDiff = INT_MIN;

        // 4. Preprocess rest of the matrix from bottom-up, right-to-left
        for (int i = n - 2; i >= 0; --i) {
            for (int j = n - 2; j >= 0; --j) {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // At any cell (i, j), `maxArr[i+1][j+1]` is ALREADY computed and represents the 
                // absolute maximum element in the strictly bottom-right quadrant (c > i and d > j)!
                // We update maxDiff immediately before maxArr[i][j] absorbs mat[i][j].
                if (maxArr[i + 1][j + 1] - mat[i][j] > maxDiff) {
                    maxDiff = maxArr[i + 1][j + 1] - mat[i][j];
                }

                // Update maxArr[i][j] for cells higher/left of current
                maxArr[i][j] = max(mat[i][j], max(maxArr[i + 1][j], maxArr[i][j + 1]));
            }
        }

        return maxDiff;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> mat = {
        { 1,  2, -1, -4, -20},
        {-8, -3,  4,  2,   1},
        { 3,  8,  6,  1,   3},
        {-4, -1,  1,  7,  -6},
        { 0, -4, 10, -5,   1}
    };
    int n = 5;

    cout << "Maximum Specific Pair Difference: " << sol.findMaxValue(mat, n) << "\n";
    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N^2). Each cell of the N x N matrix is visited a constant number of times.
- Space Complexity: O(N^2) auxiliary space for the `maxArr` suffix matrix.

Key Takeaways:
- 2D suffix/prefix DP tables provide O(1) query time for sub-grid extrema queries, 
  turning an intractable 4-variable constraint problem into an elegant quadratic pass.
*/
