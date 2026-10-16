#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Problem: Min Cost Path Problem
 * 
 * Given a cost matrix of size N x M where cost[i][j] represents the cost of cell (i, j).
 * Find the minimum cost to travel from top-left (0, 0) to bottom-right (N - 1, M - 1).
 * Allowed movements from (i, j):
 *   1. Down:                   (i + 1, j)
 *   2. Right:                  (i,     j + 1)
 *   3. Diagonally Down-Right:  (i + 1, j + 1)
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Unlike "10. Gold Mine" which allowed free choice of starting row in column 0 and maximized gold,
 *   here source (0, 0) and destination (N - 1, M - 1) are BOTH fixed, and we MINIMIZE cost.
 * - Unlike "17. Print paths" which only moved Down and Right, diagonal moves are ALSO permitted.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - 2D Dynamic Programming (Corner-to-Corner Minimization):
 *   Let dp[i][j] be the minimum cost to reach cell (i, j) starting from (0, 0).
 *   
 *   Base Case:
 *     dp[0][0] = cost[0][0]
 *     First row:  dp[0][j] = dp[0][j - 1] + cost[0][j] (can only come from left)
 *     First col:  dp[i][0] = dp[i - 1][0] + cost[i][0] (can only come from above)
 *   
 *   Transitions for i >= 1 and j >= 1:
 *     To enter cell (i, j), we could arrive from:
 *     - Top:            dp[i - 1][j]
 *     - Left:           dp[i][j - 1]
 *     - Diagonal (TL):  dp[i - 1][j - 1]
 *     
 *     dp[i][j] = cost[i][j] + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]})
 *   
 *   Space Optimization:
 *     Using 1D array + previous diagonal variable reduces space to O(M).
 */

class Solution {
public:
    int minCostPath(vector<vector<int>>& cost) {
        int n = cost.size();
        if (n == 0) return 0;
        int m = cost[0].size();

        vector<vector<int>> dp(n, vector<int>(m, 0));

        // Base case: Starting cell
        dp[0][0] = cost[0][0];

        // Initialize first column (can only move Down)
        for (int i = 1; i < n; i++) {
            dp[i][0] = dp[i - 1][0] + cost[i][0];
        }

        // Initialize first row (can only move Right)
        for (int j = 1; j < m; j++) {
            dp[0][j] = dp[0][j - 1] + cost[0][j];
        }

        // Populate rest of the DP table
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Arrive at (i, j) via the cheapest of the 3 incoming directions (top, left, diagonal)
                dp[i][j] = cost[i][j] + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
            }
        }

        return dp[n - 1][m - 1];
    }
};

int main() {
    Solution sol;
    vector<vector<int>> cost = {
        {1, 2, 3},
        {4, 8, 2},
        {1, 5, 3}
    };

    cout << "Minimum Cost Path: " << sol.minCostPath(cost) << "\n";
    // Path: (0, 0) [1] -> (0, 1) [2] -> (1, 2) [2] -> (2, 2) [3]
    // Total cost = 1 + 2 + 2 + 3 = 8. Expected: 8.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N * M) visiting each cell of the grid once.
 * - Space Complexity: O(N * M) for the 2D DP matrix (can be optimized to O(M)).
 */
