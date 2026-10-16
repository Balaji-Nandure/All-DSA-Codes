// Problem: Rotate Matrix by 90 Degrees
// Link (GFG): https://www.geeksforgeeks.org/problems/rotate-by-90-degree0356/1
// Article: https://www.geeksforgeeks.org/dsa/rotate-a-matrix-by-90-degree-in-clockwise-direction-without-using-any-extra-space/
// Difficulty: Medium
// Topic: Matrix, In-Place Linear Algebra Transformation

/*
Problem Statement:
Given a square matrix of size N x N. The task is to rotate the matrix by 90 degrees 
in-place (without allocating another full matrix).

There are two standard interview variations:
  Variation 1: Clockwise 90-degree rotation (LeetCode 48 / Standard)
  Variation 2: Anti-Clockwise (Counter-Clockwise) 90-degree rotation (GFG Classic)

Both in-place transformations are implemented and explained below.

Example 1 (Clockwise):
Input:
mat = [[1, 2, 3],
       [4, 5, 6],
       [7, 8, 9]]
Output:
[[7, 4, 1],
 [8, 5, 2],
 [9, 6, 3]]

Example 2 (Anti-Clockwise):
Input:
mat = [[1, 2, 3],
       [4, 5, 6],
       [7, 8, 9]]
Output:
[[3, 6, 9],
 [2, 5, 8],
 [1, 4, 7]]

Constraints:
- 1 <= N <= 1000
- 1 <= mat[i][j] <= 1000
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In 1D Array Reversal (Problem 1 in Arrays):
//   * A 1D array was reversed via two pointers `swap(arr[l], arr[r])`.
// - In 2D Matrix Rotation:
//   * A naive 90-degree rotation copies `mat[i][j]` into `newMat[j][n - 1 - i]`, 
//     which consumes O(N^2) extra space!
//   * To achieve STRICT IN-PLACE O(1) auxiliary space, we decompose the geometric 
//     rotation into two standard primitive linear algebra operations:
//     1. Transposition (reflecting along the main diagonal: swapping `mat[i][j]` with `mat[j][i]`).
//     2. Row Reversal (horizontal reflection) OR Column Reversal (vertical reflection).

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Mathematical Decomposition:
//
// 1. Clockwise 90-degree:
//    - Cell (i, j) needs to go to (j, n - 1 - i).
//    - Step 1: Transpose the matrix -> Cell (i, j) moves to (j, i).
//    - Step 2: Reverse each individual row -> Cell (j, i) moves to (j, n - 1 - i).
//    - Done! In-place in two clean sweeps.
//
// 2. Anti-Clockwise 90-degree:
//    - Cell (i, j) needs to go to (n - 1 - j, i).
//    - Step 1: Transpose the matrix -> Cell (i, j) moves to (j, i).
//    - Step 2: Reverse each individual column (or swap rows top to bottom) -> 
//              Cell (j, i) moves to (n - 1 - j, i).
//    - Alternatively: Reverse each row first, then transpose!

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // -------------------------------------------------------------------------
    // Variation 1: Rotate Clockwise by 90 degrees (LeetCode 48 / Standard)
    // -------------------------------------------------------------------------
    void rotateClockwise(vector<vector<int>>& mat) {
        int n = mat.size();

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Step 1: Transpose the matrix in-place (swap symmetric elements across main diagonal)
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                swap(mat[i][j], mat[j][i]);
            }
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Step 2: Reverse each row horizontally
        for (int i = 0; i < n; ++i) {
            reverse(mat[i].begin(), mat[i].end());
        }
    }

    // -------------------------------------------------------------------------
    // Variation 2: Rotate Anti-Clockwise by 90 degrees (GFG Classic)
    // -------------------------------------------------------------------------
    void rotateAntiClockwise(vector<vector<int>>& mat) {
        int n = mat.size();

        // Step 1: Transpose the matrix in-place
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                swap(mat[i][j], mat[j][i]);
            }
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Step 2: Reverse each column (or swap top row with bottom row)
        for (int j = 0; j < n; ++j) {
            int top = 0, bottom = n - 1;
            while (top < bottom) {
                swap(mat[top][j], mat[bottom][j]);
                top++;
                bottom--;
            }
        }
    }
};

void printMatrix(const vector<vector<int>>& mat) {
    for (const auto& row : mat) {
        for (int val : row) cout << val << " ";
        cout << "\n";
    }
}

int main() {
    Solution sol;

    vector<vector<int>> mat1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    cout << "Original Matrix:\n";
    printMatrix(mat1);

    sol.rotateClockwise(mat1);
    cout << "\nAfter 90 deg Clockwise Rotation:\n";
    printMatrix(mat1);

    vector<vector<int>> mat2 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    sol.rotateAntiClockwise(mat2);
    cout << "\nAfter 90 deg Anti-Clockwise Rotation:\n";
    printMatrix(mat2);

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N^2)
  * Transposition visits N*(N-1)/2 pairs = O(N^2).
  * Reversing rows/columns visits N*(N/2) swaps = O(N^2).
  * Total time is strictly O(N^2), the minimum required to touch all cells.
- Space Complexity: O(1) auxiliary space (strict in-place swaps).

Key Takeaways:
- Rotation = Transpose + Reverse.
  * Clockwise: Transpose -> Reverse Rows.
  * Anti-Clockwise: Transpose -> Reverse Columns (or Reverse Rows -> Transpose).
*/
