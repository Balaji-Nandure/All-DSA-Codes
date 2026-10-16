#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

/**
 * Problem: Find shortest safe route in a path with landmines
 * 
 * Given a matrix of size R x C with 0s and 1s.
 * 1 represents safe path, 0 represents landmine.
 * A cell adjacent (Up, Down, Left, Right) to a landmine is also UNSAFE.
 * Find the length of the shortest safe path from ANY cell in the first column (col 0)
 * to ANY cell in the last column (col C - 1). Return -1 if no path exists.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Unlike "1. Rat in a Maze" where only the obstacle cell itself was blocked,
 *   here landmines radiate a hazard field: all 4 orthogonal neighbors of a mine become forbidden.
 * - Unlike single-source paths (start at (0,0)), here we have MULTI-SOURCE starts (any row in col 0).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Step 1: Hazard Field Marking:
 *   Create a boolean matrix `isSafe` initialized to true for cells with mat[r][c] == 1.
 *   For every cell containing a mine (mat[r][c] == 0):
 *   Mark the cell itself and all its 4 adjacent neighbors as unsafe.
 * 
 * - Step 2: Multi-Source BFS vs Backtracking:
 *   Why BFS over DFS Backtracking for SHORTEST path?
 *   - DFS Backtracking visits paths of varying lengths, requiring exponential exploration 
 *     to minimize path length.
 *   - Multi-source BFS expands all candidates simultaneously level by level. The first time 
 *     BFS touches ANY cell in the last column (col C - 1), that path is GUARANTEED to be 
 *     the global shortest path!
 *   - Time complexity reduces from exponential O(4^(R*C)) to strictly linear O(R * C).
 */

class Solution {
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

public:
    int findShortestPath(vector<vector<int>>& mat) {
        int R = mat.size();
        if (R == 0) return -1;
        int C = mat[0].size();

        // Step 1: Mark hazard zones around landmines
        vector<vector<bool>> safe(R, vector<bool>(C, true));

        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                if (mat[r][c] == 0) {
                    // Mine itself is unsafe
                    safe[r][c] = false;
                    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                    // Mark all 4 adjacent cells as hazardously contaminated
                    for (int i = 0; i < 4; i++) {
                        int nr = r + dr[i];
                        int nc = c + dc[i];
                        if (nr >= 0 && nr < R && nc >= 0 && nc < C) {
                            safe[nr][nc] = false;
                        }
                    }
                }
            }
        }

        // Step 2: Multi-Source BFS from column 0
        queue<pair<int, int>> q;
        vector<vector<int>> dist(R, vector<int>(C, -1));

        for (int r = 0; r < R; r++) {
            if (safe[r][0]) {
                q.push({r, 0});
                dist[r][0] = 1; // 1 step to start at column 0
            }
        }

        while (!q.empty()) {
            auto curr = q.front();
            q.pop();

            int r = curr.first;
            int c = curr.second;

            // *** CRUCIAL LINE: Destination reached! First BFS arrival is guaranteed shortest ***
            if (c == C - 1) {
                return dist[r][c];
            }

            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr >= 0 && nr < R && nc >= 0 && nc < C) {
                    if (safe[nr][nc] && dist[nr][nc] == -1) {
                        dist[nr][nc] = dist[r][c] + 1;
                        q.push({nr, nc});
                    }
                }
            }
        }

        return -1; // No safe path reaches the last column
    }
};

int main() {
    Solution sol;
    vector<vector<int>> mat = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 0, 1, 1, 1, 1}
    };

    cout << "Shortest Safe Path Length: " << sol.findShortestPath(mat) << "\n";
    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(R * C). Hazard field marking takes O(R * C), and BFS visits each cell at most once.
 * - Space Complexity: O(R * C) for the safe grid, distance matrix, and BFS queue.
 */
