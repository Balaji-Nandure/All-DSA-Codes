// Problem: 1091. Shortest Distance in a Binary Maze / Shortest Path in Binary Matrix
// Link (GFG): https://www.geeksforgeeks.org/problems/shortest-path-in-a-binary-maze-1655453161/1
// Link (LeetCode): https://leetcode.com/problems/shortest-path-in-binary-matrix/
// Difficulty: Medium
// Topic: Graph, BFS, Shortest Path, Dijkstra's Algorithm, Matrix

/*
Problem Statement (GFG):
Given an n x m binary matrix grid where 1 denotes a walkable cell and 0 denotes a blocked cell.
Find the shortest distance from a given source cell to a destination cell.
You can move in 4 directions: Up, Down, Left, Right.
Each move costs 1 unit. If source cannot reach destination, return -1.

Problem Statement (LeetCode 1091):
Given an n x n binary matrix grid where 0 denotes a clear cell and 1 denotes a blocked cell.
Find the length of the shortest clear path from top-left (0, 0) to bottom-right (n-1, n-1).
You can move in 8 directions (including diagonals).
Return the number of cells visited along the path, or -1 if no such path exists.

Example 1 (GFG):
Input:
grid = [[1, 1, 1, 1],
        [1, 1, 0, 1],
        [1, 1, 1, 1],
        [1, 1, 0, 0],
        [1, 0, 0, 1]]
source = [0, 1], destination = [2, 2]
Output: 3
Explanation: Shortest path: (0,1) -> (0,2) -> (1,2) -> (2,2) with distance 3.

Example 2 (LeetCode 1091):
Input: grid = [[0,1],[1,0]]
Output: 2
Explanation: (0,0) -> (1,1) diagonally, length = 2 cells.

Constraints:
- 1 <= n, m <= 500
- grid[i][j] is either 0 or 1.
*/

// Approach: BFS (Why Queue instead of Priority Queue?)
// 1. Core Insight:
//    - Every step/edge in the grid has an EQUAL weight of 1.
//    - When all edge weights are identical (uniform), standard BFS inherently visits cells in 
//      strictly increasing order of distance (level-by-level).
//    - Therefore, a standard `std::queue` works perfectly in O(N * M) time!
//    - Using a `priority_queue` would unnecessarily add a log(N * M) factor without any benefit.
// 2. Algorithm Steps (GFG - 4 directions):
//    Step 1: If source == destination, return 0 immediately.
//    Step 2: Check if source or destination cell is blocked. If so, return -1.
//    Step 3: Maintain a 2D distance array initialized to infinity (1e9), with dist[src] = 0.
//    Step 4: Queue stores {distance, {row, col}}. Push {0, source}.
//    Step 5: While queue is not empty:
//            - Pop {d, {r, c}}.
//            - Explore 4 adjacent directions (up, down, left, right).
//            - If within bounds, cell is walkable (1), and d + 1 < dist[nr][nc]:
//              * Update dist[nr][nc] = d + 1.
//              * Early exit: if (nr, nc) == destination, return d + 1!
//              * Push {d + 1, {nr, nc}} to queue.
//    Step 6: If queue empties without reaching destination, return -1.

#include <bits/stdc++.h>
using namespace std;

// =========================================================================
// Variant 1: GFG Format (4 Directions, 1 = Walkable, Custom Source & Dest)
// =========================================================================
class Solution {
public:
    int shortestPath(vector<vector<int>>& grid, pair<int, int> source, pair<int, int> destination) {
        // Base case: already at destination
        if (source == destination) return 0;

        int n = grid.size();
        int m = grid[0].size();

        // If source or destination cell is blocked (0)
        if (grid[source.first][source.second] == 0 || 
            grid[destination.first][destination.second] == 0) {
            return -1;
        }

        // Distance array initialized to infinity
        const int INF = 1e9;
        vector<vector<int>> dist(n, vector<int>(m, INF));
        dist[source.first][source.second] = 0;

        // BFS queue stores {distance, {row, col}}
        queue<pair<int, pair<int, int>>> q;
        q.push({0, {source.first, source.second}});

        // 4 directions: Up, Down, Left, Right
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!q.empty()) {
            auto [d, cell] = q.front();
            auto [r, c] = cell;
            q.pop();

            // Destination reached
            if (r == destination.first && c == destination.second) {
                return d;
            }

            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                // If neighbor is within bounds, walkable, and offers a shorter path
                if (nr >= 0 && nr < n && nc >= 0 && nc < m && 
                    grid[nr][nc] == 1 && d + 1 < dist[nr][nc]) {
                    
                    dist[nr][nc] = d + 1;

                    // Early exit optimization
                    if (nr == destination.first && nc == destination.second) {
                        return d + 1;
                    }

                    q.push({d + 1, {nr, nc}});
                }
            }
        }

        return -1; // Unreachable
    }
};

// =========================================================================
// Variant 2: LeetCode 1091 Format (8 Directions, 0 = Clear, Path Length in Cells)
// =========================================================================
class SolutionLeetCode {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();

        // Blocked start or target
        if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) return -1;
        if (n == 1) return 1;

        vector<vector<int>> dist(n, vector<int>(n, 1e9));
        dist[0][0] = 1; // LeetCode counts number of cells visited

        queue<pair<int, pair<int, int>>> q;
        q.push({1, {0, 0}});

        // 8 directional deltas (including diagonals)
        int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

        while (!q.empty()) {
            auto [d, cell] = q.front();
            auto [r, c] = cell;
            q.pop();

            for (int i = 0; i < 8; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr >= 0 && nr < n && nc >= 0 && nc < n && 
                    grid[nr][nc] == 0 && d + 1 < dist[nr][nc]) {
                    
                    dist[nr][nc] = d + 1;

                    // Early exit
                    if (nr == n - 1 && nc == n - 1) {
                        return d + 1;
                    }

                    q.push({d + 1, {nr, nc}});
                }
            }
        }

        return -1;
    }
};

/*
Time Complexity: O(N * M)
- Each cell (r, c) is pushed into the queue at most once.
- For each cell, we explore 4 (or 8) neighbors.
- Total operations: 4 * (N * M) or 8 * (N * M) = O(N * M).

Space Complexity: O(N * M)
- 2D distance matrix: O(N * M).
- BFS queue: stores at most O(N * M) cells in worst case.
- Overall Auxiliary Space: O(N * M).

Key Insights:
1. Why Queue instead of Priority Queue?
   - In standard Dijkstra, edges have different non-negative weights, so paths grow unevenly.
   - Here, every edge has weight 1. The distance strictly increments by +1 level by level.
   - A simple FIFO queue naturally preserves monotonic distance order, saving the O(log(N*M)) 
     heap overhead!
2. Early Exit:
   - Because the queue is strictly monotonic, the moment we first relax the destination cell, 
     its distance is guaranteed to be minimal. We can return immediately without waiting for 
     it to be popped.
*/
