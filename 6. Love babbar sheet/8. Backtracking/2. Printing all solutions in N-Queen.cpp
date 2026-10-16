#include <iostream>
#include <vector>
#include <string>

using namespace std;

/**
 * Problem: Printing all solutions in N-Queen
 * 
 * Place N queens on an N x N chessboard such that no two queens threaten each other.
 * (No two queens share the same row, column, or diagonal).
 * Output all distinct configurations.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "1. Rat in a Maze", movement was local (adjacent neighbors).
 * - In N-Queens, constraints are GLOBAL across entire lines of sight (row, column, and both diagonals).
 * - A queen placed at (r, c) constrains all future rows.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Row-by-Row Backtracking with O(1) Constraint Bitsets:
 *   1. Since each row must contain exactly one queen, we iterate row by row from r = 0 to N - 1.
 *   2. For row r, try placing a queen in column c for c in [0..N-1].
 *   3. Constraint Verification in O(1):
 *      - Column check: column `c` must be unoccupied.
 *      - Main diagonal check: `r + c` is constant for all cells on the top-right to bottom-left diagonals.
 *      - Anti-diagonal check: `r - c + (N - 1)` is constant for top-left to bottom-right diagonals.
 *      Using three boolean arrays (or bitmasks) reduces the safety check from O(N) to O(1)!
 *   4. State Restoration:
 *      - Place queen: mark col[c], diag1[r + c], diag2[r - c + N - 1].
 *      - Recurse for row r + 1.
 *      - Backtrack: unmark col[c], diag1[r + c], diag2[r - c + N - 1].
 */

class Solution {
    void solve(int row, int n, vector<int>& current_cols,
               vector<bool>& col_used, vector<bool>& diag1_used, vector<bool>& diag2_used,
               vector<vector<int>>& result) {
        // Base case: All N queens successfully placed
        if (row == n) {
            result.push_back(current_cols);
            return;
        }

        for (int col = 0; col < n; col++) {
            int d1 = row + col;
            int d2 = row - col + (n - 1);

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // O(1) check: A placement is safe if and only if its column and both diagonals are free
            if (!col_used[col] && !diag1_used[d1] && !diag2_used[d2]) {
                // Apply choice
                col_used[col] = true;
                diag1_used[d1] = true;
                diag2_used[d2] = true;
                current_cols.push_back(col + 1); // 1-based column position for GFG convention

                // Recurse to next row
                solve(row + 1, n, current_cols, col_used, diag1_used, diag2_used, result);

                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Backtrack: Undo choice to leave board clean for alternative search paths
                current_cols.pop_back();
                col_used[col] = false;
                diag1_used[d1] = false;
                diag2_used[d2] = false;
            }
        }
    }

public:
    vector<vector<int>> nQueen(int n) {
        vector<vector<int>> result;
        vector<int> current_cols;
        vector<bool> col_used(n, false);
        vector<bool> diag1_used(2 * n, false);
        vector<bool> diag2_used(2 * n, false);

        solve(0, n, current_cols, col_used, diag1_used, diag2_used, result);
        return result;
    }

    // Helper to print chessboard visualization
    void printBoard(const vector<int>& solution, int n) {
        for (int r = 0; r < n; r++) {
            int q_col = solution[r] - 1;
            for (int c = 0; c < n; c++) {
                if (c == q_col) cout << "Q ";
                else cout << ". ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
};

int main() {
    Solution sol;
    int n = 4;
    vector<vector<int>> ans = sol.nQueen(n);

    cout << "Total Solutions for N = " << n << ": " << ans.size() << "\n";
    for (size_t i = 0; i < ans.size(); i++) {
        cout << "Solution " << (i + 1) << " (1-based cols): [ ";
        for (int c : ans[i]) cout << c << " ";
        cout << "]\n";
        sol.printBoard(ans[i], n);
    }
    // For N = 4, exactly 2 solutions: [2 4 1 3] and [3 1 4 2]

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N!). In row 0 we have N choices, row 1 at most N-2 choices, row 2 at most N-4 choices, etc.
 *   With O(1) state checks via bitsets, pruning occurs instantaneously.
 * - Space Complexity: O(N) recursion stack and constraint hash tables.
 */
