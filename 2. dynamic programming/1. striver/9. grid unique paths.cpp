#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
 * Problem: Grid Unique Paths
 * 
 * LeetCode 62: Unique Paths
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/number-of-paths/0
 *
 * There is a robot on an m x n grid. The robot is initially located at the top-left corner 
(i.e., grid[0][0]). The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]). 
The robot can only move either down or right at any point in time.

Given the two integers m and n, return the number of possible unique paths that the robot 
can take to reach the bottom-right corner.

Constraints:
- Can only move right or down
- Cannot move diagonally or backwards
- Answer will be <= 2 * 10^9

Example:
m = 3, n = 7
Grid: 3x7
Paths: 28 unique paths

Recurrence:
dp[i][j] = number of ways to reach cell (i, j)
dp[i][j] = dp[i-1][j] + dp[i][j-1]
Base cases:
- dp[0][j] = 1 (only way: move right)
- dp[i][0] = 1 (only way: move down)
*/

// Recursive approach
int gridUniquePaths(int i, int j){
    // Base case: reached destination (top-left)
    if(i == 0 && j == 0) return 1;
    // Base case: out of bounds
    if(i < 0 || j < 0) return 0;
    
    // Can reach (i,j) from top (i-1,j) or left (i,j-1)
    int fromTop = gridUniquePaths(i - 1, j);
    int fromLeft = gridUniquePaths(i, j - 1);
    
    return fromTop + fromLeft;
}

// Memoization approach (Top-down DP)
int gridUniquePathsMemoization(int i, int j, vector<vector<int>> &dp){
    // Base cases
    if(i == 0 && j == 0) return 1;
    if(i < 0 || j < 0) return 0;
    // Return cached result
    if(dp[i][j] != -1) return dp[i][j];
    
    // Compute and store result
    int fromTop = gridUniquePathsMemoization(i - 1, j, dp);
    int fromLeft = gridUniquePathsMemoization(i, j - 1, dp);
    
    return dp[i][j] = fromTop + fromLeft;
}

// Tabulation approach (Bottom-up DP)
int gridUniquePathsTabulation(int m, int n){
    vector<vector<int>> dp(m, vector<int>(n, 0));
    
    // Base cases: first row and first column have only 1 path
    for(int i = 0; i < m; i++) dp[i][0] = 1; // First column
    for(int j = 0; j < n; j++) dp[0][j] = 1; // First row
    
    // Fill dp table: paths[i][j] = paths[i-1][j] + paths[i][j-1]
    for(int i = 1; i < m; i++){
        for(int j = 1; j < n; j++){
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }
    
    return dp[m - 1][n - 1];
}

// Space optimization (only need previous row)
int gridUniquePathsSpaceOptimization(int m, int n){
    // Only track previous row (size n)
    vector<int> prev(n, 1); // First row is all 1s
    
    for(int i = 1; i < m; i++){
        vector<int> curr(n, 0);
        curr[0] = 1; // First column is always 1
        
        // Compute current row using previous row
        for(int j = 1; j < n; j++){
            curr[j] = prev[j] + curr[j - 1]; // From top + from left
        }
        
        prev = curr; // Update for next iteration
    }
    
    return prev[n - 1];
}

signed main() {
    int m = 3, n = 7;
    
    int recursive = gridUniquePaths(m - 1, n - 1);
    
    vector<vector<int>> dp1(m, vector<int>(n, -1));
    int memoization = gridUniquePathsMemoization(m - 1, n - 1, dp1);
    
    int tabulation = gridUniquePathsTabulation(m, n);
    int spaceOptimization = gridUniquePathsSpaceOptimization(m, n);
    
    cout << "Recursive: " << recursive << endl;
    cout << "Memoization: " << memoization << endl;
    cout << "Tabulation: " << tabulation << endl;
    cout << "Space Optimization: " << spaceOptimization << endl;
    
    return 0;
}