#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

/**
 * Problem: The Knight's tour problem
 * 
 * Given an N x N chessboard, a knight starts at cell (0, 0).
 * Move the knight according to standard chess rules such that every square 
 * on the board is visited exactly once.
 * Print the resulting grid showing the step number (0 to N^2 - 1) at each cell.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - This is an open Hamiltonian path problem on a knight graph.
 * - Unlike Rat in a Maze (where the grid has 4 neighbors), a knight has 8 moves.
 * - On an 8x8 board (64 cells), naive backtracking explores an astronomical search space (up to 8^64)
 *   and will hang indefinitely.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Backtracking with Warnsdorff's Heuristic:
 *   Warnsdorff's Rule:
 *     "Always move the knight to the adjacent unvisited square that has the MINIMUM 
 *      number of onward accessible legal moves."
 *   Why this works:
 *     Moving to cells with fewer onward choices visits "tight corners and edges" early,
 *     preventing them from becoming isolated unvisitable dead ends later in the tour!
 *   With Warnsdorff's heuristic, a Knight's Tour on an 8x8 board is found in milliseconds 
 *   with almost zero backtracks!
 */

class Solution {
    const int N = 8;
    const int dr[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    const int dc[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    bool isSafe(int r, int c, const vector<vector<int>>& board) {
        return (r >= 0 && r < N && c >= 0 && c < N && board[r][c] == -1);
    }

    // Count onward degree: how many unvisited safe moves exist from (r, c)
    int getDegree(int r, int c, const vector<vector<int>>& board) {
        int count = 0;
        for (int i = 0; i < 8; i++) {
            if (isSafe(r + dr[i], c + dc[i], board)) {
                count++;
            }
        }
        return count;
    }

    bool solveKTUtil(int r, int c, int move_idx, vector<vector<int>>& board) {
        // Base case: All N*N squares have been visited
        if (move_idx == N * N) {
            return true;
        }

        // Collect all valid next moves and their degrees (Warnsdorff's heuristic)
        vector<pair<int, int>> next_moves; // pair<degree, move_direction_index>

        for (int i = 0; i < 8; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (isSafe(nr, nc, board)) {
                int degree = getDegree(nr, nc, board);
                next_moves.push_back({degree, i});
            }
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Warnsdorff's Rule: Sort next candidate moves by ascending degree (fewest onward moves first)
        sort(next_moves.begin(), next_moves.end());

        // Try candidates in order of Warnsdorff heuristic
        for (const auto& candidate : next_moves) {
            int dir_idx = candidate.second;
            int nr = r + dr[dir_idx];
            int nc = c + dc[dir_idx];

            board[nr][nc] = move_idx; // Make move

            if (solveKTUtil(nr, nc, move_idx + 1, board)) {
                return true;
            }

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Backtrack: Undo move if subsequent path dead-ends
            board[nr][nc] = -1;
        }

        return false;
    }

public:
    bool solveKnightTour() {
        vector<vector<int>> board(N, vector<int>(N, -1));

        // Start knight at (0, 0)
        board[0][0] = 0;

        if (!solveKTUtil(0, 0, 1, board)) {
            cout << "No tour exists.\n";
            return false;
        }

        // Print board tour
        cout << "Knight's Tour (8x8) using Warnsdorff's Algorithm:\n";
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                cout << setw(3) << board[r][c] << " ";
            }
            cout << "\n";
        }

        return true;
    }
};

int main() {
    Solution sol;
    sol.solveKnightTour();
    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N^2) with Warnsdorff's heuristic (finds a valid Hamiltonian path almost deterministically).
 *   Naive backtracking would be O(8^(N^2)).
 * - Space Complexity: O(N^2) for the chessboard matrix and recursion call stack.
 */
