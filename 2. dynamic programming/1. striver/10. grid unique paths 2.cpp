#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
 * Problem: Grid Unique Paths 2 (With Obstacles)
 * 
 * LeetCode 63: Unique Paths II
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/special-matrix/0
 *
 * There is a robot on an m x n grid. The robot is initially located at the top-left corner 
(i.e., grid[0][0]). The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]). 
The robot can only move either down or right at any point in time.

An obstacle and space are marked as 1 and 0 respectively in grid. A path that the robot takes 
cannot include any square that is an obstacle.

Return the number of possible unique paths that the robot can take to reach the bottom-right corner.

Constraints:
- Can only move right or down
- Cannot move through obstacles (grid[i][j] == 1)
- If start or end cell has obstacle, return 0

Example:
grid = [[0, 0, 0],
        [0, 1, 0],
        [0, 0, 0]]
Paths: 2 unique paths (must avoid the obstacle at (1,1))

Recurrence:
dp[i][j] = number of ways to reach cell (i, j)
If grid[i][j] == 1 (obstacle): dp[i][j] = 0
Else: dp[i][j] = dp[i-1][j] + dp[i][j-1]
*/

// Recursive approach
int gridUniquePaths2(int i, int j, vector<vector<int>> &grid){
    // Base case: out of bounds
    if(i < 0 || j < 0) return 0;
    // Base case: obstacle cell, no path through it
    if(grid[i][j] == 1) return 0;
    // Base case: reached destination
    if(i == 0 && j == 0) return 1;
    
    // Can reach (i,j) from top (i-1,j) or left (i,j-1)
    int fromTop = gridUniquePaths2(i - 1, j, grid);
    int fromLeft = gridUniquePaths2(i, j - 1, grid);
    
    return fromTop + fromLeft;
}

// Memoization approach (Top-down DP)
int gridUniquePaths2Memoization(int i, int j, vector<vector<int>> &grid, vector<vector<int>> &dp){
    // Base cases
    if(i < 0 || j < 0) return 0;
    if(grid[i][j] == 1) return 0;
    if(i == 0 && j == 0) return 1;
    // Return cached result
    if(dp[i][j] != -1) return dp[i][j];
    
    // Compute and store result
    int fromTop = gridUniquePaths2Memoization(i - 1, j, grid, dp);
    int fromLeft = gridUniquePaths2Memoization(i, j - 1, grid, dp);
    
    return dp[i][j] = fromTop + fromLeft;
}

// Tabulation approach (Bottom-up DP)
int gridUniquePaths2Tabulation(int m, int n, vector<vector<int>> &grid){
    // Edge case: start or end has obstacle
    if(grid[0][0] == 1 || grid[m - 1][n - 1] == 1) return 0;
    
    vector<vector<int>> dp(m, vector<int>(n, 0));
    
    // Base case: starting cell
    dp[0][0] = 1;
    
    // Fill first row: can only come from left
    for(int j = 1; j < n; j++){
        if(grid[0][j] == 1) dp[0][j] = 0; // Obstacle
        else dp[0][j] = dp[0][j - 1]; // Continue from left
    }
    
    // Fill first column: can only come from top
    for(int i = 1; i < m; i++){
        if(grid[i][0] == 1) dp[i][0] = 0; // Obstacle
        else dp[i][0] = dp[i - 1][0]; // Continue from top
    }
    
    // Fill dp table: paths[i][j] = paths[i-1][j] + paths[i][j-1]
    for(int i = 1; i < m; i++){
        for(int j = 1; j < n; j++){
            if(grid[i][j] == 1) dp[i][j] = 0; // Obstacle, no path
            else dp[i][j] = dp[i - 1][j] + dp[i][j - 1]; // From top + from left
        }
    }
    
    return dp[m - 1][n - 1];
}

// Space optimization (only need previous row)
int gridUniquePaths2SpaceOptimization(int m, int n, vector<vector<int>> &grid){
    // Edge case: start or end has obstacle
    if(grid[0][0] == 1 || grid[m - 1][n - 1] == 1) return 0;
    
    // Only track previous row
    vector<int> prev(n, 0);
    prev[0] = 1; // Starting cell
    
    // Fill first row
    for(int j = 1; j < n; j++){
        if(grid[0][j] == 1) prev[j] = 0; // Obstacle
        else prev[j] = prev[j - 1]; // Continue from left
    }
    
    for(int i = 1; i < m; i++){
        vector<int> curr(n, 0);
        
        // First column
        if(grid[i][0] == 1) curr[0] = 0; // Obstacle
        else curr[0] = prev[0]; // From top
        
        // Compute current row using previous row
        for(int j = 1; j < n; j++){
            if(grid[i][j] == 1) curr[j] = 0; // Obstacle
            else curr[j] = prev[j] + curr[j - 1]; // From top + from left
        }
        
        prev = curr; // Update for next iteration
    }
    
    return prev[n - 1];
}

signed main() {
    vector<vector<int>> grid = {{0, 0, 0},
                                 {0, 1, 0},
                                 {0, 0, 0}};
    int m = grid.size();
    int n = grid[0].size();
    
    int recursive = gridUniquePaths2(m - 1, n - 1, grid);
    
    vector<vector<int>> dp1(m, vector<int>(n, -1));
    int memoization = gridUniquePaths2Memoization(m - 1, n - 1, grid, dp1);
    
    int tabulation = gridUniquePaths2Tabulation(m, n, grid);
    int spaceOptimization = gridUniquePaths2SpaceOptimization(m, n, grid);
    
    cout << "Recursive: " << recursive << endl;
    cout << "Memoization: " << memoization << endl;
    cout << "Tabulation: " << tabulation << endl;
    cout << "Space Optimization: " << spaceOptimization << endl;
    
    return 0;
}

