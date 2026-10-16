/**
 * Problem: Minimum time required to rot all oranges (Rotten Oranges)
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Simple 1D queue manipulations handled sequential stream ordering.
 * - Here, we perform Multi-Source Breadth-First Search (BFS) over a 2D grid where multiple infection
 *   sources spread simultaneously in parallel level-by-level (minute-by-minute).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Multi-Source BFS Queue:
 *   - Why not DFS? DFS explores deeply along one path, which does NOT calculate the simultaneous
 *     shortest time of infection across multiple independent sources.
 *   - Enqueue all initially rotten oranges (cells with value 2) and count initial fresh oranges (cells with value 1).
 *   - In each BFS time-step:
 *     - Expand the entire current frontier of the queue across the 4 cardinal directions (Up, Down, Left, Right).
 *     - Convert fresh oranges (1 -> 2), decrement fresh count, and enqueue newly infected cells.
 *   - Stop when the queue is exhausted. If `freshCount == 0`, return `timeElapsed`; else return -1.
 * 
 * TIME COMPLEXITY:
 * - O(R * C): Every cell is visited at most once.
 * 
 * SPACE COMPLEXITY:
 * - O(R * C) in worst case for the BFS queue.
 */

#include <iostream>
#include <vector>
#include <queue>

int orangesRotting(std::vector<std::vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    std::queue<std::pair<int, int>> q;
    int fresh = 0;

    // Step 1: Collect all initial rotten oranges and count fresh ones
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 2) {
                q.push({r, c});
            } else if (grid[r][c] == 1) {
                fresh++;
            }
        }
    }

    if (fresh == 0) return 0; // No fresh oranges to rot

    int minutes = 0;
    int dRow[] = {-1, 1, 0, 0};
    int dCol[] = {0, 0, -1, 1};

    // Step 2: Multi-source BFS
    while (!q.empty()) {
        int sz = q.size();
        bool rottedAny = false;

        for (int i = 0; i < sz; i++) {
            auto [r, c] = q.front();
            q.pop();

            for (int d = 0; d < 4; d++) {
                int nr = r + dRow[d];
                int nc = c + dCol[d];

                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Simultaneously infect adjacent fresh oranges in parallel and push into the next minute layer.
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == 1) {
                    grid[nr][nc] = 2; // Rot the orange
                    fresh--;
                    rottedAny = true;
                    q.push({nr, nc});
                }
            }
        }

        if (rottedAny) minutes++;
    }

    return (fresh == 0) ? minutes : -1;
}

int main() {
    std::vector<std::vector<int>> grid = {
        {2, 1, 1},
        {1, 1, 0},
        {0, 1, 1}
    };

    std::cout << "Time required: " << orangesRotting(grid) << " minutes\n"; // 4

    return 0;
}
