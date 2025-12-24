/*
 * Problem: Path with Maximum Gold
 * 
 * LeetCode 1219: Path with Maximum Gold
 * 
 * In a gold mine grid of size m x n, each cell in this mine has an integer 
 * representing the amount of gold in that cell, 0 if it is empty.
 * 
 * Return the maximum amount of gold you can collect under the conditions:
 * - You can start and stop collecting gold from any position in the grid that has some gold.
 * - You can only move to adjacent cells (up, down, left, right).
 * - You cannot visit the same cell more than once.
 * - You cannot visit a cell with 0 gold.
 * 
 * Example 1:
 * Input: grid = [[0,6,0],[5,8,7],[0,9,0]]
 * Output: 24
 * Explanation:
 * [[0,6,0],
 *  [5,8,7],
 *  [0,9,0]]
 * Path to get the maximum gold: 9 -> 8 -> 7 = 24
 * 
 * Example 2:
 * Input: grid = [[1,0,7],[2,0,6],[3,4,5],[0,3,0],[9,0,20]]
 * Output: 28
 * Explanation:
 * [[1,0,7],
 *  [2,0,6],
 *  [3,4,5],
 *  [0,3,0],
 *  [9,0,20]]
 * Path to get the maximum gold: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 = 28
 * 
 * Approach:
 * - Try starting from each cell that has gold (value > 0)
 * - For each starting cell, use DFS/backtracking to explore all possible paths
 * - Track the maximum gold collected across all paths
 * - Mark cells as visited during DFS, then backtrack
 * 
 * Time: O(m * n * 4^k) where k is the average path length
 * Space: O(k) for recursion stack
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // DFS/backtracking to collect gold starting from (i, j)
    // dfs tc = 4^(m*n) or 4^k where k is number of cells != 0.
    // dfs sc = m*n or k where k is number of cells != 0.
    // total tc = m*n * 4^(m*n)
    // total sc = m*n
    int dfs(int i, int j, vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        // Check bounds and if cell has gold
        if (i < 0 || j < 0 || i >= m || j >= n || grid[i][j] == 0)
            return 0;
        
        // Collect gold from current cell
        int gold = grid[i][j];
        
        // Mark cell as visited (set to 0 temporarily)
        // very nice technique to avoid visiting the same cell again.
        grid[i][j] = 0;
        
        // Try all 4 directions and get maximum gold from each path
        int maxGold = 0;
        maxGold = max(maxGold, dfs(i - 1, j, grid)); // UP
        maxGold = max(maxGold, dfs(i + 1, j, grid)); // DOWN
        maxGold = max(maxGold, dfs(i, j - 1, grid)); // LEFT
        maxGold = max(maxGold, dfs(i, j + 1, grid)); // RIGHT
        
        // Backtrack: restore the cell value
        grid[i][j] = gold;
        
        // Return current gold + maximum from all paths
        return gold + maxGold;
    }
    
public:
    int getMaximumGold(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int maxGold = 0;
        
        // Try starting from each cell that has gold
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] > 0) {
                    // Start DFS from this cell and track maximum
                    maxGold = max(maxGold, dfs(i, j, grid));
                }
            }
        }
        
        return maxGold;
    }
};
