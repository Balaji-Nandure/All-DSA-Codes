#include <iostream>
#include <vector>

using namespace std;

/**
 * Problem: Print all possible paths from top left to bottom right of mXn matrix
 * 
 * Given an M x N matrix, find and print all possible paths from cell (0, 0) 
 * to bottom-right cell (M - 1, N - 1).
 * Movement is restricted to DOWN and RIGHT only.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "1. Rat in a Maze" and "16. Longest Route", 4 directions were allowed, creating potential loops.
 * - Here, moves are STRICTLY directed (Down and Right). The state space forms a Directed Acyclic 
 *   Graph (DAG), guaranteeing that every path has exactly (M + N - 1) cells.
 * - While the COUNT of paths can be found with DP in O(M * N) or combinatorics C(M+N-2, M-1),
 *   PRINTING EVERY PATH requires Backtracking.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Simple Recursive DFS Backtracking:
 *   1. Maintain a dynamic buffer `current_path`.
 *   2. At cell (r, c):
 *      - Push mat[r][c] into current_path.
 *      - Base Case:
 *        If r == M - 1 and c == N - 1 (destination reached), add current_path to result.
 *      - Branching:
 *        - Move Down: if r + 1 < M, recurse dfs(r + 1, c).
 *        - Move Right: if c + 1 < N, recurse dfs(r, c + 1).
 *      - Backtrack:
 *        Pop mat[r][c] from current_path.
 */

class Solution {
    void dfs(int r, int c, int M, int N, const vector<vector<int>>& mat, 
             vector<int>& current_path, vector<vector<int>>& result) {
        current_path.push_back(mat[r][c]);

        // Base case: Reached bottom-right cell
        if (r == M - 1 && c == N - 1) {
            result.push_back(current_path);
            current_path.pop_back(); // Backtrack
            return;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Move Down (r + 1)
        if (r + 1 < M) {
            dfs(r + 1, c, M, N, mat, current_path, result);
        }

        // Move Right (c + 1)
        if (c + 1 < N) {
            dfs(r, c + 1, M, N, mat, current_path, result);
        }

        // *** CRUCIAL LINE: Backtrack to restore path state ***
        current_path.pop_back();
    }

public:
    vector<vector<int>> allPaths(int M, int N, vector<vector<int>>& mat) {
        vector<vector<int>> result;
        vector<int> current_path;
        if (M == 0 || N == 0) return result;

        dfs(0, 0, M, N, mat, current_path, result);
        return result;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> mat = {
        {1, 2, 3},
        {4, 5, 6}
    };
    int M = 2, N = 3;

    vector<vector<int>> paths = sol.allPaths(M, N, mat);
    cout << "Total Paths: " << paths.size() << "\n";
    for (const auto& path : paths) {
        cout << "[ ";
        for (int val : path) cout << val << " ";
        cout << "]\n";
    }
    // Expected:
    // [ 1 2 3 6 ]
    // [ 1 2 5 6 ]
    // [ 1 4 5 6 ]

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(C(M + N - 2, M - 1) * (M + N)). Generating all binomial paths, each of length M + N - 1.
 * - Space Complexity: O(M + N) recursion stack depth and current path buffer.
 */
