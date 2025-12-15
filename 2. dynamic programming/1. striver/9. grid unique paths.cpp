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
 * GeeksforGeeks: https://www.geeksforgeeks.org/count-possible-paths-top-left-bottom-right-nxm-matrix/
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

// recursive approach
int gridUniquePaths(int i, int j){
    if(i == 0 && j == 0) return 1; // reached destination
    if(i < 0 || j < 0) return 0; // out of bounds
    
    // Can come from top (i-1, j) or left (i, j-1)
    int fromTop = gridUniquePaths(i - 1, j);
    int fromLeft = gridUniquePaths(i, j - 1);
    
    return fromTop + fromLeft;
}

// memoization approach
int gridUniquePathsMemoization(int i, int j, vector<vector<int>> &dp){
    if(i == 0 && j == 0) return 1;
    if(i < 0 || j < 0) return 0;
    
    if(dp[i][j] != -1) return dp[i][j];
    
    int fromTop = gridUniquePathsMemoization(i - 1, j, dp);
    int fromLeft = gridUniquePathsMemoization(i, j - 1, dp);
    
    return dp[i][j] = fromTop + fromLeft;
}

// tabulation approach
int gridUniquePathsTabulation(int m, int n){
    vector<vector<int>> dp(m, vector<int>(n, 0));
    
    // Base cases: first row and first column
    for(int i = 0; i < m; i++) dp[i][0] = 1;
    for(int j = 0; j < n; j++) dp[0][j] = 1;
    
    // Fill the dp table
    for(int i = 1; i < m; i++){
        for(int j = 1; j < n; j++){
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }
    
    return dp[m - 1][n - 1];
}

// space optimization approach
int gridUniquePathsSpaceOptimization(int m, int n){
    // We only need previous row, so use 1D array
    vector<int> prev(n, 1); // first row is all 1s
    
    for(int i = 1; i < m; i++){
        vector<int> curr(n, 0);
        curr[0] = 1; // first column is always 1
        
        for(int j = 1; j < n; j++){
            curr[j] = prev[j] + curr[j - 1];
        }
        
        prev = curr;
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