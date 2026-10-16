#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Problem: Gold Mine Problem
 * 
 * Given an N x M matrix representing a gold mine, where each cell contains gold.
 * A miner starts at ANY cell in the first column (column 0) and can move to:
 *   1. Diagonally up-right:   (r - 1, c + 1)
 *   2. Directly right:        (r,     c + 1)
 *   3. Diagonally down-right: (r + 1, c + 1)
 * Find the maximum amount of gold the miner can collect reaching the last column (column M - 1).
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Unlike "17. Print paths from top-left to bottom-right" where the start is fixed at (0, 0)
 *   and movements are Down/Right, here the start can be ANY row in column 0, and movements 
 *   are strictly column-advancing to the RIGHT (with row choices: -1, 0, +1).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Column-by-Column Dynamic Programming:
 *   Because movements strictly increase the column coordinate from c to c + 1,
 *   subproblems at column c depend exclusively on results at column c + 1!
 *   
 *   Recurrence Relation (traversing column c from M - 2 down to 0):
 *     dp[r][c] = mine[r][c] + max({
 *         (r > 0)     ? dp[r - 1][c + 1] : 0,  // Move up-right
 *         dp[r][c + 1],                        // Move right
 *         (r < N - 1) ? dp[r + 1][c + 1] : 0   // Move down-right
 *     })
 *   
 *   Result:
 *     max_{0 <= r < N} dp[r][0]
 *   
 *   Space Optimization:
 *     We only need the next column `c + 1` to compute column `c`. Space can be O(N) 
 *     or O(1) by updating the grid in-place!
 */

class Solution {
public:
    int maxGold(int n, int m, vector<vector<int>>& M) {
        // dp[r][c] stores max gold collectible from (r, c) to last column
        vector<vector<int>> dp(n, vector<int>(m, 0));

        // Base case: Last column values are just the gold in that cell
        for (int r = 0; r < n; r++) {
            dp[r][m - 1] = M[r][m - 1];
        }

        // Process columns from right to left (from m - 2 down to 0)
        for (int c = m - 2; c >= 0; c--) {
            for (int r = 0; r < n; r++) {
                // Option 1: Move right-up
                int right_up = (r > 0) ? dp[r - 1][c + 1] : 0;

                // Option 2: Move right
                int right = dp[r][c + 1];

                // Option 3: Move right-down
                int right_down = (r < n - 1) ? dp[r + 1][c + 1] : 0;

                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Max gold from (r, c) is cell's gold + max of the 3 legal rightward transitions
                dp[r][c] = M[r][c] + max({right_up, right, right_down});
            }
        }

        // Maximum gold starting from any row in the first column
        int max_gold = 0;
        for (int r = 0; r < n; r++) {
            max_gold = max(max_gold, dp[r][0]);
        }

        return max_gold;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> mine1 = {
        {1, 3, 3},
        {2, 1, 4},
        {0, 6, 4}
    };
    int n1 = 3, m1 = 3;
    cout << "Max Gold 1: " << sol.maxGold(n1, m1, mine1) << "\n";
    // Path: (2, 0) [0] -> (2, 1) [6] -> (1, 2) [4] = 12, or (1,0)[2] -> (2,1)[6] -> (1,2)[4] = 12

    vector<vector<int>> mine2 = {
        {1, 3, 1, 5},
        {2, 2, 4, 1},
        {5, 0, 2, 3},
        {0, 6, 1, 2}
    };
    int n2 = 4, m2 = 4;
    cout << "Max Gold 2: " << sol.maxGold(n2, m2, mine2) << "\n";
    // Path: (2, 0)[5] -> (1, 1)[2] -> (0, 2)[1] -> (0, 3)[5] or (2,0)[5] -> (3,1)[6] -> (2,2)[2] -> (2,3)[3] = 16

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N * M) iterating through every cell once.
 * - Space Complexity: O(N * M) for the DP table (can be optimized to O(N) using two column vectors).
 */
