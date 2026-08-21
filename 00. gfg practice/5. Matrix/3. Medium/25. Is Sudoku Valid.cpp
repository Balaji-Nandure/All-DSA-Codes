/*
    Problem Name: Is Sudoku Valid
    Difficulty: Medium
    Platform: GeeksforGeeks / LeetCode 36

    Problem Statement:
    Given an incomplete Sudoku configuration in terms of a 9x9 2D matrix mat[][], check if the current
    configuration is valid or not.
    - 0 represents an empty cell.
    - Non-zero numbers range from 1 to 9.
    - A Sudoku configuration is valid if:
      1. Each row contains digits 1-9 without repetition.
      2. Each column contains digits 1-9 without repetition.
      3. Each of the nine 3x3 sub-boxes contains digits 1-9 without repetition.

    Examples:
    Input: mat[][] = [ [3, 0, 6, 5, 0, 8, 4, 0, 0],
                       [5, 2, 0, 0, 0, 0, 0, 0, 0],
                       [0, 8, 7, 0, 0, 0, 0, 3, 1],
                       [0, 0, 3, 0, 1, 0, 0, 8, 0],
                       [9, 0, 0, 8, 6, 3, 0, 0, 5],
                       [0, 5, 0, 0, 9, 0, 6, 0, 0],
                       [1, 3, 0, 0, 0, 0, 2, 5, 0],
                       [0, 0, 0, 0, 0, 0, 0, 7, 4],
                       [0, 0, 5, 2, 0, 6, 3, 0, 0] ]
    Output: true (or 1)

    Input: mat[][] = [ [3, 0, 3, 5, 0, 8, 4, 0, 0], ... ]
    Output: false (or 0)
    Explanation: Duplicate number 3 in row 0.

    Constraints:
    0 <= mat[i][j] <= 9
    Matrix size = 9 x 9

    Expected Complexities:
    Time Complexity: O(1) / O(81), fixed 9x9 grid size.
    Space Complexity: O(1) auxiliary space.

    Approach 1: Frequency Hashing for Rows, Columns & 3x3 Sub-boxes (Optimal - Striver & Love Babbar)
    Approach 2: Bit Manipulation Bitmasks (Optimal - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. 3x3 Box Index Formula:
       - For cell (i, j), its 3x3 sub-box index (0 to 8) is: `boxIdx = (i / 3) * 3 + (j / 3)`.
    2. Hashing Check:
       - Maintain three boolean 2D tracking arrays:
         * `rowSeen[9][10]`: tracks numbers 1-9 seen in row `i`.
         * `colSeen[9][10]`: tracks numbers 1-9 seen in col `j`.
         * `boxSeen[9][10]`: tracks numbers 1-9 seen in sub-box `boxIdx`.
       - Iterate each cell (i, j). If `mat[i][j] != 0`:
         * If number `val` already exists in `rowSeen[i][val]`, `colSeen[j][val]`, or `boxSeen[boxIdx][val]`, return `false`.
         * Otherwise, set all three indicators to `true`.
*/

#include <iostream>
#include <vector>

using namespace std;

// ============================================================================
// Approach 1: Boolean Frequency Hashing (Optimal - Striver & Love Babbar)
// ============================================================================
class SolutionHashing {
public:
    int isValid(vector<vector<int>>& mat) {
        vector<vector<bool>> rowSeen(9, vector<bool>(10, false));
        vector<vector<bool>> colSeen(9, vector<bool>(10, false));
        vector<vector<bool>> boxSeen(9, vector<bool>(10, false));

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                int val = mat[i][j];
                if (val == 0) continue; // Skip empty cells

                int boxIdx = (i / 3) * 3 + (j / 3);

                // Check duplicate in current row, column, or 3x3 sub-box
                if (rowSeen[i][val] || colSeen[j][val] || boxSeen[boxIdx][val]) {
                    return 0; // Invalid Sudoku
                }

                // Mark number as seen
                rowSeen[i][val] = true;
                colSeen[j][val] = true;
                boxSeen[boxIdx][val] = true;
            }
        }

        return 1; // Valid Sudoku
    }
};

// ============================================================================
// Approach 2: Bit Manipulation Bitmasks (Optimal O(1) Space - Striver & Love Babbar)
// ============================================================================
class SolutionBitmask {
public:
    int isValid(vector<vector<int>>& mat) {
        vector<int> rowMask(9, 0);
        vector<int> colMask(9, 0);
        vector<int> boxMask(9, 0);

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                int val = mat[i][j];
                if (val == 0) continue;

                int bit = 1 << val;
                int boxIdx = (i / 3) * 3 + (j / 3);

                if ((rowMask[i] & bit) || (colMask[j] & bit) || (boxMask[boxIdx] & bit)) {
                    return 0;
                }

                rowMask[i] |= bit;
                colMask[j] |= bit;
                boxMask[boxIdx] |= bit;
            }
        }

        return 1;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    int isValid(vector<vector<int>>& mat) {
        SolutionHashing solver;
        return solver.isValid(mat);
    }
};

int main() {
    // Example 1: Valid Sudoku
    // Expected Output: 1 (true)
    vector<vector<int>> mat1 = {
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

    SolutionHashing solver1;
    cout << "Example 1 Is Valid (Hashing): " << (solver1.isValid(mat1) ? "true" : "false") << "\n";

    // Example 2: Invalid Sudoku (Duplicate 3 in row 0)
    // Expected Output: 0 (false)
    vector<vector<int>> mat2 = {
        {3, 0, 3, 5, 0, 8, 4, 0, 0},
        {5, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 0, 3, 1},
        {0, 0, 3, 0, 1, 0, 0, 8, 0},
        {9, 0, 0, 8, 6, 3, 0, 0, 5},
        {0, 5, 0, 0, 9, 0, 6, 0, 0},
        {1, 3, 0, 0, 0, 0, 2, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 4},
        {0, 0, 5, 2, 0, 6, 3, 0, 0}
    };

    SolutionBitmask solver2;
    cout << "Example 2 Is Valid (Bitmask): " << (solver2.isValid(mat2) ? "true" : "false") << "\n";

    return 0;
}
