/**
 * Problem: Search in a Maze (Rat in a Maze Problem)
 * Category: Graphs / Backtracking
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In standard BFS/DFS, finding any path was sufficient and visited nodes were marked permanently.
 * - Here, we must discover ALL VALID PATHS from `(0, 0)` to `(N - 1, N - 1)` in lexicographically sorted
 *   order ('D', 'L', 'R', 'U'), requiring backtracking (unmarking visited cells).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Grid DFS with Lexicographical Direction Order:
 *   - Move in sorted order: Down ('D'), Left ('L'), Right ('R'), Up ('U').
 *   - Base condition: If `(r == N - 1 && c == N - 1)`, append current path string to result.
 *   - At each cell `(r, c)`:
 *     - If `(r, c)` is out of bounds, blocked (`maze[r][c] == 0`), or already in current path (`visited[r][c]`): return.
 *     - Mark cell visited: `visited[r][c] = 1`.
 *     - Explore in order: D, L, R, U.
 *     - Backtrack: `visited[r][c] = 0` to allow other viable paths to traverse through `(r, c)`.
 * 
 * TIME COMPLEXITY:
 * - O(4^(N^2)): Upper bounded by all branching paths through an N x N maze.
 * 
 * SPACE COMPLEXITY:
 * - O(N^2) recursion stack and visited matrix.
 */

#include <iostream>
#include <vector>
#include <string>

void solveMaze(int r, int c, const std::vector<std::vector<int>>& m, int n,
               std::vector<std::vector<bool>>& visited, std::string path, std::vector<std::string>& ans) {
    if (r == n - 1 && c == n - 1) {
        ans.push_back(path);
        return;
    }

    // Direction arrays in lexicographical order: D, L, R, U
    int dr[] = {1, 0, 0, -1};
    int dc[] = {0, -1, 1, 0};
    char dir[] = {'D', 'L', 'R', 'U'};

    visited[r][c] = true;

    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Move in sorted order D, L, R, U ensuring paths are naturally generated in lexicographical order.
        if (nr >= 0 && nr < n && nc >= 0 && nc < n && m[nr][nc] == 1 && !visited[nr][nc]) {
            solveMaze(nr, nc, m, n, visited, path + dir[i], ans);
        }
    }

    // Backtrack to unblock cell for other paths
    visited[r][c] = false;
}

std::vector<std::string> findPath(std::vector<std::vector<int>>& m, int n) {
    std::vector<std::string> ans;
    if (m[0][0] == 0 || m[n - 1][n - 1] == 0) return ans;

    std::vector<std::vector<bool>> visited(n, std::vector<bool>(n, false));
    solveMaze(0, 0, m, n, visited, "", ans);

    return ans;
}

int main() {
    std::vector<std::vector<int>> maze = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {1, 1, 0, 0},
        {0, 1, 1, 1}
    };
    int n = 4;

    std::vector<std::string> paths = findPath(maze, n);
    std::cout << "Valid paths: ";
    for (const std::string& p : paths) {
        std::cout << p << " ";
    }
    std::cout << "\n"; // DDRDRR DRDDRR

    return 0;
}
