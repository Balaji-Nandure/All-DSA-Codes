/*
    Problem Name: Maximum path sum in matrix
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a matrix mat[][] of size n x m where each element is a positive integer.
    Starting from any cell in the first row (r = 0), you are allowed to move to the next row with
    the following movement constraints:
    From cell (r, c), you can move to:
    1. (r+1, c-1) — move diagonally left
    2. (r+1, c)   — move directly down
    3. (r+1, c+1) — move diagonally right

    Find the maximum sum of any path starting from any column in the first row and ending at any
    column in the last row (r = n - 1).

    Examples:
    Input: mat[][] = [[3, 6, 1],
                      [2, 3, 4],
                      [5, 5, 1]]
    Output: 15
    Explanation: Path (0,1) [6] -> (1,2) [4] -> (2,1) [5] = 15.

    Input: mat[][] = [[2, 1, 1],
                      [1, 2, 2]]
    Output: 4
    Explanation: Path (0,0) [2] -> (1,1) [2] = 4.

    Input: mat[][] = [[25]]
    Output: 25

    Constraints:
    1 <= n, m <= 500
    1 <= mat[i][j] <= 1000

    Expected Complexities:
    Time Complexity: O(N * M), where N is rows and M is columns.
    Space Complexity: O(M), for 1D space-optimized DP vector.

    Approach 1: Recursion + Memoization (Top-Down DP - Striver & Love Babbar)
    Approach 2: Tabulation 2D (Bottom-Up DP - Striver & Love Babbar)
    Approach 3: Space-Optimized Tabulation (1D DP - Striver & Love Babbar)

    INTUITION & STRATEGY:
    - DP State Definition: `dp[i][j]` represents the maximum path sum from row 0 to cell `(i, j)`.
    - Base Case (row 0): `dp[0][j] = mat[0][j]` for all `0 <= j < m`.
    - DP State Transition for cell `(i, j)` coming from row `i - 1`:
      * `up = dp[i - 1][j]`
      * `upLeft = dp[i - 1][j - 1]` (if `j > 0`)
      * `upRight = dp[i - 1][j + 1]` (if `j < m - 1`)
      * `dp[i][j] = mat[i][j] + max({up, upLeft, upRight})`
    - Final Answer: Maximum value in the last row `dp[n - 1]`.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ============================================================================
// Approach 1: Recursion + Memoization (Top-Down DP - Striver & Love Babbar)
// ============================================================================
class SolutionMemoization {
private:
    int solve(int r, int c, vector<vector<int>>& mat, vector<vector<int>>& memo, int n, int m) {
        // Boundary Check
        if (c < 0 || c >= m) {
            return -1e9; // Invalid path
        }

        // Base Case: First row
        if (r == 0) {
            return mat[0][c];
        }

        // Memoized Result Check
        if (memo[r][c] != -1) {
            return memo[r][c];
        }

        // 3 Possible movements from previous row r - 1
        int up = solve(r - 1, c, mat, memo, n, m);
        int upLeft = solve(r - 1, c - 1, mat, memo, n, m);
        int upRight = solve(r - 1, c + 1, mat, memo, n, m);

        return memo[r][c] = mat[r][c] + max({up, upLeft, upRight});
    }

public:
    int maximumPath(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();

        vector<vector<int>> memo(n, vector<int>(m, -1));
        int maxPath = -1e9;

        // Try ending at every column in the last row n - 1
        for (int c = 0; c < m; c++) {
            maxPath = max(maxPath, solve(n - 1, c, mat, memo, n, m));
        }

        return maxPath;
    }
};

// ============================================================================
// Approach 2: Tabulation 2D (Bottom-Up DP - Striver & Love Babbar)
// ============================================================================
class SolutionTabulation {
public:
    int maximumPath(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();

        vector<vector<int>> dp(n, vector<int>(m, 0));

        // Base Case: Initialize first row
        for (int j = 0; j < m; j++) {
            dp[0][j] = mat[0][j];
        }

        // Fill DP table row by row
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int up = dp[i - 1][j];
                int upLeft = (j > 0) ? dp[i - 1][j - 1] : -1e9;
                int upRight = (j < m - 1) ? dp[i - 1][j + 1] : -1e9;

                dp[i][j] = mat[i][j] + max({up, upLeft, upRight});
            }
        }

        // Find maximum value in last row
        int maxPath = -1e9;
        for (int j = 0; j < m; j++) {
            maxPath = max(maxPath, dp[n - 1][j]);
        }

        return maxPath;
    }
};

// ============================================================================
// Approach 3: Space-Optimized Tabulation (1D DP - Striver & Love Babbar)
// ============================================================================
class SolutionSpaceOptimized {
public:
    int maximumPath(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();

        vector<int> prev(m, 0);

        // Base Case: Initialize row 0
        for (int j = 0; j < m; j++) {
            prev[j] = mat[0][j];
        }

        // Iterate through rows 1 to n - 1
        for (int i = 1; i < n; i++) {
            vector<int> curr(m, 0);

            for (int j = 0; j < m; j++) {
                int up = prev[j];
                int upLeft = (j > 0) ? prev[j - 1] : -1e9;
                int upRight = (j < m - 1) ? prev[j + 1] : -1e9;

                curr[j] = mat[i][j] + max({up, upLeft, upRight});
            }

            prev = curr;
        }

        return *max_element(prev.begin(), prev.end());
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    int maximumPath(vector<vector<int>>& mat) {
        SolutionSpaceOptimized solver;
        return solver.maximumPath(mat);
    }
};

int main() {
    // Example 1:
    // Expected Output: 15
    vector<vector<int>> mat1 = {
        {3, 6, 1},
        {2, 3, 4},
        {5, 5, 1}
    };

    SolutionMemoization solver1;
    cout << "Example 1 Max Path Sum (Memoization): " << solver1.maximumPath(mat1) << "\n";

    // Example 2:
    // Expected Output: 4
    vector<vector<int>> mat2 = {
        {2, 1, 1},
        {1, 2, 2}
    };

    SolutionTabulation solver2;
    cout << "Example 2 Max Path Sum (Tabulation): " << solver2.maximumPath(mat2) << "\n";

    // Example 3:
    // Expected Output: 25
    vector<vector<int>> mat3 = {
        {25}
    };

    SolutionSpaceOptimized solver3;
    cout << "Example 3 Max Path Sum (Space Optimized): " << solver3.maximumPath(mat3) << "\n";

    return 0;
}
