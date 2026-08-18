/*
    Problem Name: Check for Path in a 2D Grid with Obstacles
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a grid mat[][] of size n x n containing integers 0, 1, 2, and 3 having the following meanings:
    - 1 represents the source cell (exactly one source)
    - 2 represents the destination cell (exactly one destination)
    - 3 represents a blank cell through which movement is allowed
    - 0 represents a wall/obstacle that cannot be traversed

    Find whether a path exists from the source cell (1) to the destination cell (2).
    Movement is allowed in four directions: Up, Down, Left, and Right.

    Examples:
    Input: mat[][] = {{0, 3, 1, 0},
                      {3, 0, 3, 3},
                      {2, 3, 0, 3},
                      {0, 3, 3, 3}}
    Output: true
    Explanation: A valid path exists from 1 at (0,2) to 2 at (2,0) via blank cells 3.

    Input: mat[][] = {{1, 0, 3},
                      {0, 0, 0},
                      {3, 3, 2}}
    Output: false
    Explanation: Source 1 at (0,0) is blocked by walls (0 cells).

    Constraints:
    1 <= n <= 500
    mat[i][j] = {0, 1, 2, 3}

    Expected Complexities:
    Time Complexity: O(N^2), where N is the dimension of the square matrix.
    Space Complexity: O(N^2), for visited matrix / queue / recursion call stack.

    Approach 1: BFS Traversal (Iterative Queue - Striver & Love Babbar)
    Approach 2: DFS Traversal (Recursive Stack - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Locate the single source cell (value 1) at `(sr, sc)`.
    2. Starting from `(sr, sc)`, explore the grid using BFS or DFS traversal.
    3. From cell `(r, c)`, move to 4-directional neighbours `(nr, nc)`:
       - Valid cell condition: `nr` and `nc` inside grid bounds, `!visited[nr][nc]`, and `grid[nr][nc] != 0`.
       - If `grid[nr][nc] == 2`: Destination reached -> Return `true` immediately.
       - If `grid[nr][nc] == 3`: Mark visited and continue exploring.
    4. If traversal finishes without reaching value 2, return `false`.
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// ============================================================================
// Approach 1: BFS Traversal (Iterative Queue - Striver & Love Babbar Style)
// ============================================================================
class SolutionBFS {
public:
    bool is_Possible(vector<vector<int>>& grid) {
        int n = grid.size();
        int sr = -1, sc = -1;

        // Step 1: Find the source cell (value 1)
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    sr = i;
                    sc = j;
                    break;
                }
            }
            if (sr != -1) break;
        }

        if (sr == -1) return false;

        queue<pair<int, int>> q;
        vector<vector<bool>> vis(n, vector<bool>(n, false));

        q.push({sr, sc});
        vis[sr][sc] = true;

        int delRow[] = {-1, 1, 0, 0};
        int delCol[] = {0, 0, -1, 1};

        // Step 2: BFS Exploration
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (int i = 0; i < 4; i++) {
                int nr = r + delRow[i];
                int nc = c + delCol[i];

                if (nr >= 0 && nr < n && nc >= 0 && nc < n && !vis[nr][nc]) {
                    if (grid[nr][nc] == 2) {
                        return true; // Destination reached
                    }
                    if (grid[nr][nc] == 3) {
                        vis[nr][nc] = true;
                        q.push({nr, nc});
                    }
                }
            }
        }

        return false; // Destination unreachable
    }
};

// ============================================================================
// Approach 2: DFS Traversal (Recursive Stack - Striver & Love Babbar Style)
// ============================================================================
class SolutionDFS {
private:
    bool dfs(int r, int c, vector<vector<int>>& grid, vector<vector<bool>>& vis, int delRow[], int delCol[], int n) {
        vis[r][c] = true;

        // If destination cell reached
        if (grid[r][c] == 2) {
            return true;
        }

        for (int i = 0; i < 4; i++) {
            int nr = r + delRow[i];
            int nc = c + delCol[i];

            if (nr >= 0 && nr < n && nc >= 0 && nc < n && !vis[nr][nc]) {
                if (grid[nr][nc] == 3 || grid[nr][nc] == 2) {
                    if (dfs(nr, nc, grid, vis, delRow, delCol, n)) {
                        return true;
                    }
                }
            }
        }

        return false;
    }

public:
    bool is_Possible(vector<vector<int>>& grid) {
        int n = grid.size();
        int sr = -1, sc = -1;

        // Find source cell (value 1)
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    sr = i;
                    sc = j;
                    break;
                }
            }
            if (sr != -1) break;
        }

        if (sr == -1) return false;

        vector<vector<bool>> vis(n, vector<bool>(n, false));
        int delRow[] = {-1, 1, 0, 0};
        int delCol[] = {0, 0, -1, 1};

        return dfs(sr, sc, grid, vis, delRow, delCol, n);
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    bool is_Possible(vector<vector<int>>& grid) {
        SolutionBFS solver;
        return solver.is_Possible(grid);
    }
};

int main() {
    // Example 1:
    // Expected Output: true
    vector<vector<int>> mat1 = {
        {0, 3, 1, 0},
        {3, 0, 3, 3},
        {2, 3, 0, 3},
        {0, 3, 3, 3}
    };

    SolutionBFS bfsSolver;
    cout << "Example 1 Path Exists (BFS): " << (bfsSolver.is_Possible(mat1) ? "true" : "false") << "\n";

    // Example 2:
    // Expected Output: false
    vector<vector<int>> mat2 = {
        {1, 0, 3},
        {0, 0, 0},
        {3, 3, 2}
    };

    SolutionDFS dfsSolver;
    cout << "Example 2 Path Exists (DFS): " << (dfsSolver.is_Possible(mat2) ? "true" : "false") << "\n";

    return 0;
}
