/*
    Problem Name: Replace O's with X's (Surrounded Regions)
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a matrix grid[][] of size n x m, where every element is either 'O' or 'X'.
    Replace all 'O' or connected groups of 'O' with 'X' if they are completely surrounded by 'X'.
    - An 'O' (or connected group of 'O's) is surrounded by 'X' if none of its 'O's touch the matrix boundary.

    Examples:
    Input: grid[][] = [['X', 'X', 'X', 'X'],
                       ['X', 'O', 'X', 'X'],
                       ['X', 'O', 'O', 'X'],
                       ['X', 'O', 'X', 'X'],
                       ['X', 'X', 'O', 'O']]
    Output: [['X', 'X', 'X', 'X'],
             ['X', 'O', 'X', 'X'],
             ['X', 'O', 'O', 'X'],
             ['X', 'O', 'X', 'X'],
             ['X', 'X', 'O', 'O']]
    Explanation: All 'O's are connected to the boundary 'O's at the bottom row, so none are surrounded.

    Input: grid[][] = [['X', 'X', 'X'],
                       ['X', 'O', 'X'],
                       ['X', 'X', 'X']]
    Output: [['X', 'X', 'X'],
             ['X', 'X', 'X'],
             ['X', 'X', 'X']]
    Explanation: The center 'O' is completely surrounded by 'X' and is replaced by 'X'.

    Constraints:
    1 <= n, m <= 100
    grid[i][j] = {'X', 'O'}

    Expected Complexities:
    Time Complexity: O(N * M), traversing each cell a constant number of times.
    Space Complexity: O(N * M), for visited matrix / queue / call stack.

    Approach 1: Boundary DFS (Depth First Search - Striver & Love Babbar)
    Approach 2: Boundary BFS (Breadth First Search - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Inverse Problem Analysis:
       - Any 'O' on the matrix boundary (row 0, row n-1, col 0, col m-1) CANNOT be surrounded by 'X'.
       - Any 'O' connected 4-directionally to a boundary 'O' CANNOT be surrounded by 'X'.
       - Therefore, starting from all boundary 'O's, we perform a traversal (DFS or BFS) to mark all
         boundary-connected 'O's as visited.
    2. Final Update:
       - Iterate through all cells `(i, j)`:
         * If `grid[i][j] == 'O'` and NOT visited -> it is completely surrounded by 'X' -> Change to 'X'.
         * Otherwise -> Keep as 'O'.
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// ============================================================================
// Approach 1: Boundary DFS (Depth First Search - Striver & Love Babbar Style)
// ============================================================================
class SolutionDFS {
private:
    void dfs(int r, int c, vector<vector<char>>& grid, vector<vector<bool>>& vis, int delRow[], int delCol[], int n, int m) {
        vis[r][c] = true;

        for (int i = 0; i < 4; i++) {
            int nr = r + delRow[i];
            int nc = c + delCol[i];

            if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] == 'O' && !vis[nr][nc]) {
                dfs(nr, nc, grid, vis, delRow, delCol, n, m);
            }
        }
    }

public:
    vector<vector<char>> fill(vector<vector<char>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        vector<vector<bool>> vis(n, vector<bool>(m, false));
        int delRow[] = {-1, 1, 0, 0};
        int delCol[] = {0, 0, -1, 1};

        // Step 1: Traverse Top & Bottom boundaries
        for (int j = 0; j < m; j++) {
            if (grid[0][j] == 'O' && !vis[0][j]) {
                dfs(0, j, grid, vis, delRow, delCol, n, m);
            }
            if (grid[n - 1][j] == 'O' && !vis[n - 1][j]) {
                dfs(n - 1, j, grid, vis, delRow, delCol, n, m);
            }
        }

        // Step 2: Traverse Left & Right boundaries
        for (int i = 0; i < n; i++) {
            if (grid[i][0] == 'O' && !vis[i][0]) {
                dfs(i, 0, grid, vis, delRow, delCol, n, m);
            }
            if (grid[i][m - 1] == 'O' && !vis[i][m - 1]) {
                dfs(i, m - 1, grid, vis, delRow, delCol, n, m);
            }
        }

        // Step 3: Replace unvisited 'O's with 'X'
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 'O' && !vis[i][j]) {
                    grid[i][j] = 'X';
                }
            }
        }

        return grid;
    }
};

// ============================================================================
// Approach 2: Boundary BFS (Breadth First Search - Striver & Love Babbar Style)
// ============================================================================
class SolutionBFS {
public:
    vector<vector<char>> fill(vector<vector<char>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        queue<pair<int, int>> q;
        vector<vector<bool>> vis(n, vector<bool>(m, false));

        // Step 1: Push all boundary 'O's into BFS Queue
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
                    if (grid[i][j] == 'O') {
                        q.push({i, j});
                        vis[i][j] = true;
                    }
                }
            }
        }

        int delRow[] = {-1, 1, 0, 0};
        int delCol[] = {0, 0, -1, 1};

        // Step 2: Multi-source BFS from boundary 'O's
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (int i = 0; i < 4; i++) {
                int nr = r + delRow[i];
                int nc = c + delCol[i];

                if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] == 'O' && !vis[nr][nc]) {
                    vis[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }

        // Step 3: Replace unvisited 'O's with 'X'
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 'O' && !vis[i][j]) {
                    grid[i][j] = 'X';
                }
            }
        }

        return grid;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    vector<vector<char>> fill(vector<vector<char>>& grid) {
        SolutionDFS solver;
        return solver.fill(grid);
    }
};

// Helper function to print grid
void printGrid(const vector<vector<char>>& grid) {
    for (const auto& row : grid) {
        for (char ch : row) {
            cout << ch << " ";
        }
        cout << "\n";
    }
}

int main() {
    // Example 1:
    vector<vector<char>> grid1 = {
        {'X', 'X', 'X', 'X'},
        {'X', 'O', 'X', 'X'},
        {'X', 'O', 'O', 'X'},
        {'X', 'O', 'X', 'X'},
        {'X', 'X', 'O', 'O'}
    };

    SolutionDFS dfsSolver;
    vector<vector<char>> res1 = dfsSolver.fill(grid1);
    cout << "Example 1 Output (DFS):\n";
    printGrid(res1);
    cout << "\n";

    // Example 2:
    vector<vector<char>> grid2 = {
        {'X', 'X', 'X'},
        {'X', 'O', 'X'},
        {'X', 'X', 'X'}
    };

    SolutionBFS bfsSolver;
    vector<vector<char>> res2 = bfsSolver.fill(grid2);
    cout << "Example 2 Output (BFS):\n";
    printGrid(res2);

    return 0;
}
