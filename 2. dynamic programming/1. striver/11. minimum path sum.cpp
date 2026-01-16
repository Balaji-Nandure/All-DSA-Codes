#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
 * Problem: Minimum Path Sum
 * 
 * LeetCode 64: Minimum Path Sum
 * GeeksforGeeks Practice: https://leetcode.com/problems/minimum-path-sum/submissions/1886461497/
 
 * Given a m x n grid filled with non-negative numbers, find a path from top-left to 
bottom-right which minimizes the sum of all numbers along its path.

The robot can only move either down or right at any point in time.

Constraints:
- Can only move right or down
- Grid contains non-negative numbers
- Find the path with minimum sum

Example:
grid = [[1, 3, 1],
        [1, 5, 1],
        [4, 2, 1]]
Minimum path: 1 -> 3 -> 1 -> 1 -> 1 = 7
Or: 1 -> 1 -> 4 -> 2 -> 1 = 9
Minimum = 7

Recurrence:
dp[i][j] = minimum sum to reach cell (i, j)
dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1])
Base cases:
- dp[0][0] = grid[0][0]
- dp[0][j] = grid[0][j] + dp[0][j-1] (only from left)
- dp[i][0] = grid[i][0] + dp[i-1][0] (only from top)
*/

// Recursive approach 
int minPathSum(int i, int j, vector<vector<int>> &grid){
    // Base case: reached starting cell
    if(i == 0 && j == 0) return grid[0][0];
    // Base case: out of bounds
    if(i < 0 || j < 0) return INF;
    
    // Can reach (i,j) from top (i-1,j) or left (i,j-1)
    // Take minimum and add current cell value
    int fromTop = minPathSum(i - 1, j, grid);
    int fromLeft = minPathSum(i, j - 1, grid);
    
    return grid[i][j] + min(fromTop, fromLeft);
}

// Memoization approach (Top-down DP)
int minPathSumMemoization(int i, int j, vector<vector<int>> &grid, vector<vector<int>> &dp){
    // Base cases
    if(i == 0 && j == 0) return grid[0][0];
    if(i < 0 || j < 0) return INF;
    // Return cached result
    if(dp[i][j] != -1) return dp[i][j];
    
    // Compute and store result
    int fromTop = minPathSumMemoization(i - 1, j, grid, dp);
    int fromLeft = minPathSumMemoization(i, j - 1, grid, dp);
    
    return dp[i][j] = grid[i][j] + min(fromTop, fromLeft);
}

// Tabulation approach (Bottom-up DP)
int minPathSumTabulation(int m, int n, vector<vector<int>> &grid){
    vector<vector<int>> dp(m, vector<int>(n, 0));
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(i == 0 && j == 0) {
                dp[i][j] = grid[i][j];
            }
            else if(i == 0) {
                dp[i][j] = grid[i][j] + dp[i][j - 1];
            }
            else if(j == 0) {
                dp[i][j] = grid[i][j] + dp[i - 1][j];
            }
            else {
                dp[i][j] = grid[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[m - 1][n - 1];
}

// Space optimization (only need previous row)
int minPathSumSpaceOptimization(int m, int n, vector<vector<int>> &grid){
    // Only track previous row
    vector<int> prev(n, 0);
    prev[0] = grid[0][0]; // Starting cell
    
    // Fill first row
    for(int j = 1; j < n; j++){
        prev[j] = grid[0][j] + prev[j - 1];
    }
    
    for(int i = 1; i < m; i++){
        vector<int> curr(n, 0);
        curr[0] = grid[i][0] + prev[0]; // First column: from top
        
        // Compute current row using previous row
        for(int j = 1; j < n; j++){
            curr[j] = grid[i][j] + min(prev[j], curr[j - 1]); // From top or from left
        }
        
        prev = curr; // Update for next iteration
    }
    
    return prev[n - 1];
}

signed main() {
    vector<vector<int>> grid = {{1, 3, 1},
                                 {1, 5, 1},
                                 {4, 2, 1}};
    int m = grid.size();
    int n = grid[0].size();
    
    int recursive = minPathSum(m - 1, n - 1, grid);
    
    vector<vector<int>> dp1(m, vector<int>(n, -1));
    int memoization = minPathSumMemoization(m - 1, n - 1, grid, dp1);
    
    int tabulation = minPathSumTabulation(m, n, grid);
    int spaceOptimization = minPathSumSpaceOptimization(m, n, grid);
    
    cout << "Recursive: " << recursive << endl;
    cout << "Memoization: " << memoization << endl;
    cout << "Tabulation: " << tabulation << endl;
    cout << "Space Optimization: " << spaceOptimization << endl;
    
    return 0;
}

