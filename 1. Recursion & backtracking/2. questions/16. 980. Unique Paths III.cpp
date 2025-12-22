/*
 * Problem: 980. Unique Paths III
 * 
 * You are given an m x n integer array grid where grid[i][j] could be:
 * - 1 representing the starting square. There is exactly one starting square.
 * - 2 representing the ending square. There is exactly one ending square.
 * - 0 representing empty squares we can walk over.
 * - -1 representing obstacles that we cannot walk over.
 * 
 * Return the number of 4-directionally walks from the starting square to the ending square,
 * that walk over every non-obstacle square exactly once.
 * 
 * Example 1:
 * Input: grid = [[1,0,0,0],[0,0,0,0],[0,0,2,-1]]
 * Output: 2
 * Explanation: We have the following two paths:
 * 1. (0,0)->(0,1)->(0,2)->(0,3)->(1,3)->(1,2)->(1,1)->(1,0)->(2,0)->(2,1)->(2,2)
 * 2. (0,0)->(1,0)->(2,0)->(2,1)->(1,1)->(0,1)->(0,2)->(0,3)->(1,3)->(1,2)->(2,2)
 * 
 * Example 2:
 * Input: grid = [[1,0,0,0],[0,0,0,0],[0,0,0,2]]
 * Output: 4
 * 
 * Example 3:
 * Input: grid = [[0,1],[2,0]]
 * Output: 0
 */

#include <bits/stdc++.h>
using namespace std;

// DFS/backtracking to count paths visiting all non-obstacle cells
void dfs(int i, int j, int m, int n, vector<vector<int>>& grid, 
         int cellsVisited, int totalCells, int& count) {
    // Base case: out of bounds or obstacle
    if (i < 0 || j < 0 || i >= m || j >= n || grid[i][j] == -1) {
        return;
    }
    
    // Base case: reached ending square (value 2)
    if (grid[i][j] == 2) {
        // Valid path only if visited all non-obstacle cells
        if (cellsVisited == totalCells) {
            count++;
        }
        return;
    }
    
    // Mark current cell as visited (temporarily set to -1)
    int saved = grid[i][j];
    grid[i][j] = -1;
    
    // Try all 4 directions: UP, DOWN, LEFT, RIGHT
    dfs(i - 1, j, m, n, grid, cellsVisited + 1, totalCells, count); // UP
    dfs(i + 1, j, m, n, grid, cellsVisited + 1, totalCells, count); // DOWN
    dfs(i, j - 1, m, n, grid, cellsVisited + 1, totalCells, count); // LEFT
    dfs(i, j + 1, m, n, grid, cellsVisited + 1, totalCells, count); // RIGHT
    
    // Backtrack: restore cell value
    grid[i][j] = saved;
}

int uniquePathsIII(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    
    int startRow = -1, startCol = -1;
    int totalCells = 0; // Count of cells we need to visit (0, 1, 2)
    
    // Find starting position and count total non-obstacle cells
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                startRow = i;
                startCol = j;
            }
            if (grid[i][j] != -1) {
                totalCells++; // Count all non-obstacle cells
            }
        }
    }
    
    // If no starting position found
    if (startRow == -1 || startCol == -1) {
        return 0;
    }
    
    int count = 0;
    // Start DFS from starting position
    // cellsVisited starts at 1 because we're at the starting cell
    dfs(startRow, startCol, m, n, grid, 1, totalCells, count);
    
    return count;
}

// Helper function to print grid
void printGrid(vector<vector<int>>& grid) {
    for (auto& row : grid) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
    // Test case 1
    vector<vector<int>> grid1 = {
        {1, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 2, -1}
    };
    
    cout << "Test case 1:" << endl;
    cout << "Grid:" << endl;
    printGrid(grid1);
    
    vector<vector<int>> grid1_copy = grid1; // Make a copy for the function
    int result1 = uniquePathsIII(grid1_copy);
    cout << "Output: " << result1 << endl;
    cout << "Expected: 2" << endl;
    cout << endl;
    
    // Test case 2
    vector<vector<int>> grid2 = {
        {1, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 2}
    };
    
    cout << "Test case 2:" << endl;
    cout << "Grid:" << endl;
    printGrid(grid2);
    
    vector<vector<int>> grid2_copy = grid2;
    int result2 = uniquePathsIII(grid2_copy);
    cout << "Output: " << result2 << endl;
    cout << "Expected: 4" << endl;
    cout << endl;
    
    // Test case 3
    vector<vector<int>> grid3 = {
        {0, 1},
        {2, 0}
    };
    
    cout << "Test case 3:" << endl;
    cout << "Grid:" << endl;
    printGrid(grid3);
    
    vector<vector<int>> grid3_copy = grid3;
    int result3 = uniquePathsIII(grid3_copy);
    cout << "Output: " << result3 << endl;
    cout << "Expected: 0" << endl;
    cout << endl;
    
    return 0;
}

