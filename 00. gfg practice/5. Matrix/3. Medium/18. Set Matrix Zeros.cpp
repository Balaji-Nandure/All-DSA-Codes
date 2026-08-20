/*
    Problem Name: Set Matrix Zeros
    Difficulty: Medium
    Platform: GeeksforGeeks / LeetCode 73

    Problem Statement:
    Given a 2D matrix mat[][] of size n x m. Modify the matrix in-place such that if mat[i][j] is 0,
    all the elements in the i-th row and j-th column are set to 0.

    Examples:
    Input: mat[][] = [[1, -1, 1],
                      [-1, 0, 1],
                      [1, -1, 1]]
    Output: [[1, 0, 1],
             [0, 0, 0],
             [1, 0, 1]]
    Explanation: mat[1][1] = 0, so all elements in row 1 and column 1 are updated to 0s.

    Input: mat[][] = [[0, 1, 2, 0],
                      [1, 2, 6, 2],
                      [1, 3, 1, 8]]
    Output: [[0, 0, 0, 0],
             [0, 2, 6, 0],
             [0, 3, 1, 0]]

    Constraints:
    1 <= n, m <= 500
    -2^31 <= mat[i][j] <= 2^31 - 1

    Expected Complexities:
    Time Complexity: O(N * M), visiting each cell a constant number of times.
    Space Complexity: O(1) auxiliary space, in-place modification.

    Approach 1: Sentinel / Marker Value Replacement (Brute Force - Striver & Love Babbar)
    Approach 2: Dummy Row & Column Arrays (O(N * M) Time, O(N + M) Space - Striver & Love Babbar)
    Approach 3: In-Place Using 1st Row & Col as Indicators (Optimal O(N * M) Time, O(1) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Sentinel Marker Approach (Approach 1):
       - Traverse matrix. Whenever `mat[i][j] == 0`, mark non-zero elements in row `i` and col `j`
         with a sentinel value (e.g. `INT_MIN + 7` or `#` if char matrix).
       - In pass 2, replace all sentinel marked values with `0`.
    2. Dummy Arrays (Approach 2):
       - Use separate `dummyRow[n]` and `dummyCol[m]` boolean arrays to record zero locations.
    3. Optimal In-Place (Approach 3):
       - Use `mat[0][j]` (first row) and `mat[i][0]` (first column) as indicator arrays in-place.
       - Use a separate variable `col0 = 1` for column 0 indicator to avoid overlap at `mat[0][0]`.
*/

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// ============================================================================
// Approach 2: Dummy Row & Column Arrays (O(N + M) Space - Striver & Love Babbar)
// ============================================================================
class SolutionExtraSpace {
public:
    void setMatrixZeroes(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();

        vector<bool> dummyRow(n, false);
        vector<bool> dummyCol(m, false);

        // Step 1: Record rows and columns containing 0
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mat[i][j] == 0) {
                    dummyRow[i] = true;
                    dummyCol[j] = true;
                }
            }
        }

        // Step 2: Set elements to 0 based on dummy arrays
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (dummyRow[i] || dummyCol[j]) {
                    mat[i][j] = 0;
                }
            }
        }
    }
};

// ============================================================================
// Approach 3: In-Place Using 1st Row & Col (Optimal O(1) Space - Striver & Love Babbar)
// ============================================================================
class SolutionOptimal {
public:
    void setMatrixZeroes(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();

        int col0 = 1; // Indicator for column 0

        // Step 1: Mark indicators in first row and first column
        for (int i = 0; i < n; i++) {
            if (mat[i][0] == 0) col0 = 0;

            for (int j = 1; j < m; j++) {
                if (mat[i][j] == 0) {
                    mat[i][0] = 0;
                    mat[0][j] = 0;
                }
            }
        }

        // Step 2: Update inner grid cells (1 to n-1, 1 to m-1)
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                if (mat[i][0] == 0 || mat[0][j] == 0) {
                    mat[i][j] = 0;
                }
            }
        }

        // Step 3: Update first row if mat[0][0] is 0
        if (mat[0][0] == 0) {
            for (int j = 0; j < m; j++) {
                mat[0][j] = 0;
            }
        }

        // Step 4: Update first column if col0 is 0
        if (col0 == 0) {
            for (int i = 0; i < n; i++) {
                mat[i][0] = 0;
            }
        }
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    void setMatrixZeroes(vector<vector<int>>& mat) {
        SolutionOptimal solver;
        solver.setMatrixZeroes(mat);
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
    // 1 0 1
    // 0 0 0
    // 1 0 1
    vector<vector<int>> mat1 = {
        {1, -1, 1},
        {-1, 0, 1},
        {1, -1, 1}
    };

    SolutionOptimal solver1;
    solver1.setMatrixZeroes(mat1);
    cout << "Example 1 Set Matrix Zeros (Optimal):\n";
    printMatrix(mat1);
    cout << "\n";

    // Example 2:
    // Expected Output:
    // 0 0 0 0
    // 0 2 6 0
    // 0 3 1 0
    vector<vector<int>> mat2 = {
        {0, 1, 2, 0},
        {1, 2, 6, 2},
        {1, 3, 1, 8}
    };

    SolutionMarker solver2;
    solver2.setMatrixZeroes(mat2);
    cout << "Example 2 Set Matrix Zeros (Marker Approach):\n";
    printMatrix(mat2);

    return 0;
}
