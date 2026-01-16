#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;


/*
Problem: Cherry Pickup II
LeetCode 1463: https://leetcode.com/problems/cherry-pickup-ii/

Given a grid with cherries:
- grid[i][j] = number of cherries at cell (i, j)
- Two robots start at (0, 0) and (0, cols-1)
- Both can only move DOWN, but can move LEFT or RIGHT within the same row
- They collect cherries, but if both are at the same cell, only one collects
- Find maximum cherries collected

DP State: dp[row][col1][col2] = max cherries when:
- Robot 1 is at (row, col1)
- Robot 2 is at (row, col2)
- Both are at the same row (since they move down together)

Recurrence:
dp[row][col1][col2] = grid[row][col1] + grid[row][col2] (if col1 != col2, else count once)
                    + max of all 9 combinations of previous moves:
                      - Both can move: left, stay, or right (3x3 = 9 combinations)
                      - From previous row: dp[row-1][prev_col1][prev_col2]

Base Cases:
- dp[0][0][cols-1] = grid[0][0] + grid[0][cols-1] (if different, else count once)
- If any cell is out of bounds, that state is invalid

Time Complexity: O(rows * cols^2) - row goes from 0 to rows-1, col1 and col2 each go from 0 to cols-1
Space Complexity: O(rows * cols^2) for memoization, O(cols^2) for tabulation
*/
class Solution {
public:
    int solve(int i, int j1, int j2, vector<vector<int>> &grid, vector<vector<vector<int>>> &dp){
        int m = grid.size();
        int n = grid[0].size();
        //  out bound cases
        if(i > m || j1 < 0 || j2 < 0 || j1 >= n || j2 >= n) return -1e9;
        if(i == m) return 0;
        if(dp[i][j1][j2] != -1) return dp[i][j1][j2];

        int cherries = 0;
        if(j1 == j2){
            cherries += grid[i][j2];
        } else {
            cherries = grid[i][j1] + grid[i][j2];
        }

        int maxCherry = -1e9;
        for(int d1 = -1; d1 <= 1; d1++){
            for(int d2 = -1; d2 <= 1; d2++){
                maxCherry = max(maxCherry, solve(i + 1, j1 + d1, j2 + d2, grid, dp));
            }
        }

        if(maxCherry == -1e9) return dp[i][j1][j2] = -1e9;
        return dp[i][j1][j2] = (cherries + maxCherry);
    }
    int cherryPickup(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        // dp[i][j1][j2];
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(n, -1)));

        int result = solve(0, 0, n - 1, grid, dp);
        if(result < 0) return 0;
        else return result;
    }
};