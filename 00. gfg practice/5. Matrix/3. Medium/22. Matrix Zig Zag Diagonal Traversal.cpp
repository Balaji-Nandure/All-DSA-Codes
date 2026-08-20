/*
    Problem Name: Matrix Zig Zag Diagonal Traversal
    Difficulty: Medium
    Platform: GeeksforGeeks / LeetCode 498

    Problem Statement:
    Given a square matrix mat[][] of size n x n, find its diagonal pattern, where elements are arranged
    linearly by traversing the matrix diagonally in an alternating (Zig-Zag) direction.
    - Diagonal s = r + c ranges from 0 to 2 * n - 2.
    - If s is EVEN: Traverse UPWARD (from bottom-left to top-right).
    - If s is ODD: Traverse DOWNWARD (from top-right to bottom-left).

    Examples:
    Input: mat[][] = [[1, 2, 3],
                      [4, 5, 6],
                      [7, 8, 9]]
    Output: [1, 2, 4, 7, 5, 3, 6, 8, 9]
    Explanation:
    - s=0 (even): 1
    - s=1 (odd): 2, 4
    - s=2 (even): 7, 5, 3
    - s=3 (odd): 6, 8
    - s=4 (even): 9

    Input: mat[][] = [[1, 2, 3, 10],
                      [4, 5, 6, 11],
                      [7, 8, 9, 12],
                      [13, 14, 15, 16]]
    Output: [1, 2, 4, 7, 5, 3, 10, 6, 8, 13, 14, 9, 11, 12, 15, 16]

    Constraints:
    1 <= n <= 1000
    -100 <= mat[i][j] <= 100

    Expected Complexities:
    Time Complexity: O(N^2), visiting each matrix cell exactly once.
    Space Complexity: O(1) auxiliary space (excluding result vector).

    Approach 1: Directional Parity Simulation (Optimal O(1) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Diagonal Index `s = r + c`:
       - The total number of diagonals in an n x n matrix is `2 * n - 1` (indexed `s = 0` to `2*n - 2`).
    2. Direction Rules:
       - EVEN `s` (Upward traversal):
         * Starting cell: `r = (s < n) ? s : n - 1`, `c = s - r`.
         * Move `r--`, `c++` until `r >= 0` and `c < n`.
       - ODD `s` (Downward traversal):
         * Starting cell: `c = (s < n) ? s : n - 1`, `r = s - c`.
         * Move `r++`, `c--` until `c >= 0` and `r < n`.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ============================================================================
// Approach 1: Directional Parity Simulation (Optimal O(1) Space - Striver & Love Babbar)
// ============================================================================
class SolutionSimulation {
public:
    vector<int> matrixDiagonally(vector<vector<int>>& mat) {
        int n = mat.size();
        vector<int> ans;

        for (int s = 0; s < 2 * n - 1; s++) {
            if (s % 2 == 0) {
                // EVEN diagonal -> Upward direction (bottom-left to top-right)
                int r = (s < n) ? s : n - 1;
                int c = s - r;

                while (r >= 0 && c < n) {
                    ans.push_back(mat[r][c]);
                    r--;
                    c++;
                }
            } else {
                // ODD diagonal -> Downward direction (top-right to bottom-left)
                int c = (s < n) ? s : n - 1;
                int r = s - c;

                while (c >= 0 && r < n) {
                    ans.push_back(mat[r][c]);
                    r++;
                    c--;
                }
            }
        }

        return ans;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    vector<int> matrixDiagonally(vector<vector<int>>& mat) {
        SolutionSimulation solver;
        return solver.matrixDiagonally(mat);
    }
};

// Helper function to print 1D vector
void printVector(const vector<int>& vec) {
    for (int val : vec) {
        cout << val << " ";
    }
    cout << "\n";
}

int main() {
    // Example 1:
    // Expected Output: 1 2 4 7 5 3 6 8 9
    vector<vector<int>> mat1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    SolutionSimulation solver1;
    cout << "Example 1 Zig Zag Diagonals (Simulation):\n";
    printVector(solver1.matrixDiagonally(mat1));

    // Example 2:
    // Expected Output: 1 2 4 7 5 3 10 6 8 13 14 9 11 12 15 16
    vector<vector<int>> mat2 = {
        {1, 2, 3, 10},
        {4, 5, 6, 11},
        {7, 8, 9, 12},
        {13, 14, 15, 16}
    };

    SolutionBucketGrouping solver2;
    cout << "Example 2 Zig Zag Diagonals (Bucket Grouping):\n";
    printVector(solver2.matrixDiagonally(mat2));

    return 0;
}
