/*
    Problem Name: Shortest Distance in a Binary Maze
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a binary matrix mat[][] of size n x m containing values 0 and 1, a source cell src[]
    and destination cell dest[], find the minimum number of steps required to reach the destination
    cell from the source cell.
    - 1 represents a traversable cell.
    - 0 represents a blocked cell.
    - From any cell, you can move in 4 directions (Up, Down, Left, Right).
    - If destination cell cannot be reached, return -1.

    Examples:
    Input: mat[][] = [[1, 1, 1, 1],
                      [1, 1, 0, 1],
                      [1, 1, 1, 1],
                      [1, 1, 0, 0],
                      [1, 0, 0, 1]], src = {0, 1}, dest = {2, 2}
    Output: 3
    Explanation: Shortest path: (0,1) -> (1,1) -> (2,1) -> (2,2) = 3 steps.

    Input: mat[][] = [[1, 1, 1, 1, 1],
                      [1, 1, 1, 1, 1],
                      [1, 1, 1, 1, 0],
                      [1, 0, 1, 0, 1]], src = {0, 0}, dest = {3, 4}
    Output: -1
    Explanation: Destination (3,4) is unreachable due to blocked 0 cells.

    Constraints:
    1 <= n, m <= 500
    grid[i][j] == 0 or 1

    Expected Complexities:
    Time Complexity: O(N * M), unweighted grid BFS visits each cell at most once.
    Space Complexity: O(N * M), for BFS Queue and distance array.

    Love Babbar Style Approach:
    BFS Unweighted Shortest Path Algorithm:

    1. INTUITION:
       - Since all edge weights in the grid are uniform (1 step per adjacent movement),
         Breadth-First Search (BFS) guarantees finding the SHORTEST DISTANCE to any reachable cell!
       - Step 1: Check edge cases:
         * If source == destination, return 0.
         * If source cell or destination cell is blocked (value 0), return -1.
       - Step 2: Initialize `queue<pair<int, int>> q` and distance matrix `dist[n][m]` with -1.
       - Step 3: Push source cell `(sr, sc)` into `q` and set `dist[sr][sc] = 0`.
       - Step 4: While queue is not empty:
         * Pop `curr = (r, c)`.
         * If `(r, c) == (dr, dc)`, return `dist[r][c]`.
         * Explore 4-directional valid adjacent cells `(nr, nc)` with `grid[nr][nc] == 1` and `dist[nr][nc] == -1`.
         * Set `dist[nr][nc] = dist[r][c] + 1` and push `(nr, nc)` into `q`.
         * If `(nr, nc) == (dr, dc)`, return `dist[nr][nc]` early!
       - Step 5: If queue empties without reaching destination, return -1.

    2. ALGORITHM:
       - `shortestPath(grid, source, destination)`:
         * `auto [sr, sc] = source; auto [dr, dc] = destination;`
         * `if (sr == dr && sc == dc) return 0;`
         * `if (grid[sr][sc] == 0 || grid[dr][dc] == 0) return -1;`
         * `queue<pair<int, int>> q;`
         * `vector<vector<int>> dist(n, vector<int>(m, -1));`
         * `q.push({sr, sc}); dist[sr][sc] = 0;`
         * Direction arrays: `dx[] = {-1, 1, 0, 0}`, `dy[] = {0, 0, -1, 1}`.
         * While (`!q.empty()`):
           - Pop `(r, c)`.
           - For `d` from 0 to 3:
             * `nr = r + dx[d], nc = c + dy[d];`
             * `if (valid(nr, nc) && grid[nr][nc] == 1 && dist[nr][nc] == -1)`:
               `dist[nr][nc] = dist[r][c] + 1;`
               `if (nr == dr && nc == dc) return dist[nr][nc];`
               `q.push({nr, nc});`
         * Return `-1`.

    Dry Run:
    grid = 5x4, src = (0,1), dest = (2,2)
    - q = [(0,1)], dist[0][1] = 0
    - Pop (0,1) -> push (0,0), (0,2), (1,1) with dist = 1
    - Pop (1,1) -> push (1,0), (2,1) with dist = 2
    - Pop (2,1) -> push (2,0) [dist=3], (2,2) [dist=3 -> dest reached!]
    Return 3 ✓
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    // GFG Signature - BFS Unweighted Shortest Path
    int shortestPath(vector<vector<int>>& grid, pair<int, int> source, pair<int, int> destination) {
        int n = grid.size();
        int m = grid[0].size();

        int sr = source.first, sc = source.second;
        int dr = destination.first, dc = destination.second;

        // Base Case 1: Source is already destination
        if (sr == dr && sc == dc) return 0;

        // Base Case 2: Source or Destination cell is blocked
        if (grid[sr][sc] == 0 || grid[dr][dc] == 0) return -1;

        queue<pair<int, int>> q;
        vector<vector<int>> dist(n, vector<int>(m, -1));

        q.push({sr, sc});
        dist[sr][sc] = 0;

        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            // Early exit if popped cell is destination
            if (r == dr && c == dc) {
                return dist[r][c];
            }

            for (int d = 0; d < 4; d++) {
                int nr = r + dx[d];
                int nc = c + dy[d];

                // Check boundary, traversable cell (1) and unvisited cell (-1)
                if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] == 1 && dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;

                    // Early exit when destination is reached
                    if (nr == dr && nc == dc) {
                        return dist[nr][nc];
                    }

                    q.push({nr, nc});
                }
            }
        }

        return -1; // Destination unreachable
    }
};

int main() {
    Solution ob;

    // Example 1:
    // Expected Output: 3
    vector<vector<int>> mat1 = {
        {1, 1, 1, 1},
        {1, 1, 0, 1},
        {1, 1, 1, 1},
        {1, 1, 0, 0},
        {1, 0, 0, 1}
    };
    pair<int, int> src1 = {0, 1};
    pair<int, int> dest1 = {2, 2};
    cout << "Example 1 Shortest Steps: " << ob.shortestPath(mat1, src1, dest1) << "\n";

    // Example 2:
    // Expected Output: -1
    vector<vector<int>> mat2 = {
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 0},
        {1, 0, 1, 0, 1}
    };
    pair<int, int> src2 = {0, 0};
    pair<int, int> dest2 = {3, 4};
    cout << "Example 2 Shortest Steps: " << ob.shortestPath(mat2, src2, dest2) << "\n";

    return 0;
}
