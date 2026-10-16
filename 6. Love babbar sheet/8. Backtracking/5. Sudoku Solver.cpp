#include <iostream>
#include <vector>

using namespace std;

/**
 * Problem: Sudoku Solver
 * 
 * Given an incomplete 9x9 Sudoku grid (with 0 representing empty cells),
 * fill all empty cells such that every row, column, and 3x3 subgrid contains 
 * the digits 1 to 9 exactly once.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In N-Queens, we placed 1 queen per row with linear diagonal checks.
 * - In Sudoku, we have 3 simultaneous interlocking constraints:
 *   1. Row constraint: digit unique in row.
 *   2. Column constraint: digit unique in column.
 *   3. 3x3 Box constraint: digit unique in sub-box ((r/3)*3 + c/3).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Backtracking with Fast O(1) Constraint Checking:
 *   1. Iterate through cells to find the first empty cell (grid[r][c] == 0).
 *      (If no empty cell exists, the entire board is solved!).
 *   2. For the empty cell, try placing digits '1' through '9':
 *      Check if digit d is safe:
 *      - Not present in row r.
 *      - Not present in column c.
 *      - Not present in the 3x3 sub-box starting at (r - r%3, c - c%3).
 *   3. If safe:
 *      - Place digit d.
 *      - Recursively call solveSudoku().
 *      - If recursion succeeds: return true immediately (puzzle completed).
 *      - If recursion fails: undo placement (grid[r][c] = 0) and try next digit.
 *   4. If no digit from 1 to 9 is valid, return false to trigger backtracking in parent cell.
 */

class Solution {
    bool isValid(vector<vector<int>>& grid, int row, int col, int num) {
        for (int i = 0; i < 9; i++) {
            // Check row
            if (grid[row][i] == num) return false;
            // Check column
            if (grid[i][col] == num) return false;
            // Check 3x3 subgrid
            int box_r = 3 * (row / 3) + i / 3;
            int box_c = 3 * (col / 3) + i % 3;
            if (grid[box_r][box_c] == num) return false;
        }
        return true;
    }

public:
    bool SolveSudoku(vector<vector<int>>& grid) {
        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                // Find next unfilled cell
                if (grid[r][c] == 0) {
                    for (int num = 1; num <= 9; num++) {
                        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                        // Only branch into numbers that satisfy all 3 simultaneous constraints (row, col, 3x3 box)
                        if (isValid(grid, r, c, num)) {
                            grid[r][c] = num; // Make choice

                            if (SolveSudoku(grid)) {
                                return true; // Solution found! Propagate success up
                            }

                            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                            // Backtrack: Reset cell to 0 to test alternative digits
                            grid[r][c] = 0;
                        }
                    }
                    // None of the digits 1-9 worked for this cell -> dead end
                    return false;
                }
            }
        }
        // No empty cells remaining -> puzzle completely solved!
        return true;
    }

    void printGrid(const vector<vector<int>>& grid) {
        for (int r = 0; r < 9; r++) {
            if (r > 0 && r % 3 == 0) {
                cout << "------+-------+------\n";
            }
            for (int c = 0; c < 9; c++) {
                if (c > 0 && c % 3 == 0) cout << "| ";
                cout << grid[r][c] << " ";
            }
            cout << "\n";
        }
    }
};

int main() {
    Solution sol;
    vector<vector<int>> grid = {
        {3, 0, 6, 5, 0, 8, 4, 0, 0},
        {5, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 0, 3, 1},
        {0, 0, 3, 0, 1, 0, 0, 8, 0},
        {9, 0, 0, 8, 6, 3, 0, 0, 5},
        {0, 5, 0, 0, 9, 0, 6, 0, 0},
        {1, 3, 0, 0, 0, 0, 2, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 4},
        {0, 0, 5, 2, 0, 6, 3, 0, 0}
    };

    cout << "Original Sudoku:\n";
    sol.printGrid(grid);

    if (sol.SolveSudoku(grid)) {
        cout << "\nSolved Sudoku:\n";
        sol.printGrid(grid);
    } else {
        cout << "\nNo solution exists.\n";
    }

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(9^(empty_cells)) in the worst theoretical case.
 *   In practice, constraint propagation prunes the vast majority of combinations within milliseconds.
 * - Space Complexity: O(81) = O(1) recursion stack depth bounded by the number of empty cells.
 */
