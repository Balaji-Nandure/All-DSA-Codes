#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/**
 * Problem: Rat in a maze Problem
 * 
 * Given an N x N grid `mat` where 1 represents a passable cell and 0 represents an obstacle.
 * A rat starts at (0, 0) and must reach destination (N - 1, N - 1).
 * Allowed movements: 'D' (Down), 'L' (Left), 'R' (Right), 'U' (Up).
 * No cell can be visited more than once in the same path.
 * Return all valid paths in lexicographical order.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Unlike Greedy graph traversal (which makes irrevocable local choices), backtracking explores 
 *   ALL feasible paths through a search tree with state recovery.
 * - Unlike DAG path counting (where DP works), 4-directional grids can contain cycles, 
 *   requiring an in-place visited trail that MUST be restored (unmarked) upon backtracking.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Backtracking with In-Place Visited State:
 *   1. Feasibility:
 *      If source mat[0][0] == 0 or target mat[N-1][N-1] == 0, no path can exist.
 *   2. Lexicographical Guarantee:
 *      To avoid sorting the final results vector (which is O(K log K)), explore neighbors in 
 *      strictly lexicographical direction order: 'D', 'L', 'R', 'U'.
 *   3. Backtracking State Transition:
 *      - Mark current cell mat[r][c] = 0 (or visited[r][c] = true).
 *      - Recursively explore valid unvisited neighbors.
 *      - *** CRUCIAL BACKTRACKING STEP ***: Unmark mat[r][c] = 1 (restore state) so that 
 *        other alternate paths can use this cell!
 */

class Solution {
    // Directions in strictly lexicographical order: 'D', 'L', 'R', 'U'
    const int dr[4] = {1, 0, 0, -1};
    const int dc[4] = {0, -1, 1, 0};
    const char dir[4] = {'D', 'L', 'R', 'U'};

    void backtrack(int r, int c, int n, vector<vector<int>>& mat, string& path, vector<string>& result) {
        // Base case: Reached destination (n - 1, n - 1)
        if (r == n - 1 && c == n - 1) {
            result.push_back(path);
            return;
        }

        // Mark cell as visited in-place
        mat[r][c] = 0;

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            // Check boundary and passable condition
            if (nr >= 0 && nr < n && nc >= 0 && nc < n && mat[nr][nc] == 1) {
                path.push_back(dir[i]);
                
                // Recurse deeper into search tree
                backtrack(nr, nc, n, mat, path, result);

                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Backtrack: Remove direction from path to restore candidate string state
                path.pop_back();
            }
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Backtrack: Restore matrix cell to 1 so alternative path branches can traverse through here
        mat[r][c] = 1;
    }

public:
    vector<string> findPath(vector<vector<int>>& mat) {
        int n = mat.size();
        vector<string> result;

        if (n == 0 || mat[0][0] == 0 || mat[n - 1][n - 1] == 0) {
            return result;
        }

        string path = "";
        backtrack(0, 0, n, mat, path, result);
        return result;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> mat = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {1, 1, 0, 0},
        {0, 1, 1, 1}
    };

    vector<string> paths = sol.findPath(mat);
    cout << "Total Paths: " << paths.size() << "\n";
    for (const string& p : paths) {
        cout << p << " ";
    }
    cout << "\n";
    // Expected output: "DDRDRR" "DDRRDR"

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(4^(N^2)). In the worst-case open grid, each cell can branch up to 3 directions.
 * - Space Complexity: O(N^2) maximum recursion stack depth for a path of length at most N^2.
 */
