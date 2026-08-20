/*
    Problem Name: Rotate Each Row of Matrix K Times
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given an integer k and a matrix mat[][] of size m x n, left rotate every row by k in a circular fashion.

    Examples:
    Input: k = 1, mat[][] = [[1, 2, 3],
                            [4, 5, 6],
                            [7, 8, 9]]
    Output: [[2, 3, 1],
             [5, 6, 4],
             [8, 9, 7]]
    Explanation: Each row is left rotated circularly by 1 position.

    Input: k = 2, mat[][] = [[1, 2, 3],
                            [4, 5, 6],
                            [7, 8, 9]]
    Output: [[3, 1, 2],
             [6, 4, 5],
             [9, 7, 8]]
    Explanation: Each row is left rotated circularly by 2 positions.

    Constraints:
    1 <= k <= 100000
    1 <= m, n <= 1000
    1 <= mat[i][j] <= 1000

    Expected Complexities:
    Time Complexity: O(M * N), visiting each element once.
    Space Complexity: O(1) auxiliary space, using in-place reversal algorithm.

    Approach 1: In-Place Reversal Algorithm (Optimal O(1) Extra Space - Striver & Love Babbar)
    Approach 2: Modulo Index Mapping (O(M * N) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Effective Rotation:
       - Since rotating a row of size `N` by `N` positions returns it to the original state,
         the effective left rotation required is `kEffective = k % N`.
    2. Reversal Algorithm for Circular Left Rotation of 1D Row:
       - To left-rotate a row by `kEffective`:
         * Step 1: Reverse first `kEffective` elements: `reverse(row[0 ... kEffective-1])`.
         * Step 2: Reverse remaining `N - kEffective` elements: `reverse(row[kEffective ... N-1])`.
         * Step 3: Reverse the entire row: `reverse(row[0 ... N-1])`.
       - Repeat for all `M` rows in-place!
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ============================================================================
// Approach 1: In-Place Reversal Algorithm (Optimal O(1) Space - Striver & Love Babbar)
// ============================================================================
class SolutionReversal {
public:
    vector<vector<int>> rotateMatrix(int k, vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();

        int kEff = k % n;
        if (kEff == 0) return mat;

        for (int i = 0; i < m; i++) {
            // Step 1: Reverse first kEff elements
            reverse(mat[i].begin(), mat[i].begin() + kEff);

            // Step 2: Reverse remaining n - kEff elements
            reverse(mat[i].begin() + kEff, mat[i].end());

            // Step 3: Reverse the entire row
            reverse(mat[i].begin(), mat[i].end());
        }

        return mat;
    }
};

// ============================================================================
// Approach 2: Modulo Index Mapping (O(M * N) Space - Striver & Love Babbar)
// ============================================================================
class SolutionIndexMapping {
public:
    vector<vector<int>> rotateMatrix(int k, vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();

        int kEff = k % n;
        vector<vector<int>> res(m, vector<int>(n));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                res[i][j] = mat[i][(j + kEff) % n];
            }
        }

        return res;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    vector<vector<int>> rotateMatrix(int k, vector<vector<int>>& mat) {
        SolutionReversal solver;
        return solver.rotateMatrix(k, mat);
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
    // Example 1:
    // Expected Output:
    // 2 3 1
    // 5 6 4
    // 8 9 7
    vector<vector<int>> mat1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int k1 = 1;

    SolutionReversal solver1;
    solver1.rotateMatrix(k1, mat1);
    cout << "Example 1 (k=1 Reversal In-Place):\n";
    printMatrix(mat1);
    cout << "\n";

    // Example 2:
    // Expected Output:
    // 3 1 2
    // 6 4 5
    // 9 7 8
    vector<vector<int>> mat2 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int k2 = 2;

    SolutionIndexMapping solver2;
    vector<vector<int>> res2 = solver2.rotateMatrix(k2, mat2);
    cout << "Example 2 (k=2 Index Mapping):\n";
    printMatrix(res2);

    return 0;
}
