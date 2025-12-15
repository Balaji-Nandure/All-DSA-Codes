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
 * GeeksforGeeks: https://www.geeksforgeeks.org/min-cost-path-dp-6/
 *
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

// recursive approach
int minPathSum(int i, int j, vector<vector<int>> &grid){
    if(i == 0 && j == 0) return grid[0][0]; // reached starting cell
    if(i < 0 || j < 0) return INF; // out of bounds
    
    // Can come from top (i-1, j) or left (i, j-1)
    int fromTop = minPathSum(i - 1, j, grid);
    int fromLeft = minPathSum(i, j - 1, grid);
    
    return grid[i][j] + min(fromTop, fromLeft);
}

// memoization approach
int minPathSumMemoization(int i, int j, vector<vector<int>> &grid, vector<vector<int>> &dp){
    if(i == 0 && j == 0) return grid[0][0];
    if(i < 0 || j < 0) return INF;
    
    if(dp[i][j] != -1) return dp[i][j];
    
    int fromTop = minPathSumMemoization(i - 1, j, grid, dp);
    int fromLeft = minPathSumMemoization(i, j - 1, grid, dp);
    
    return dp[i][j] = grid[i][j] + min(fromTop, fromLeft);
}

// tabulation approach
int minPathSumTabulation(int m, int n, vector<vector<int>> &grid){
    vector<vector<int>> dp(m, vector<int>(n, 0));
    
    // Base case: starting cell
    dp[0][0] = grid[0][0];
    
    // Fill first row (can only come from left)
    for(int j = 1; j < n; j++){
        dp[0][j] = grid[0][j] + dp[0][j - 1];
    }
    
    // Fill first column (can only come from top)
    for(int i = 1; i < m; i++){
        dp[i][0] = grid[i][0] + dp[i - 1][0];
    }
    
    // Fill the dp table
    for(int i = 1; i < m; i++){
        for(int j = 1; j < n; j++){
            dp[i][j] = grid[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    
    return dp[m - 1][n - 1];
}

// space optimization approach
int minPathSumSpaceOptimization(int m, int n, vector<vector<int>> &grid){
    // We only need previous row, so use 1D array
    vector<int> prev(n, 0);
    prev[0] = grid[0][0]; // starting cell
    
    // Fill first row
    for(int j = 1; j < n; j++){
        prev[j] = grid[0][j] + prev[j - 1];
    }
    
    for(int i = 1; i < m; i++){
        vector<int> curr(n, 0);
        curr[0] = grid[i][0] + prev[0]; // first column
        
        for(int j = 1; j < n; j++){
            curr[j] = grid[i][j] + min(prev[j], curr[j - 1]);
        }
        
        prev = curr;
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

