/*
    Problem Name: Determinant of a Matrix
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a square matrix mat[][] of size n x n. Find the determinant of this matrix.

    Examples:
    Input: mat[][] = [[1, 0, 2, -1],
                      [3, 0, 0, 5],
                      [2, 1, 4, -3],
                      [1, 0, 5, 0]]
    Output: 30
    Explanation: Determinant of the given 4x4 matrix is 30.

    Input: mat[][] = [[1, 2, 3],
                      [4, 5, 6],
                      [7, 10, 9]]
    Output: 12
    Explanation: Determinant of the given 3x3 matrix is 12.

    Constraints:
    1 <= n <= 7
    -10 <= mat[i][j] <= 10

    Expected Complexities:
    Time Complexity: O(N!), using Recursive Cofactor Expansion (for N <= 7, 7! = 5040 ops).
    Space Complexity: O(N^2), for storing minor matrices during recursive calls.

    Approach 1: Recursive Cofactor Expansion (Optimal for N <= 7 - Striver & Love Babbar)
    Approach 2: Upper Triangular Gaussian Elimination (O(N^3) - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Base Cases:
       - If `n == 1`: return `mat[0][0]`.
       - If `n == 2`: return `mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0]`.
    2. Recursive Cofactor Expansion:
       - Expand along row 0: `det = sum( (-1)^c * mat[0][c] * det(minorMatrix) )`.
       - To build `minorMatrix` for column `c`:
         * Omit row 0 and column `c` from the current matrix.
         * Recursively compute determinant of the remaining `(n-1) x (n-1)` submatrix.
*/

#include <iostream>
#include <vector>

using namespace std;

// ============================================================================
// Approach 1: Recursive Cofactor Expansion (Optimal for N <= 7 - Striver & Love Babbar)
// ============================================================================
class SolutionCofactor {
public:
    int determinantOfMatrix(vector<vector<int>>& mat, int n) {
        // Base Case 1: 1x1 matrix
        if (n == 1) {
            return mat[0][0];
        }

        // Base Case 2: 2x2 matrix
        if (n == 2) {
            return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
        }

        int det = 0;
        int sign = 1;

        // Expand along row 0 across all columns c
        for (int c = 0; c < n; c++) {
            // Construct (n-1) x (n-1) minor matrix excluding row 0 and col c
            vector<vector<int>> minorMat(n - 1, vector<int>(n - 1));

            int subI = 0;
            for (int i = 1; i < n; i++) {
                int subJ = 0;
                for (int j = 0; j < n; j++) {
                    if (j == c) continue;
                    minorMat[subI][subJ] = mat[i][j];
                    subJ++;
                }
                subI++;
            }

            // Accumulate cofactor term
            det += sign * mat[0][c] * determinantOfMatrix(minorMat, n - 1);

            // Alternate sign (+1, -1, +1, -1, ...)
            sign = -sign;
        }

        return det;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    int determinantOfMatrix(vector<vector<int>>& matrix, int n) {
        SolutionCofactor solver;
        return solver.determinantOfMatrix(matrix, n);
    }

    int determinantOfMatrix(vector<vector<int>>& matrix) {
        int n = matrix.size();
        return determinantOfMatrix(matrix, n);
    }
};

int main() {
    // Example 1:
    // Expected Output: 30
    vector<vector<int>> mat1 = {
        {1, 0, 2, -1},
        {3, 0, 0, 5},
        {2, 1, 4, -3},
        {1, 0, 5, 0}
    };
    int n1 = 4;

    SolutionCofactor solver1;
    cout << "Example 1 Determinant: " << solver1.determinantOfMatrix(mat1, n1) << "\n";

    // Example 2:
    // Expected Output: 12
    vector<vector<int>> mat2 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 10, 9}
    };
    int n2 = 3;

    cout << "Example 2 Determinant: " << solver1.determinantOfMatrix(mat2, n2) << "\n";

    return 0;
}
