// Problem: 1020. Number of Enclaves
// Link (LeetCode): https://leetcode.com/problems/number-of-enclaves/
// Link (GFG): https://www.geeksforgeeks.org/problems/number-of-enclaves/1
// Difficulty: Medium
// Topic: DFS, BFS, Matrix, Graph, Flood Fill

/*
Problem Statement:
You are given an m x n binary matrix grid, where 0 represents a sea cell and 1 represents a land cell.

A move consists of walking from one land cell to another adjacent (4-directionally) land cell 
or walking off the boundary of the grid.

Return the number of land cells in grid for which we cannot walk off the boundary of the grid in any number of moves.

Example 1:
Input: grid = [[0,0,0,0],
               [1,0,1,0],
               [0,1,1,0],
               [0,0,0,0]]
Output: 3
Explanation: 
- There are three 1s in the interior that cannot walk off the boundary.
- The 1 at grid[1][0] is on the boundary, so it can walk off the grid.

Example 2:
Input: grid = [[0,1,1,0],
               [0,0,1,0],
               [0,0,1,0],
               [0,0,0,0]]
Output: 0
Explanation: 
- All 1s are either on the boundary or directly connected to a boundary 1, 
  so all can walk off the boundary.

Constraints:
- m == grid.length
- n == grid[i].length
- 1 <= m, n <= 500
- grid[i][j] is either 0 or 1.
*/

// Approach: Boundary Flood Fill (Inverse Thinking)
// 1. Identify Escapable Land: Any land cell (1) that touches the boundary can escape off the grid.
//    Any land cell connected to a boundary land cell can also escape off the grid.
// 2. Traverse all boundary cells (first/last row, first/last column). If a cell contains 1:
//    - Trigger DFS or BFS to traverse and "sink" (change 1 -> 0) all connected land cells.
// 3. Count Enclaves: After sinking all boundary-connected components, any remaining 1s in the matrix
//    are completely trapped/enclosed by water (0s) and cannot reach any boundary.
// 4. Sum up or count all remaining 1s.

#include <bits/stdc++.h>
using namespace std;

// Approach 1: In-place DFS (Optimal & Clean)
class Solution {
private:
    void dfs(int r, int c, vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // Base conditions: Out of bounds or water cell (0)
        if (r < 0 || c < 0 || r >= m || c >= n || grid[r][c] == 0) {
            return;
        }

        // Sink current land cell (mark as visited by changing 1 -> 0)
        grid[r][c] = 0;

        // Traverse 4 directions
        dfs(r + 1, c, grid); // Down
        dfs(r - 1, c, grid); // Up
        dfs(r, c + 1, grid); // Right
        dfs(r, c - 1, grid); // Left
    }

public:
    int numEnclaves(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;

        int m = grid.size();
        int n = grid[0].size();

        // Step 1: Traverse the boundary rows (first and last column)
        for (int i = 0; i < m; i++) {
            if (grid[i][0] == 1) dfs(i, 0, grid);
            if (grid[i][n - 1] == 1) dfs(i, n - 1, grid);
        }

        // Step 2: Traverse the boundary columns (first and last row)
        for (int j = 0; j < n; j++) {
            if (grid[0][j] == 1) dfs(0, j, grid);
            if (grid[m - 1][j] == 1) dfs(m - 1, j, grid);
        }

        // Step 3: Count remaining interior land cells (enclaves)
        int count = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                count += grid[i][j];
            }
        }

        return count;
    }
};

// Approach 2: BFS Approach (Alternative using Queue)
class SolutionBFS {
public:
    int numEnclaves(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;

        int m = grid.size();
        int n = grid[0].size();
        queue<pair<int, int>> q;

        // Step 1: Add all boundary land cells to queue and mark as 0
        for (int i = 0; i < m; i++) {
            if (grid[i][0] == 1) { grid[i][0] = 0; q.push({i, 0}); }
            if (grid[i][n - 1] == 1) { grid[i][n - 1] = 0; q.push({i, n - 1}); }
        }
        for (int j = 0; j < n; j++) {
            if (grid[0][j] == 1) { grid[0][j] = 0; q.push({0, j}); }
            if (grid[m - 1][j] == 1) { grid[m - 1][j] = 0; q.push({m - 1, j}); }
        }

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        // Step 2: BFS to sink all connected boundary land
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                    grid[nr][nc] = 0;
                    q.push({nr, nc});
                }
            }
        }

        // Step 3: Count surviving enclosed land cells
        int count = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                count += grid[i][j];
            }
        }

        return count;
    }
};

/*
Time Complexity: O(M * N)
- Traversing the boundary cells takes O(M + N).
- DFS / BFS visits each connected cell at most once: O(M * N).
- Counting the surviving cells visits each cell once: O(M * N).
- Overall Time Complexity: O(M * N)

Space Complexity:
- DFS Recursion Stack: O(M * N) in the worst case (all land cells).
- BFS Queue: O(M * N) in the worst case.
- Auxiliary Space: O(1) because we sink cells in-place (1 -> 0) without needing extra visited matrix.

Key Insights:
1. Similar to "130. Surrounded Regions", this problem is best solved by eliminating boundary-connected
   components first rather than checking each interior cell to see if it escapes.
2. In-place sinking (changing 1 to 0) acts as both marking visited and eliminating escapable cells,
   which reduces space complexity to O(1) auxiliary.
*/
