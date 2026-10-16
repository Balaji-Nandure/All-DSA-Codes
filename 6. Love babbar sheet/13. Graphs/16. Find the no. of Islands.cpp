/**
 * Problem: Find the Number of Islands
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Flood fill changes pixel colors; here, we must partition the 2D binary matrix into disconnected connected components (islands).
 * - In classic GFG problem definitions, an island is formed by horizontally, vertically, and DIAGONALLY adjacent '1's (8 directions).
 * - Sinking the land (mutating '1' to '0') or tracking visited cells avoids counting the same island multiple times.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - 8-Directional DFS Component Sinking:
 *   - Iterate through every cell `(r, c)` of the `N x M` grid.
 *   - If `grid[r][c] == '1'`, we have discovered a new unvisited island:
 *     - Increment `islandCount`.
 *     - Launch DFS/BFS starting from `(r, c)`.
 *     - During DFS, sink `grid[r][c] = '0'` and explore all 8 adjacent neighbors.
 *   - By sinking the land in-place, we eliminate the need for an extra 2D visited boolean matrix, achieving O(1) auxiliary space outside the call stack.
 * 
 * TIME COMPLEXITY:
 * - O(N * M): Every cell is visited at most a constant number of times.
 * 
 * SPACE COMPLEXITY:
 * - O(N * M) for the maximum DFS recursion stack depth in worst case (grid full of 1s).
 */

#include <iostream>
#include <vector>

class Solution {
    int n, m;

    void dfsSink(int r, int c, std::vector<std::vector<char>>& grid) {
        if (r < 0 || r >= n || c < 0 || c >= m || grid[r][c] != '1') {
            return;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Sink the current land cell to '0' to prevent revisiting without allocating extra memory.
        grid[r][c] = '0';

        // 8-directional offsets (horizontally, vertically, diagonally)
        int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

        for (int i = 0; i < 8; i++) {
            dfsSink(r + dr[i], c + dc[i], grid);
        }
    }

public:
    int numIslands(std::vector<std::vector<char>>& grid) {
        n = grid.size();
        if (n == 0) return 0;
        m = grid[0].size();

        int islandCount = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '1') {
                    islandCount++;
                    dfsSink(i, j, grid);
                }
            }
        }
        return islandCount;
    }
};

int main() {
    std::vector<std::vector<char>> grid = {
        {'0', '1', '1', '1', '0', '0', '0'},
        {'0', '0', '1', '1', '0', '1', '0'}
    };

    Solution sol;
    int count = sol.numIslands(grid);
    std::cout << "Number of islands (8-directional): " << count << "\n"; // Expected: 2

    return 0;
}
