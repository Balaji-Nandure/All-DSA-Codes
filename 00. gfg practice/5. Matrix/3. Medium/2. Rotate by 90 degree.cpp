/*
    Problem Name: Rotate by 90 degree
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a square matrix mat[][] of size n x n, rotate it by 90 degrees in an anti-clockwise
    direction in-place (without using any extra space).

    Examples:
    Input: mat[][] = [[0, 1, 2],
                      [3, 4, 5],
                      [6, 7, 8]]
    Output: [[2, 5, 8],
             [1, 4, 7],
             [0, 3, 6]]

    Input: mat[][] = [[1, 2],
                      [3, 4]]
    Output: [[2, 4],
             [1, 3]]

    Constraints:
    1 <= n <= 100
    0 <= mat[i][j] <= 1000

    Expected Complexities:
    Time Complexity: O(N^2), visiting each matrix element a constant number of times.
    Space Complexity: O(1), in-place rotation.

    Love Babbar Style Approach:
    In-Place Matrix Transformation (Reverse Rows + Transpose):

    1. INTUITION:
       - Rotating a matrix by 90 degrees ANTI-CLOCKWISE can be achieved in two in-place steps:
         * Step 1: Reverse each row of the matrix horizontally.
           For example:
           0 1 2         2 1 0
           3 4 5  ====>  5 4 3
           6 7 8         8 7 6
         * Step 2: Transpose the matrix by swapping elements across the main diagonal (`swap(mat[i][j], mat[j][i])`).
           For example:
           2 1 0         2 5 8
           5 4 3  ====>  1 4 7
           8 7 6         0 3 6
       - Resulting matrix is rotated 90 degrees anti-clockwise in-place using O(1) auxiliary space!

    2. ALGORITHM:
       - `int n = mat.size();`
       - Step 1: For each row `i` from `0` to `n - 1`:
         * `reverse(mat[i].begin(), mat[i].end());`
       - Step 2: Transpose matrix:
         * For `i` from `0` to `n - 1`:
           - For `j` from `i + 1` to `n - 1`:
             `swap(mat[i][j], mat[j][i]);`

    Dry Run:
    mat = [[1, 2], [3, 4]]
    - Step 1 (Reverse rows):
      row 0: [2, 1]
      row 1: [4, 3]
      mat = [[2, 1], [4, 3]]
    - Step 2 (Transpose):
      swap(mat[0][1], mat[1][0]) -> swap(1, 4)
      mat = [[2, 4], [1, 3]]
    Output: [[2, 4], [1, 3]] ✓
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // GFG Signature - Anti-clockwise 90-degree in-place rotation
    void rotateby90(vector<vector<int>>& mat) {
        int n = mat.size();

        // Step 1: Reverse each row of the matrix horizontally
        for (int i = 0; i < n; i++) {
            reverse(mat[i].begin(), mat[i].end());
        }

        // Step 2: Transpose the matrix in-place
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                swap(mat[i][j], mat[j][i]);
            }
        }
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
    Solution ob;

    // Example 1:
    // Expected Output:
    // 2 5 8
    // 1 4 7
    // 0 3 6
    vector<vector<int>> mat1 = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8}
    };
    ob.rotateby90(mat1);
    cout << "Example 1 Anti-Clockwise 90 Rotation:\n";
    printMatrix(mat1);
    cout << "\n";

    // Example 2:
    // Expected Output:
    // 2 4
    // 1 3
    vector<vector<int>> mat2 = {
        {1, 2},
        {3, 4}
    };
    ob.rotateby90(mat2);
    cout << "Example 2 Anti-Clockwise 90 Rotation:\n";
    printMatrix(mat2);

    return 0;
}
