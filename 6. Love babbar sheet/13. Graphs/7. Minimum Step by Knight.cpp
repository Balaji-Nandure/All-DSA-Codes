/**
 * Problem: Minimum Steps by Knight to Reach Target
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - A grid usually allows 4 cardinal moves (Up, Down, Left, Right).
 * - A Knight moves in an "L-shape": 2 squares along one axis and 1 square along the perpendicular axis (8 possible moves).
 * - To find the MINIMUM number of steps in an unweighted graph, Breadth-First Search (BFS) is mathematically optimal.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - 8-Directional Queue BFS:
 *   - Why BFS? Because every knight leap has uniform cost (weight = 1).
 *   - The first time the target coordinate is dequeued in BFS, its path length is GUARANTEED to be minimal.
 *   - Knight move vectors:
 *     `dRow = {-2, -2, -1, -1, 1, 1, 2, 2}`
 *     `dCol = {-1, 1, -2, 2, -2, 2, -1, 1}`
 *   - Maintain a 2D boolean array `visited[N + 1][N + 1]` to eliminate redundant states.
 * 
 * TIME COMPLEXITY:
 * - O(N^2): In the worst case, all squares of the N x N chessboard are visited once.
 * 
 * SPACE COMPLEXITY:
 * - O(N^2) for the BFS queue and visited matrix.
 */

#include <iostream>
#include <vector>
#include <queue>

struct Cell {
    int r, c, dist;
};

int minStepToReachTarget(std::vector<int>& knightPos, std::vector<int>& targetPos, int N) {
    // 1-based indexing
    int startR = knightPos[0], startC = knightPos[1];
    int targetR = targetPos[0], targetC = targetPos[1];

    if (startR == targetR && startC == targetC) return 0;

    int dRow[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dCol[] = {-1, 1, -2, 2, -2, 2, -1, 1};

    std::vector<std::vector<bool>> visited(N + 1, std::vector<bool>(N + 1, false));
    std::queue<Cell> q;

    visited[startR][startC] = true;
    q.push({startR, startC, 0});

    while (!q.empty()) {
        Cell curr = q.front();
        q.pop();

        if (curr.r == targetR && curr.c == targetC) {
            return curr.dist;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Explore all 8 knight moves; BFS guarantees the earliest arrival at target has minimal steps.
        for (int i = 0; i < 8; i++) {
            int nr = curr.r + dRow[i];
            int nc = curr.c + dCol[i];

            if (nr >= 1 && nr <= N && nc >= 1 && nc <= N && !visited[nr][nc]) {
                visited[nr][nc] = true;
                q.push({nr, nc, curr.dist + 1});
            }
        }
    }

    return -1;
}

int main() {
    int N = 6;
    std::vector<int> knightPos = {4, 5};
    std::vector<int> targetPos = {1, 1};

    std::cout << "Minimum knight steps: " 
              << minStepToReachTarget(knightPos, targetPos, N) << "\n"; // 3

    return 0;
}
