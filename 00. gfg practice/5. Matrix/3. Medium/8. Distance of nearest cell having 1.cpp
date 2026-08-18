/*
    Problem Name: Distance of nearest cell having 1
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a binary grid[][] of size n x m, where each cell contains either 0 or 1, find the
    distance of the nearest 1 for every cell in the grid.
    The distance between two cells (i1, j1) and (i2, j2) is calculated as |i1 - i2| + |j1 - j2|.
    Return a matrix of the same size, where each cell (i, j) contains the minimum distance from
    grid[i][j] to the nearest cell having value 1.

    Note: For cells having value 1, distance to nearest 1 is 0.

    Examples:
    Input: grid[][] = [[0, 1, 1, 0],
                       [1, 1, 0, 0],
                       [0, 0, 1, 1]]
    Output: [[1, 0, 0, 1],
             [0, 0, 1, 1],
             [1, 1, 0, 0]]

    Input: grid[][] = [[1, 0, 1],
                       [1, 1, 0],
                       [1, 0, 0]]
    Output: [[0, 1, 0],
             [0, 0, 1],
             [0, 1, 2]]

    Constraints:
    1 <= n, m <= 200
    grid[i][j] = {0, 1}

    Expected Complexities:
    Time Complexity: O(N * M), single pass Multi-Source BFS / 2-Pass DP.
    Space Complexity: O(N * M), for BFS Queue / Distance output matrix.

    Approach 1: Multi-Source BFS (Optimal O(N * M) - Striver & Love Babbar)
    Approach 2: 2-Pass Dynamic Programming (O(N * M) - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Multi-Source BFS (Approach 1):
       - Since we want the distance of every 0 cell to the NEAREST 1 cell, we can invert the search:
         * Push ALL cells containing 1 into a `queue<pair<int, int>>` at time 0 (`dist[i][j] = 0`).
         * Perform Multi-Source BFS expanding level-by-level in 4 directions.
         * The first time a 0-cell is reached via BFS, its assigned distance is guaranteed to be minimal!
    2. 2-Pass Dynamic Programming (Approach 2):
       - Pass 1 (Top-Left to Bottom-Right): Compute minimum distance checking Top and Left neighbours.
       - Pass 2 (Bottom-Right to Top-Left): Refine minimum distance checking Bottom and Right neighbours.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// ============================================================================
// Approach 1: Multi-Source BFS (Optimal O(N * M) - Striver & Love Babbar Style)
// ============================================================================
class SolutionBFS {
public:
    vector<vector<int>> nearest(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        queue<pair<int, int>> q;
        vector<vector<int>> dist(n, vector<int>(m, -1));

        // Step 1: Push all cells containing 1 into queue with distance 0
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    dist[i][j] = 0;
                    q.push({i, j});
                }
            }
        }

        int delRow[] = {-1, 1, 0, 0};
        int delCol[] = {0, 0, -1, 1};

        // Step 2: Multi-Source BFS level-by-level
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (int i = 0; i < 4; i++) {
                int nr = r + delRow[i];
                int nc = c + delCol[i];

                if (nr >= 0 && nr < n && nc >= 0 && nc < m && dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }

        return dist;
    }
};

// ============================================================================
// Approach 2: 2-Pass Dynamic Programming (O(N * M) - Striver & Love Babbar Style)
// ============================================================================
class SolutionDP {
public:
    vector<vector<int>> nearest(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        int INF = n + m; // Maximum possible Manhattan distance

        vector<vector<int>> dist(n, vector<int>(m, INF));

        // Pass 1: Top-Left to Bottom-Right (Check Top and Left neighbours)
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    dist[i][j] = 0;
                } else {
                    if (i > 0) dist[i][j] = min(dist[i][j], dist[i - 1][j] + 1);
                    if (j > 0) dist[i][j] = min(dist[i][j], dist[i][j - 1] + 1);
                }
            }
        }

        // Pass 2: Bottom-Right to Top-Left (Check Bottom and Right neighbours)
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                if (i < n - 1) dist[i][j] = min(dist[i][j], dist[i + 1][j] + 1);
                if (j < m - 1) dist[i][j] = min(dist[i][j], dist[i][j + 1] + 1);
            }
        }

        return dist;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    vector<vector<int>> nearest(vector<vector<int>>& grid) {
        SolutionBFS solver;
        return solver.nearest(grid);
    }
};

// Helper function to print matrix
void printMatrix(const vector<vector<int>>& mat) {
    for (const auto& row : mat) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << "\n";
    }
}

int main() {
    // Example 1:
    vector<vector<int>> grid1 = {
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 1, 1}
    };

    SolutionBFS bfsSolver;
    vector<vector<int>> res1 = bfsSolver.nearest(grid1);
    cout << "Example 1 Output (Multi-Source BFS):\n";
    printMatrix(res1);
    cout << "\n";

    // Example 2:
    vector<vector<int>> grid2 = {
        {1, 0, 1},
        {1, 1, 0},
        {1, 0, 0}
    };

    SolutionDP dpSolver;
    vector<vector<int>> res2 = dpSolver.nearest(grid2);
    cout << "Example 2 Output (2-Pass DP):\n";
    printMatrix(res2);

    return 0;
}
