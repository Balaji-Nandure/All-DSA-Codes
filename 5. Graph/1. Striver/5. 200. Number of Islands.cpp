#include <bits/stdc++.h>
using namespace std;

// LeetCode 200: Number of Islands
// https://leetcode.com/problems/number-of-islands/

// Problem: Given an m x n 2D binary grid which represents a map of '1's (land) and '0's (water),
// return the number of islands.
// An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
// You may assume all four edges of the grid are all surrounded by water.

// Solution 1: DFS Approach
// Approach: Treat each cell as a node in a graph. Use DFS to explore connected land cells.
// - Iterate through each cell in the grid
// - When we find a '1' (land) that hasn't been visited, it's a new island
// - Use DFS to mark all connected land cells as visited (change '1' to '0')
// - Count the number of times we start a new DFS (number of islands)
// Time Complexity: O(m * n) where m is rows and n is columns
// Space Complexity: O(m * n) for the recursion stack in worst case
class Solution {
private:
    // DFS helper function to mark all connected land cells
    void dfs(vector<vector<char>>& grid, int i, int j) {
        int m = grid.size();
        int n = grid[0].size();
        
        // Base cases: out of bounds or water
        if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == '0') {
            return;
        }
        
        // Mark current cell as visited by changing it to '0'
        grid[i][j] = '0';
        
        // Explore all 4 directions (up, down, left, right)
        dfs(grid, i - 1, j); // up
        dfs(grid, i + 1, j); // down
        dfs(grid, i, j - 1); // left
        dfs(grid, i, j + 1); // right
    }
    
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        
        int m = grid.size();
        int n = grid[0].size();
        int islands = 0;
        
        // Iterate through each cell in the grid
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // If we find land, it's a new island
                if (grid[i][j] == '1') {
                    islands++;
                    // Mark all connected land cells using DFS
                    dfs(grid, i, j);
                }
            }
        }
        
        return islands;
    }
};
