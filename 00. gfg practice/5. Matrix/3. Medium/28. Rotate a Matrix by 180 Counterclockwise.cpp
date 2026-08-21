/*
    Problem Name: Rotate a Matrix by 180 Counterclockwise
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a 2D square matrix mat[][] of size n x n, rotate it by 180 degrees counterclockwise (in-place).
    - Note: Rotating 180 degrees counterclockwise is identical to rotating 180 degrees clockwise.

    Examples:
    Input: mat[][] = [[1, 2, 3],
                      [4, 5, 6],
                      [7, 8, 9]]
    Output: [[9, 8, 7],
             [6, 5, 4],
             [3, 2, 1]]
    Explanation: Matrix is inverted both vertically and horizontally.

    Input: mat[][] = [[1, 2],
                      [3, 4]]
    Output: [[4, 3],
             [2, 1]]

    Constraints:
    1 <= n <= 500
    0 <= mat[i][j] <= 10000

    Expected Complexities:
    Time Complexity: O(N^2), visiting each cell once.
    Space Complexity: O(1) auxiliary space, in-place modification.

    Love Babbar / Striver STL Reversal Approach:
    1. Reverse the order of rows vertically: `reverse(mat.begin(), mat.end())`.
    2. Reverse elements in each row horizontally: `reverse(mat[i].begin(), mat[i].end())`.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    void rotateMatrix(vector<vector<int>>& mat) {
        int n = mat.size();

        // Step 1: Reverse the order of rows vertically
        reverse(mat.begin(), mat.end());

        // Step 2: Reverse each row horizontally
        for (int i = 0; i < n; i++) {
            reverse(mat[i].begin(), mat[i].end());
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
    Solution solver;

    // Example 1:
    // Expected Output:
    // 9 8 7
    // 6 5 4
    // 3 2 1
    vector<vector<int>> mat1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    solver.rotateMatrix(mat1);
    cout << "Example 1 Rotated 180 Degrees:\n";
    printMatrix(mat1);
    cout << "\n";

    // Example 2:
    // Expected Output:
    // 4 3
    // 2 1
    vector<vector<int>> mat2 = {
        {1, 2},
        {3, 4}
    };

    solver.rotateMatrix(mat2);
    cout << "Example 2 Rotated 180 Degrees:\n";
    printMatrix(mat2);

    return 0;
}
