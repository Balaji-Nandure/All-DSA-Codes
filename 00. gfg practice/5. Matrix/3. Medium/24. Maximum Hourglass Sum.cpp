/*
    Problem Name: Maximum Hourglass Sum
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a 2D matrix mat[][] of size n x m, find the maximum sum of all possible hourglasses in the matrix.
    An hourglass consists of 7 elements in the following 3x3 shape:
        A  B  C
           D
        E  F  G

    Return -1 if no hourglass can be formed (i.e. if n < 3 or m < 3).

    Examples:
    Input: mat[][] = [[1, 2, 3],
                      [4, 5, 6],
                      [7, 8, 9]]
    Output: 35
    Explanation: The only 3x3 hourglass is:
    1 2 3
      5
    7 8 9
    Sum = 1 + 2 + 3 + 5 + 7 + 8 + 9 = 35.

    Input: mat[][] = [[1, 2, 3],
                      [4, 5, 6]]
    Output: -1
    Explanation: The matrix has fewer than 3 rows, so no hourglass can be formed.

    Constraints:
    1 <= n, m <= 150
    0 <= mat[i][j] <= 10^6

    Expected Complexities:
    Time Complexity: O(N * M), evaluating each 3x3 sub-grid top-left anchor (i, j).
    Space Complexity: O(1) auxiliary space.

    Approach 1: Direct Grid Hourglass Traversal (Optimal O(N * M) - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Check if an hourglass can be formed:
       - An hourglass requires a 3x3 submatrix. If `n < 3` or `m < 3`, return `-1`.
    2. Grid Traversal:
       - Iterate top-left anchor position `(i, j)` where `0 <= i <= n - 3` and `0 <= j <= m - 3`.
       - For each anchor `(i, j)`, calculate the 7-element hourglass sum:
         `sum = mat[i][j] + mat[i][j+1] + mat[i][j+2] + mat[i+1][j+1] + mat[i+2][j] + mat[i+2][j+1] + mat[i+2][j+2]`
       - Track the maximum sum encountered.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ============================================================================
// Approach 1: Direct Grid Hourglass Traversal (Optimal O(N * M) - Striver & Love Babbar)
// ============================================================================
class SolutionHourglassTraversal {
public:
    int findMaxSum(int n, int m, vector<vector<int>>& mat) {
        // Base Condition: Less than 3 rows or 3 columns cannot form an hourglass
        if (n < 3 || m < 3) {
            return -1;
        }

        int maxSum = -1;

        // Iterate through all possible top-left anchors (i, j) for 3x3 hourglass
        for (int i = 0; i <= n - 3; i++) {
            for (int j = 0; j <= m - 3; j++) {
                int currentSum = mat[i][j]     + mat[i][j + 1]     + mat[i][j + 2]
                                               + mat[i + 1][j + 1]
                               + mat[i + 2][j] + mat[i + 2][j + 1] + mat[i + 2][j + 2];

                maxSum = max(maxSum, currentSum);
            }
        }

        return maxSum;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    int findMaxSum(int n, int m, vector<vector<int>>& mat) {
        SolutionHourglassTraversal solver;
        return solver.findMaxSum(n, m, mat);
    }

    int findMaxSum(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();
        return findMaxSum(n, m, mat);
    }
};

int main() {
    // Example 1:
    // Expected Output: 35
    vector<vector<int>> mat1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int n1 = 3, m1 = 3;

    SolutionHourglassTraversal solver;
    cout << "Example 1 Max Hourglass Sum: " << solver.findMaxSum(n1, m1, mat1) << "\n";

    // Example 2:
    // Expected Output: -1
    vector<vector<int>> mat2 = {
        {1, 2, 3},
        {4, 5, 6}
    };
    int n2 = 2, m2 = 3;

    cout << "Example 2 Max Hourglass Sum: " << solver.findMaxSum(n2, m2, mat2) << "\n";

    return 0;
}
