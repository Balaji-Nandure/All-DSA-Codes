/*
    Problem Name: Rat Maze With Multiple Jumps
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given an n x n matrix mat[][], where mat[i][j] represents the maximum number of steps a rat can jump
    either forward (right) or downward from that cell.
    Find a path for the rat to reach from the top-left cell (0, 0) to the bottom-right cell (n - 1, n - 1).
    - 0 represents a blocked cell.
    - Return an n x n solution matrix with 1 for cells in the path and 0 for remaining cells.
    - If no path exists, return [[-1]].

    Priority Rules:
    If multiple valid paths exist, choose:
    1. Shortest possible jumps first (step = 1, 2, ..., maxJump).
    2. For the same jump length, preferred order is Right over Down.

    Examples:
    Input: mat[][] = [[2, 1, 0, 0],
                      [3, 0, 0, 1],
                      [0, 1, 0, 1],
                      [0, 0, 0, 1]]
    Output: [[1, 0, 0, 0],
             [1, 0, 0, 1],
             [0, 0, 0, 1],
             [0, 0, 0, 1]]

    Input: mat[][] = [[2, 1, 0, 0],
                      [2, 0, 0, 1],
                      [0, 1, 0, 1],
                      [0, 0, 0, 1]]
    Output: [[-1]]

    Constraints:
    1 <= n <= 50
    0 <= mat[i][j] <= 20

    Expected Complexities:
    Time Complexity: O(2^(N^2)), backtracking DFS.
    Space Complexity: O(N^2), for solution matrix and call stack.

    Approach 1: Backtracking DFS with Jump Priority (Optimal - Striver & Love Babbar)

    INTUITION & STRATEGY:
    - Backtracking DFS from cell (0,0):
      * Base Case: If (r, c) == (n-1, n-1), mark `sol[r][c] = 1` and return true.
      * Mark `sol[r][c] = 1`.
      * Loop `step` from 1 to `mat[r][c]`:
        - Priority 1: Try Right move with `step` length `(r, c + step)`.
        - Priority 2: Try Down move with `step` length `(r + step, c)`.
      * If any move succeeds, return true immediately (preserving shortest jump & right-first priority).
      * If all moves fail, backtrack `sol[r][c] = 0` and return false.
*/

#include <iostream>
#include <vector>

using namespace std;

// ============================================================================
// Approach 1: Backtracking DFS with Priority (Optimal - Striver & Love Babbar)
// ============================================================================
class SolutionBacktracking {
private:
    bool solve(int r, int c, const vector<vector<int>>& mat, vector<vector<int>>& sol, int n) {
        // Base Case: Reached Destination (n - 1, n - 1)
        if (r == n - 1 && c == n - 1) {
            sol[r][c] = 1;
            return true;
        }

        // Boundary & Obstacle Check
        if (r >= n || c >= n || mat[r][c] == 0) {
            return false;
        }

        // Include current cell in path
        sol[r][c] = 1;
        int maxJump = mat[r][c];

        // Priority 1: Shortest jump lengths first (step = 1, 2, ..., maxJump)
        for (int step = 1; step <= maxJump; step++) {
            // Priority 2: Right move before Down move
            // 1. Right Move
            if (c + step < n && solve(r, c + step, mat, sol, n)) {
                return true;
            }

            // 2. Down Move
            if (r + step < n && solve(r + step, c, mat, sol, n)) {
                return true;
            }
        }

        // Backtrack: Remove current cell from path if no jumps lead to destination
        sol[r][c] = 0;
        return false;
    }

public:
    vector<vector<int>> ShortestDistance(vector<vector<int>>& mat) {
        int n = mat.size();
        vector<vector<int>> sol(n, vector<int>(n, 0));

        if (solve(0, 0, mat, sol, n)) {
            return sol;
        }

        return {{-1}};
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    vector<vector<int>> ShortestDistance(vector<vector<int>>& mat) {
        SolutionBacktracking solver;
        return solver.ShortestDistance(mat);
    }
};

// Helper function to print matrix
void printMatrix(const vector<vector<int>>& mat) {
    for (const auto& row : mat) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << "\n";
    }
}

int main() {
    // Example 1:
    // Expected Output:
    // 1 0 0 0
    // 1 0 0 1
    // 0 0 0 1
    // 0 0 0 1
    vector<vector<int>> mat1 = {
        {2, 1, 0, 0},
        {3, 0, 0, 1},
        {0, 1, 0, 1},
        {0, 0, 0, 1}
    };

    SolutionBacktracking solver1;
    cout << "Example 1 Solution Path Matrix:\n";
    printMatrix(solver1.ShortestDistance(mat1));
    cout << "\n";

    // Example 2:
    // Expected Output: [[-1]]
    vector<vector<int>> mat2 = {
        {2, 1, 0, 0},
        {2, 0, 0, 1},
        {0, 1, 0, 1},
        {0, 0, 0, 1}
    };

    cout << "Example 2 Solution Path Matrix:\n";
    printMatrix(solver1.ShortestDistance(mat2));

    return 0;
}
