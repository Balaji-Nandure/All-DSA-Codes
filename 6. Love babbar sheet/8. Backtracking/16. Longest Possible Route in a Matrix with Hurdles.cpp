#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Problem: Longest Possible Route in a Matrix with Hurdles
 * 
 * Given an R x C grid where 1 represents a passable cell and 0 represents a hurdle.
 * Find the length of the LONGEST simple path from source cell (xs, ys) to destination cell (xd, yd).
 * Cells cannot be visited more than once in the path. If no path exists, return -1.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "11. Find shortest safe route", we used BFS to find the SHORTEST path in O(R * C) time.
 * - Finding the LONGEST SIMPLE path cannot be solved by BFS because BFS terminates at the first 
 *   arrival (which is the shortest, not longest).
 * - Standard 2D DP also fails because movements are 4-directional and can form loops; 
 *   visited history is an arbitrary subset of cells.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Exhaustive Backtracking with Visited State Unwinding:
 *   1. Feasibility:
 *      If mat[xs][ys] == 0 or mat[xd][yd] == 0, no path is possible.
 *   2. State:
 *      Maintain `visited[R][C]` to ensure each cell is visited at most once in a given path.
 *   3. Recursion dfs(r, c, current_length):
 *      - If (r, c) == (xd, yd):
 *        We reached the target! Update global_max_len = max(global_max_len, current_length).
 *        Return immediately (do not continue traversing past destination).
 *      - Mark current cell: visited[r][c] = true.
 *      - Explore all 4 orthogonal directions (Up, Down, Left, Right):
 *        If neighbor is within grid, passable (mat == 1), and unvisited:
 *          dfs(nr, nc, current_length + 1).
 *      - *** CRUCIAL BACKTRACKING STEP ***:
 *        visited[r][c] = false.
 *        Unmark the cell so alternative longer paths can pass through here.
 */

class Solution {
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    void dfs(int r, int c, int xd, int yd, int current_len, int& max_len,
             const vector<vector<int>>& mat, vector<vector<bool>>& visited, int R, int C) {
        // Base case: Reached destination
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        if (r == xd && c == yd) {
            max_len = max(max_len, current_len);
            return;
        }

        visited[r][c] = true;

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < R && nc >= 0 && nc < C) {
                if (mat[nr][nc] == 1 && !visited[nr][nc]) {
                    dfs(nr, nc, xd, yd, current_len + 1, max_len, mat, visited, R, C);
                }
            }
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Backtrack: Restore cell state to enable exploration of alternative paths
        visited[r][c] = false;
    }

public:
    int longestPath(vector<vector<int>>& matrix, int xs, int ys, int xd, int yd) {
        int R = matrix.size();
        if (R == 0) return -1;
        int C = matrix[0].size();

        // Edge checks
        if (matrix[xs][ys] == 0 || matrix[xd][yd] == 0) {
            return -1;
        }

        vector<vector<bool>> visited(R, vector<bool>(C, false));
        int max_len = -1;

        dfs(xs, ys, xd, yd, 0, max_len, matrix, visited, R, C);
        return max_len;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> mat = {
        {1, 1, 1, 1},
        {1, 1, 0, 1},
        {1, 1, 1, 1}
    };
    int xs = 0, ys = 0;
    int xd = 1, yd = 3;

    cout << "Longest Path Length: " << sol.longestPath(mat, xs, ys, xd, yd) << "\n";
    // Expected: 8

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(4^(R * C)) in the worst case (open grid). Pruned by hurdles and visited cells.
 * - Space Complexity: O(R * C) for the visited table and recursion stack.
 */
