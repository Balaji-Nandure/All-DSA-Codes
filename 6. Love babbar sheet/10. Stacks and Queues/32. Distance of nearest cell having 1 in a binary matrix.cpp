/**
 * Problem: Distance of nearest cell having 1 in a binary matrix
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Starting a separate BFS from every cell having 0 to search for a 1 would cost O((N*M)^2) time.
 * - By reversing the perspective—running a SINGLE multi-source BFS starting simultaneously from ALL cells containing 1—
 *   we compute all nearest distances across the entire matrix in linear O(N * M) time.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Reverse Multi-Source BFS:
 *   - Initialize a distance matrix `dist[N][M]` with -1.
 *   - Enqueue all cells `(r, c)` where `grid[r][c] == 1` with `dist[r][c] = 0`.
 *   - While queue is not empty:
 *     - Pop current cell `(r, c)`.
 *     - For each of the 4 adjacent neighbors `(nr, nc)`:
 *       - If `dist[nr][nc] == -1` (unvisited):
 *         - `dist[nr][nc] = dist[r][c] + 1`.
 *         - Enqueue `(nr, nc)`.
 *   - Guaranteed shortest Manhattan distance due to uniform edge weights in BFS.
 * 
 * TIME COMPLEXITY:
 * - O(N * M): Every cell is processed at most once.
 * 
 * SPACE COMPLEXITY:
 * - O(N * M) for the queue and distance matrix.
 */

#include <iostream>
#include <vector>
#include <queue>

std::vector<std::vector<int>> nearest(const std::vector<std::vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    std::vector<std::vector<int>> dist(n, std::vector<int>(m, -1));
    std::queue<std::pair<int, int>> q;

    // Enqueue all cells containing 1
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1) {
                dist[i][j] = 0;
                q.push({i, j});
            }
        }
    }

    int dRow[] = {-1, 1, 0, 0};
    int dCol[] = {0, 0, -1, 1};

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        for (int k = 0; k < 4; k++) {
            int nr = r + dRow[k];
            int nc = c + dCol[k];

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Unvisited cell inherits shortest distance from its BFS predecessor (+1).
            if (nr >= 0 && nr < n && nc >= 0 && nc < m && dist[nr][nc] == -1) {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }

    return dist;
}

int main() {
    std::vector<std::vector<int>> grid = {
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 1, 1}
    };

    std::vector<std::vector<int>> ans = nearest(grid);

    std::cout << "Distance to nearest 1:\n";
    for (const auto& row : ans) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
