// Problem: 542. 01 Matrix / Distance of nearest cell having 1
// Link (LeetCode): https://leetcode.com/problems/01-matrix/
// Link (GFG): https://www.geeksforgeeks.org/problems/distance-of-nearest-cell-having-1-1587115620/1
// Difficulty: Medium
// Topic: BFS, Multi-source BFS, Matrix, Graph

/*
Problem Statement:
Given an m x n binary grid:
- In LeetCode 542: Return the distance of the nearest 0 for each cell.
- In GFG: Return the distance of the nearest 1 for each cell.

The distance between two adjacent cells is 1 (Manhattan distance: |r1 - r2| + |c1 - c2|).

Example 1 (GFG - Nearest 1):
Input: grid = {{0, 1, 1, 0}, 
               {1, 1, 0, 0}, 
               {0, 0, 1, 1}}
Output: {{1, 0, 0, 1}, 
         {0, 0, 1, 1}, 
         {1, 1, 0, 0}}
Explanation:
- The cells with 1 have distance 0.
- For (0, 0), nearest 1 is at (0, 1) or (1, 0), distance = 1.
- For (0, 3), nearest 1 is at (0, 2), distance = 1.

Example 2 (LeetCode 542 - Nearest 0):
Input: mat = [[0,0,0],
              [0,1,0],
              [1,1,1]]
Output: [[0,0,0],
         [0,1,0],
         [1,2,1]]

Constraints:
- m == grid.length
- n == grid[i].length
- 1 <= m, n <= 10^4
- 1 <= m * n <= 10^4
- grid[i][j] is either 0 or 1.
- There is at least one target cell in the matrix.
*/

// Approach: Multi-source BFS
// 1. Identify all source cells (all 1s for GFG / all 0s for LeetCode) and insert them into a queue.
// 2. Initialize a distance matrix: distance of source cells is 0.
// 3. Keep a visited tracker (or mark in-place / check unvisited state) so cells are processed only once.
// 4. Pop cells from queue one by one, explore 4 adjacent directions (up, down, left, right).
// 5. If neighbor is within bounds and unvisited, set dist[nr][nc] = dist[r][c] + 1 and push neighbor to queue.
// 6. Because BFS processes nodes level-by-level, the first time an unvisited cell is reached, it is guaranteed to be the shortest distance.

#include <bits/stdc++.h>
using namespace std;

// ==========================================
// Variant 1: GFG (Distance of nearest 1)
// ==========================================
class Solution {
public:
    // Function to find distance of nearest 1 in the grid for each cell
    vector<vector<int>> nearest(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> dist(m, vector<int>(n, 0));
        vector<vector<int>> vis(m, vector<int>(n, 0));
        queue<pair<int, int>> q;

        // Step 1: Push all cells containing 1 into the queue as BFS starting sources
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    q.push({i, j});
                    vis[i][j] = 1;
                    dist[i][j] = 0;
                }
            }
        }

        // 4 possible directional movements: Up, Down, Left, Right
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        // Step 2: Multi-source BFS traversal
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                // Check boundaries and visited status
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && !vis[nr][nc]) {
                    vis[nr][nc] = 1;
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }

        return dist;
    }
};

// ==========================================
// Variant 2: LeetCode 542 (Distance of nearest 0)
// ==========================================
class SolutionLeetCode {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();

        vector<vector<int>> dist(m, vector<int>(n, -1));
        queue<pair<int, int>> q;

        // Step 1: Push all cells containing 0 into the queue
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 0) {
                    q.push({i, j});
                    dist[i][j] = 0;
                }
            }
        }

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        // Step 2: Multi-source BFS
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                // If within bounds and not yet visited (dist is -1)
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }

        return dist;
    }
};

/*
Time Complexity: O(M * N)
- In the initial scan, we iterate over all M * N cells to find the source cells.
- Each cell is pushed into and popped from the queue at most once.
- For every cell, we explore 4 neighbors: 4 * (M * N) operations.
- Total Time: O(M * N)

Space Complexity: O(M * N)
- Distance matrix: O(M * N)
- Visited matrix / tracker: O(M * N)
- Queue: O(M * N) in the worst case (e.g. when all cells are sources).
- Total Auxiliary Space: O(M * N)

Key Insights:
1. Multi-source BFS vs Single-source BFS:
   - Running a separate BFS from every 0 to find the nearest target would take O((M * N)^2), resulting in TLE.
   - By enqueuing ALL source cells at time t=0 and radiating outward simultaneously in a single BFS wave, each cell is visited in optimal O(M * N) time.
2. BFS guarantees the shortest distance in an unweighted grid because edges have equal weight (1 step).
3. Difference between platforms:
   - GFG: Find distance to nearest 1 (start BFS from all 1s).
   - LeetCode 542: Find distance to nearest 0 (start BFS from all 0s).
*/
