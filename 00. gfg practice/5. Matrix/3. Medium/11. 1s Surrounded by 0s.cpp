/*
    Problem Name: 1s Surrounded by 0s (Number of Enclaves)
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given an n x m binary matrix grid[][], find the total count of all cells containing 1 that are
    unable to move out of the grid through a path of adjacent 1s.
    - Movement is allowed in 4 directions: Up, Down, Left, Right.
    - Any 1 located directly on the outer boundary of the grid can step out.
    - Any 1 connected 4-directionally to a boundary 1 can also step out.

    Examples:
    Input: grid[][] = [[0, 0, 0, 0],
                       [1, 0, 1, 0],
                       [0, 1, 1, 0],
                       [0, 0, 0, 0]]
    Output: 3
    Explanation: The 1 at (1,0) is on the boundary. The 3 land cells at (1,2), (2,1), (2,2) cannot reach the boundary.

    Input: grid[][] = [[1, 1, 0, 0, 0, 1],
                       [0, 1, 1, 0, 1, 0],
                       [0, 0, 0, 1, 1, 0],
                       [0, 0, 0, 1, 1, 0],
                       [0, 1, 0, 1, 0, 0],
                       [1, 1, 0, 0, 0, 1]]
    Output: 6

    Constraints:
    1 <= n, m <= 500
    grid[i][j] = {0, 1}

    Expected Complexities:
    Time Complexity: O(N * M), traversing each cell a constant number of times.
    Space Complexity: O(N * M), for visited matrix / queue / call stack.

    Approach 1: Boundary Multi-Source BFS (Optimal O(N * M) - Striver & Love Babbar)
    Approach 2: Boundary DFS Traversal (O(N * M) - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Inverse Traversal Strategy:
       - Instead of finding enclosed 1s directly, identify all 1s that CAN reach the boundary.
       - Any 1 on the outer boundary (row 0, row n-1, col 0, col m-1) can reach the outside.
       - Any 1 connected to a boundary 1 can also reach the outside.
    2. Execution Steps:
       - Perform BFS / DFS starting from ALL boundary cells that contain 1.
       - Mark all reachable 1 cells as `visited`.
       - Count all 1 cells in the grid that remain UNVISITED.
       - Return this count as the answer!
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// ============================================================================
// Approach 1: Boundary Multi-Source BFS (Striver & Love Babbar Style)
// ============================================================================
class SolutionBFS {
public:
    int numberOfEnclaves(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        queue<pair<int, int>> q;
        vector<vector<bool>> vis(n, vector<bool>(m, false));

        // Step 1: Push all boundary 1s into BFS Queue
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
                    if (grid[i][j] == 1) {
                        q.push({i, j});
                        vis[i][j] = true;
                    }
                }
            }
        }

        int delRow[] = {-1, 1, 0, 0};
        int delCol[] = {0, 0, -1, 1};

        // Step 2: Multi-source BFS to mark all boundary-connected 1s
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (int i = 0; i < 4; i++) {
                int nr = r + delRow[i];
                int nc = c + delCol[i];

                if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] == 1 && !vis[nr][nc]) {
                    vis[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }

        // Step 3: Count enclosed 1s (unvisited 1s)
        int enclosedCount = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1 && !vis[i][j]) {
                    enclosedCount++;
                }
            }
        }

        return enclosedCount;
    }
};

// ============================================================================
// Approach 2: Boundary DFS Traversal (Striver & Love Babbar Style)
// ============================================================================
class SolutionDFS {
private:
    void dfs(int r, int c, vector<vector<int>>& grid, vector<vector<bool>>& vis, int delRow[], int delCol[], int n, int m) {
        vis[r][c] = true;

        for (int i = 0; i < 4; i++) {
            int nr = r + delRow[i];
            int nc = c + delCol[i];

            if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] == 1 && !vis[nr][nc]) {
                dfs(nr, nc, grid, vis, delRow, delCol, n, m);
            }
        }
    }

public:
    int numberOfEnclaves(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        vector<vector<bool>> vis(n, vector<bool>(m, false));
        int delRow[] = {-1, 1, 0, 0};
        int delCol[] = {0, 0, -1, 1};

        // Step 1: Traverse Top and Bottom boundaries
        for (int j = 0; j < m; j++) {
            if (grid[0][j] == 1 && !vis[0][j]) {
                dfs(0, j, grid, vis, delRow, delCol, n, m);
            }
            if (grid[n - 1][j] == 1 && !vis[n - 1][j]) {
                dfs(n - 1, j, grid, vis, delRow, delCol, n, m);
            }
        }

        // Step 2: Traverse Left and Right boundaries
        for (int i = 0; i < n; i++) {
            if (grid[i][0] == 1 && !vis[i][0]) {
                dfs(i, 0, grid, vis, delRow, delCol, n, m);
            }
            if (grid[i][m - 1] == 1 && !vis[i][m - 1]) {
                dfs(i, m - 1, grid, vis, delRow, delCol, n, m);
            }
        }

        // Step 3: Count enclosed 1s (unvisited 1s)
        int enclosedCount = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1 && !vis[i][j]) {
                    enclosedCount++;
                }
            }
        }

        return enclosedCount;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    // Function signature: cntOnes or numberOfEnclaves
    int cntOnes(vector<vector<int>>& grid) {
        SolutionBFS solver;
        return solver.numberOfEnclaves(grid);
    }

    int numberOfEnclaves(vector<vector<int>>& grid) {
        return cntOnes(grid);
    }
};

int main() {
    // Example 1:
    // Expected Output: 3
    vector<vector<int>> grid1 = {
        {0, 0, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    };

    SolutionBFS bfsSolver;
    cout << "Example 1 Enclosed 1s Count (BFS): " << bfsSolver.numberOfEnclaves(grid1) << "\n";

    // Example 2:
    // Expected Output: 6
    vector<vector<int>> grid2 = {
        {1, 1, 0, 0, 0, 1},
        {0, 1, 1, 0, 1, 0},
        {0, 0, 0, 1, 1, 0},
        {0, 0, 0, 1, 1, 0},
        {0, 1, 0, 1, 0, 0},
        {1, 1, 0, 0, 0, 1}
    };

    SolutionDFS dfsSolver;
    cout << "Example 2 Enclosed 1s Count (DFS): " << dfsSolver.numberOfEnclaves(grid2) << "\n";

    return 0;
}
