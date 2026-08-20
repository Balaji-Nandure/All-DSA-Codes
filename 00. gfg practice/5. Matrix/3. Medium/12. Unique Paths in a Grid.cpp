/*
    Problem Name: Unique Paths in a Grid
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a grid grid[][] of size n x m containing values 0 and 1:
    - 0 represents an open cell through which movement is allowed.
    - 1 represents a blocked cell that cannot be traversed.

    Starting from the top-left cell (0, 0), find the total number of distinct paths to reach the
    bottom-right cell (n - 1, m - 1).
    From any cell, movement is allowed only in the RIGHT and DOWN directions.
    Return the total number of valid paths modulo 10^9 + 7.

    Examples:
    Input: grid[][] = [[0, 0, 0],
                      [0, 1, 0],
                      [0, 0, 0]]
    Output: 2
    Explanation: Two paths:
    1. (0,0) -> (0,1) -> (0,2) -> (1,2) -> (2,2)
    2. (0,0) -> (1,0) -> (2,0) -> (2,1) -> (2,2)

    Input: grid[][] = [[1, 0, 1]]
    Output: 0
    Explanation: Source (0,0) is blocked, so no path exists.

    Constraints:
    1 <= n * m <= 10^6
    grid[i][j] = {0, 1}

    Expected Complexities:
    Time Complexity: O(N * M), visiting each cell once.
    Space Complexity: O(M), for 1D space-optimized DP.

    Approach 1: Recursion + Memoization (Top-Down DP - Striver & Love Babbar)
    Approach 2: Tabulation 2D (Bottom-Up DP - Striver & Love Babbar)
    Approach 3: Space-Optimized Tabulation (1D DP - Striver & Love Babbar)

    INTUITION & STRATEGY:
    - DP State Definition: `dp[i][j]` = total unique paths from (0,0) to cell (i, j).
    - Base Cases:
      * If `grid[i][j] == 1` (obstacle): `dp[i][j] = 0`.
      * If `i == 0 && j == 0`: `dp[0][0] = 1`.
    - DP State Transition for open cell (i, j):
      * `up = dp[i-1][j]` (path coming from above)
      * `left = dp[i][j-1]` (path coming from left)
      * `dp[i][j] = (up + left) % MOD`
*/

#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;

// ============================================================================
// Approach 1: Recursion + Memoization (Top-Down DP - Striver & Love Babbar)
// ============================================================================
class SolutionMemoization {
private:
    int solve(int i, int j, vector<vector<int>>& grid, vector<vector<int>>& memo) {
        // Boundary Check or Obstacle Check
        if (i < 0 || j < 0 || grid[i][j] == 1) {
            return 0;
        }

        // Base Case: Reached top-left starting cell
        if (i == 0 && j == 0) {
            return 1;
        }

        // Return memoized result
        if (memo[i][j] != -1) {
            return memo[i][j];
        }

        int up = solve(i - 1, j, grid, memo);
        int left = solve(i, j - 1, grid, memo);

        return memo[i][j] = (up + left) % MOD;
    }

public:
    int uniquePaths(int n, int m, vector<vector<int>>& grid) {
        if (grid[0][0] == 1 || grid[n - 1][m - 1] == 1) {
            return 0;
        }

        vector<vector<int>> memo(n, vector<int>(m, -1));
        return solve(n - 1, m - 1, grid, memo);
    }
};

// ============================================================================
// Approach 2: Tabulation 2D (Bottom-Up DP - Striver & Love Babbar)
// ============================================================================
class SolutionTabulation {
public:
    int uniquePaths(int n, int m, vector<vector<int>>& grid) {
        if (grid[0][0] == 1 || grid[n - 1][m - 1] == 1) {
            return 0;
        }

        vector<vector<int>> dp(n, vector<int>(m, 0));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    dp[i][j] = 0;
                } else if (i == 0 && j == 0) {
                    dp[0][0] = 1;
                } else {
                    int up = (i > 0) ? dp[i - 1][j] : 0;
                    int left = (j > 0) ? dp[i][j - 1] : 0;
                    dp[i][j] = (up + left) % MOD;
                }
            }
        }

        return dp[n - 1][m - 1];
    }
};

// ============================================================================
// Approach 3: Space-Optimized Tabulation (1D DP - Striver & Love Babbar)
// ============================================================================
class SolutionSpaceOptimized {
public:
    int uniquePaths(int n, int m, vector<vector<int>>& grid) {
        if (grid[0][0] == 1 || grid[n - 1][m - 1] == 1) {
            return 0;
        }

        vector<int> prev(m, 0);

        for (int i = 0; i < n; i++) {
            vector<int> curr(m, 0);

            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    curr[j] = 0;
                } else if (i == 0 && j == 0) {
                    curr[0] = 1;
                } else {
                    int up = prev[j];
                    int left = (j > 0) ? curr[j - 1] : 0;
                    curr[j] = (up + left) % MOD;
                }
            }

            prev = curr;
        }

        return prev[m - 1];
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    int uniquePaths(int n, int m, vector<vector<int>>& grid) {
        SolutionSpaceOptimized solver;
        return solver.uniquePaths(n, m, grid);
    }

    int uniquePaths(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        return uniquePaths(n, m, grid);
    }
};

int main() {
    // Example 1:
    // Expected Output: 2
    vector<vector<int>> grid1 = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}
    };
    int n1 = 3, m1 = 3;

    SolutionMemoization solver1;
    cout << "Example 1 Unique Paths (Memoization): " << solver1.uniquePaths(n1, m1, grid1) << "\n";

    // Example 2:
    // Expected Output: 0
    vector<vector<int>> grid2 = {
        {1, 0, 1}
    };
    int n2 = 1, m2 = 3;

    SolutionSpaceOptimized solver2;
    cout << "Example 2 Unique Paths (Space-Optimized): " << solver2.uniquePaths(n2, m2, grid2) << "\n";

    return 0;
}
