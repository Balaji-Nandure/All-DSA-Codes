#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: Maximal Square
LeetCode 221: https://leetcode.com/problems/maximal-square/
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/largest-square-formed-in-a-matrix0806/1

Given an m x n binary matrix filled with 0's and 1's, find the largest square containing 
only 1's and return its area.

Constraints:
- m == matrix.length
- n == matrix[i].length
- 1 <= m, n <= 300
- matrix[i][j] is '0' or '1'

Example:
matrix = [["1","0","1","0","0"],
          ["1","0","1","1","1"],
          ["1","1","1","1","1"],
          ["1","0","0","1","0"]]
Output: 4 (2x2 square)

Key Insight:
- For a square to end at (i, j), all three adjacent cells (top, left, top-left) 
  must also be part of a square
- The side length of square ending at (i, j) depends on the minimum of its three neighbors
- This ensures we form a valid square

DP State:
- dp[i][j] = side length of the largest square ending at position (i, j)

Recurrence Relation:
- If matrix[i][j] == '1':
  dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1
  (Take minimum of three neighbors and add 1)
- If matrix[i][j] == '0':
  dp[i][j] = 0 (can't form square ending here)

Base Cases:
- dp[0][j] = 1 if matrix[0][j] == '1', else 0
- dp[i][0] = 1 if matrix[i][0] == '1', else 0

Time Complexity: O(m * n)
Space Complexity: O(m * n) for tabulation, O(n) for space optimized
*/

// ❌
// Approach 1: Pure Recursion (take/not take method)
class Solution1_Recursion {
public:
    // TC: O(3^(m*n)) exponential, SC: O(m * n) recursion stack
    int solve(int i, int j, vector<vector<char>>& matrix) {
        // Base case: out of bounds or cell is '0'
        if (i < 0 || j < 0 || matrix[i][j] == '0') return 0;
        
        // Recursively check three neighbors
        int top = solve(i - 1, j, matrix);
        int left = solve(i, j - 1, matrix);
        int topLeft = solve(i - 1, j - 1, matrix);
        
        // Side length is minimum of three neighbors + 1
        return 1 + min({top, left, topLeft});
    }
    
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        int maxSide = 0;
        
        // Check all possible ending positions
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == '1') {
                    maxSide = max(maxSide, solve(i, j, matrix));
                }
            }
        }
        
        return maxSide * maxSide; // Return area
    }
};

// ❌
// Approach 2: Memoization (Top-down DP)
class Solution2_Memoization {
public:
    // TC: O(m * n), SC: O(m * n) for dp + O(m * n) recursion stack
    int solve(int i, int j, vector<vector<char>>& matrix, vector<vector<int>>& dp) {
        // Base cases
        if (i < 0 || j < 0 || matrix[i][j] == '0') return 0;
        
        if (dp[i][j] != -1) return dp[i][j];
        
        // Get side lengths from three neighbors
        int top = solve(i - 1, j, matrix, dp);
        int left = solve(i, j - 1, matrix, dp);
        int topLeft = solve(i - 1, j - 1, matrix, dp);
        
        // Minimum of three neighbors + 1
        return dp[i][j] = 1 + min({top, left, topLeft});
    }
    
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n, -1));
        int maxSide = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == '1') {
                    maxSide = max(maxSide, solve(i, j, matrix, dp));
                }
            }
        }
        
        return maxSide * maxSide;
    }
};

// Approach 3: Tabulation (Bottom-up DP)
class Solution3_Tabulation {
public:
    // TC: O(m * n), SC: O(m * n) for dp array
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        
        // dp[i][j] = side length of largest square ending at (i, j)
        vector<vector<int>> dp(m, vector<int>(n, 0));
        int maxSide = 0;
        
        // Fill first row and column
        for (int i = 0; i < m; i++) {
            dp[i][0] = (matrix[i][0] == '1') ? 1 : 0;
            maxSide = max(maxSide, dp[i][0]);
        }
        for (int j = 0; j < n; j++) {
            dp[0][j] = (matrix[0][j] == '1') ? 1 : 0;
            maxSide = max(maxSide, dp[0][j]);
        }
        
        // Fill rest of the table
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][j] == '1') {
                    // Minimum of three neighbors + 1
                    dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
                    maxSide = max(maxSide, dp[i][j]);
                } else {
                    dp[i][j] = 0;
                }
            }
        }
        
        return maxSide * maxSide; // Return area
    }
};

// Approach 4: Space Optimization (O(n) space)
class Solution4_SpaceOptimized {
public:
    // TC: O(m * n), SC: O(n) - only track previous row
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        
        // prev[j] = dp[i-1][j] (previous row)
        // curr[j] = dp[i][j] (current row)
        vector<int> prev(n, 0);
        vector<int> curr(n, 0);
        int maxSide = 0;
        
        // Initialize first row
        for (int j = 0; j < n; j++) {
            prev[j] = (matrix[0][j] == '1') ? 1 : 0;
            maxSide = max(maxSide, prev[j]);
        }
        
        // Process remaining rows
        for (int i = 1; i < m; i++) {
            // First column
            curr[0] = (matrix[i][0] == '1') ? 1 : 0;
            maxSide = max(maxSide, curr[0]);
            
            // Rest of columns
            for (int j = 1; j < n; j++) {
                if (matrix[i][j] == '1') {
                    // curr[j] = min(prev[j], curr[j-1], prev[j-1]) + 1
                    curr[j] = 1 + min({prev[j], curr[j - 1], prev[j - 1]});
                    maxSide = max(maxSide, curr[j]);
                } else {
                    curr[j] = 0;
                }
            }
            
            prev = curr; // Update for next iteration
        }
        
        return maxSide * maxSide;
    }
};
