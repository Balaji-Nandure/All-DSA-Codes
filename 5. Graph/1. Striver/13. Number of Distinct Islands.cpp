// Problem: Number of Distinct Islands / LeetCode 694
// Link (GFG): https://www.geeksforgeeks.org/problems/number-of-distinct-islands/1
// Link (LeetCode): https://leetcode.com/problems/number-of-distinct-islands/ (Premium)
// Difficulty: Medium
// Topic: DFS, BFS, Graph, Matrix, Hash Set, Coordinate Normalization

/*
Problem Statement:
Given a boolean 2D matrix grid of size n * m. Find the number of distinct islands where a group of 
connected 1s (horizontally or vertically) forms an island.

Two islands are considered to be distinct if and only if one island is NOT equal to another 
(without considering rotations and reflections, only translations). 
That is, if one island can be translated (shifted) to coincide with another, they are considered the SAME shape.

Example 1:
Input:
grid[][] = {{1, 1, 0, 0, 0},
            {1, 1, 0, 0, 0},
            {0, 0, 0, 1, 1},
            {0, 0, 0, 1, 1}}
Output: 1
Explanation:
- Island 1: [(0,0), (0,1), (1,0), (1,1)]
- Island 2: [(2,3), (2,4), (3,3), (3,4)]
- Shifting Island 2 by (-2, -3) yields the exact same relative coordinates: [(0,0), (0,1), (1,0), (1,1)].
- Therefore, there is only 1 distinct island.

Example 2:
Input:
grid[][] = {{1, 1, 0, 1, 1},
            {1, 0, 0, 0, 0},
            {0, 0, 0, 0, 1},
            {1, 1, 0, 1, 1}}
Output: 3

Constraints:
- 1 <= n, m <= 500
- grid[i][j] is either 0 or 1.
*/

// Approach: Coordinate Normalization + Set of Shapes
// 1. Traverse each cell in the grid.
// 2. When an unvisited land cell '1' is found, it represents the root/base of a new island at (base_row, base_col).
// 3. Perform DFS/BFS to explore all connected land cells of this island:
//    - For each cell (r, c) in the island, compute its relative coordinate: (r - base_row, c - base_col).
//    - Store these relative coordinates in an ordered list (shape vector).
// 4. Because traversal explores neighbors in a deterministic order (up, right, down, left), 
//    two identical island shapes will yield the exact same sequence of relative offsets.
// 5. Insert the shape vector into a std::set to filter out duplicates.
// 6. Return the size of the set (total distinct shapes).

#include <bits/stdc++.h>
using namespace std;

// Approach 1: DFS with Relative Coordinate Normalization
class Solution {
private:
    void dfs(int r, int c, vector<vector<int>>& grid,
             vector<vector<int>>& vis, vector<pair<int, int>>& shape,
             int br, int bc) {
        int m = grid.size();
        int n = grid[0].size();

        vis[r][c] = 1;
        // Record coordinate relative to the island's base (br, bc)
        shape.push_back({r - br, c - bc});

        // Consistent traversal order: Up, Right, Down, Left
        int dr[] = {-1, 0, 1, 0};
        int dc[] = {0, 1, 0, -1};

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nc >= 0 && nr < m && nc < n &&
                grid[nr][nc] == 1 && !vis[nr][nc]) {
                dfs(nr, nc, grid, vis, shape, br, bc);
            }
        }
    }

public:
    int countDistinctIslands(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> vis(m, vector<int>(n, 0));
        set<vector<pair<int, int>>> shapes;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1 && !vis[i][j]) {
                    vector<pair<int, int>> shape;
                    // Start DFS with (i, j) as the base reference point
                    dfs(i, j, grid, vis, shape, i, j);
                    shapes.insert(shape);
                }
            }
        }

        return shapes.size();
    }
};

// Approach 2: BFS Alternative (with Queue)
class SolutionBFS {
private:
    void bfs(int startR, int startC, vector<vector<int>>& grid,
             vector<vector<int>>& vis, vector<pair<int, int>>& shape) {
        int m = grid.size();
        int n = grid[0].size();

        queue<pair<int, int>> q;
        q.push({startR, startC});
        vis[startR][startC] = 1;

        int dr[] = {-1, 0, 1, 0};
        int dc[] = {0, 1, 0, -1};

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            // Store relative coordinates with respect to base (startR, startC)
            shape.push_back({r - startR, c - startC});

            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr >= 0 && nc >= 0 && nr < m && nc < n &&
                    grid[nr][nc] == 1 && !vis[nr][nc]) {
                    vis[nr][nc] = 1;
                    q.push({nr, nc});
                }
            }
        }
    }

public:
    int countDistinctIslands(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> vis(m, vector<int>(n, 0));
        set<vector<pair<int, int>>> shapes;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1 && !vis[i][j]) {
                    vector<pair<int, int>> shape;
                    bfs(i, j, grid, vis, shape);
                    shapes.insert(shape);
                }
            }
        }

        return shapes.size();
    }
};

/*
Time Complexity: O(M * N * log(number of distinct shapes))
- Every cell is visited at most once during DFS/BFS: O(M * N).
- Inserting a shape of size K into the set takes O(K * log(total shapes)).
- Across all shapes, sum of K <= M * N.
- Total Time: O(M * N * log(distinct shapes)).

Space Complexity: O(M * N)
- Visited matrix: O(M * N).
- Recursion call stack / BFS queue: O(M * N) in worst case.
- Set storing shapes: O(M * N) total cells across all distinct island representations.

Key Insights:
1. Why Coordinate Normalization Works:
   - Subtracting the base cell coordinates (r - br, c - bc) translates any island so its first 
     discovered cell becomes (0, 0).
   - This makes identical shapes invariant to their absolute position in the grid.
2. Crucial Role of Traversal Order:
   - We must keep directional steps in the exact same sequence (e.g. Up, Right, Down, Left).
   - If traversal order differs, two identical shapes could record cells in a different sequence,
     causing std::set to mistakenly treat them as different shapes.
*/
