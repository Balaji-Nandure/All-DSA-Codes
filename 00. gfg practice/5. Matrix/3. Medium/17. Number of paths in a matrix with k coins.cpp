/*
    Problem Name: Number of paths in a matrix with k coins
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a matrix mat[][] of size n x m, where each cell contains some coins.
    Count the number of ways to collect EXACTLY k coins while moving from the top-left cell (0, 0)
    to the bottom-right cell (n-1, m-1).
    From cell (i, j), you can only move to cell (i+1, j) (Down) or (i, j+1) (Right).

    Examples:
    Input: k = 12, mat[][] = [[1, 2, 3],
                              [4, 6, 5],
                              [3, 2, 1]]
    Output: 2
    Explanation: 2 paths with total 12 coins:
    1. (0,0)[1] -> (0,1)[2] -> (1,1)[6] -> (2,1)[2] -> (2,2)[1] = 12
    2. (0,0)[1] -> (0,1)[2] -> (0,2)[3] -> (1,2)[5] -> (2,2)[1] = 12

    Input: k = 16, mat[][] = [[1, 2, 3],
                              [4, 6, 5],
                              [9, 8, 7]]
    Output: 0
    Explanation: No paths sum up to 16 coins.

    Constraints:
    1 <= k <= 100
    1 <= n, m <= 100
    0 <= mat[i][j] <= 200

    Expected Complexities:
    Time Complexity: O(N * M * K), visiting each state (i, j, k) once.
    Space Complexity: O(M * K), for 2D space-optimized DP table.

    Approach 1: 3D Recursion + Memoization (Top-Down DP - Striver & Love Babbar)
    Approach 2: 3D Bottom-Up Tabulation (Striver & Love Babbar)
    Approach 3: Space-Optimized 2D DP Table (O(M * K) Space - Striver & Love Babbar)

    CAN WE DO THIS IN 2D DP?
    - State Parameters (3 Parameters): We CANNOT drop `k` from the DP state parameters because
      a path reaching cell (i, j) with remaining coins K1 is a DIFFERENT subproblem than reaching (i, j)
      with remaining coins K2. Thus, the DP state logically requires 3 dimensions: `dp[i][j][k]`.
    - Space Optimization: However, we CAN optimize memory from 3D O(N * M * K) to 2D O(M * K) space!
      Since row `i` only depends on the previous row `i - 1`, we only need two 2D tables: `prev[m][k+1]`
      and `curr[m][k+1]`.
*/

#include <iostream>
#include <vector>

using namespace std;

// ============================================================================
// Approach 1: 3D Recursion + Memoization (Top-Down DP - Striver & Love Babbar)
// ============================================================================
class SolutionMemoization {
private:
    long long solve(int i, int j, int k, const vector<vector<int>>& mat, vector<vector<vector<long long>>>& memo) {
        if (i < 0 || j < 0 || k < 0) {
            return 0;
        }

        if (i == 0 && j == 0) {
            return (k == mat[0][0]) ? 1 : 0;
        }

        if (memo[i][j][k] != -1) {
            return memo[i][j][k];
        }

        long long up = solve(i - 1, j, k - mat[i][j], mat, memo);
        long long left = solve(i, j - 1, k - mat[i][j], mat, memo);

        return memo[i][j][k] = up + left;
    }

public:
    long long numberOfPath(int n, int m, int k, vector<vector<int>>& mat) {
        vector<vector<vector<long long>>> memo(n, vector<vector<long long>>(m, vector<long long>(k + 1, -1)));
        return solve(n - 1, m - 1, k, mat, memo);
    }
};

// ============================================================================
// Approach 2: 3D Bottom-Up Tabulation (Striver & Love Babbar)
// ============================================================================
class SolutionTabulation {
public:
    long long numberOfPath(int n, int m, int k, vector<vector<int>>& mat) {
        vector<vector<vector<long long>>> dp(n, vector<vector<long long>>(m, vector<long long>(k + 1, 0)));

        if (mat[0][0] <= k) {
            dp[0][0][mat[0][0]] = 1;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int sum = mat[i][j]; sum <= k; sum++) {
                    if (i == 0 && j == 0) continue;

                    long long up = (i > 0) ? dp[i - 1][j][sum - mat[i][j]] : 0;
                    long long left = (j > 0) ? dp[i][j - 1][sum - mat[i][j]] : 0;

                    dp[i][j][sum] = up + left;
                }
            }
        }

        return dp[n - 1][m - 1][k];
    }
};

// ============================================================================
// Approach 3: Space-Optimized 2D DP Table (O(M * K) Space - Striver & Love Babbar)
// ============================================================================
class SolutionSpaceOptimized {
public:
    long long numberOfPath(int n, int m, int k, vector<vector<int>>& mat) {
        // prev[j][sum] stores path count for previous row i-1
        vector<vector<long long>> prev(m, vector<long long>(k + 1, 0));

        if (mat[0][0] <= k) {
            prev[0][mat[0][0]] = 1;
        }

        for (int i = 0; i < n; i++) {
            vector<vector<long long>> curr(m, vector<long long>(k + 1, 0));

            for (int j = 0; j < m; j++) {
                for (int sum = mat[i][j]; sum <= k; sum++) {
                    if (i == 0 && j == 0) {
                        curr[0][mat[0][0]] = 1;
                        continue;
                    }

                    long long up = (i > 0) ? prev[j][sum - mat[i][j]] : 0;
                    long long left = (j > 0) ? curr[j - 1][sum - mat[i][j]] : 0;

                    curr[j][sum] = up + left;
                }
            }
            prev = curr;
        }

        return prev[m - 1][k];
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    long long numberOfPath(int n, int m, int k, vector<vector<int>>& mat) {
        SolutionSpaceOptimized solver;
        return solver.numberOfPath(n, m, k, mat);
    }

    long long numberOfPath(int k, vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();
        return numberOfPath(n, m, k, mat);
    }
};

int main() {
    // Example 1:
    // Expected Output: 2
    vector<vector<int>> mat1 = {
        {1, 2, 3},
        {4, 6, 5},
        {3, 2, 1}
    };
    int n1 = 3, m1 = 3, k1 = 12;

    SolutionMemoization solver1;
    cout << "Example 1 Number of Paths (Memoization): " << solver1.numberOfPath(n1, m1, k1, mat1) << "\n";

    // Example 2:
    // Expected Output: 0
    vector<vector<int>> mat2 = {
        {1, 2, 3},
        {4, 6, 5},
        {9, 8, 7}
    };
    int n2 = 3, m2 = 3, k2 = 16;

    SolutionSpaceOptimized solver3;
    cout << "Example 2 Number of Paths (Space Optimized 2D Table): " << solver3.numberOfPath(n2, m2, k2, mat2) << "\n";

    return 0;
}
