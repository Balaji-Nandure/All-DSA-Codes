/*
    Problem Name: Search in a sorted Matrix
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a strictly sorted 2D matrix mat[][] of size n x m and a target number x.
    Find whether the number x is present in the matrix or not.
    Note: In a strictly sorted matrix:
    1. Each row is sorted in strictly increasing order.
    2. The first element of the i-th row (i!=0) is strictly greater than the last element of the (i-1)-th row.

    Examples:
    Input: mat[][] = [[1, 5, 9],
                      [14, 20, 21],
                      [30, 34, 43]], x = 14
    Output: true

    Input: mat[][] = [[1, 5, 9, 11],
                      [14, 20, 21, 26],
                      [30, 34, 43, 50]], x = 42
    Output: false

    Constraints:
    1 <= n, m <= 1000
    1 <= mat[i][j] <= 10^9
    1 <= x <= 10^9

    Expected Complexities:
    Time Complexity: O(log(N * M)), using virtual 1D Binary Search.
    Space Complexity: O(1), no extra space.

    Approach 1: Virtual 1D Array Binary Search (Optimal O(log(N * M)) - Striver & Love Babbar)
    Approach 2: Top-Right Staircase Search (O(N + M) - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Virtual 1D Binary Search (Optimal):
       - Since the entire 2D matrix is flattened strictly sorted from mat[0][0] to mat[n-1][m-1],
         we can treat it as a virtual 1D sorted array of length `n * m` with indices `0` to `n * m - 1`.
       - For any virtual 1D index `mid`:
         * Row index `r = mid / m`
         * Column index `c = mid % m`
       - Perform standard Binary Search:
         * If `mat[r][c] == x`: return true.
         * If `mat[r][c] < x`: `low = mid + 1`.
         * Else: `high = mid - 1`.
*/

#include <iostream>
#include <vector>

using namespace std;

// ============================================================================
// Approach 1: Virtual 1D Array Binary Search (Optimal O(log(N * M)) - Striver & Love Babbar)
// ============================================================================
class SolutionOptimal {
public:
    bool searchMatrix(vector<vector<int>>& mat, int x) {
        int n = mat.size();
        int m = mat[0].size();

        int low = 0;
        int high = n * m - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            // Map 1D index mid to 2D matrix coordinates (r, c)
            int r = mid / m;
            int c = mid % m;

            if (mat[r][c] == x) {
                return true;
            } else if (mat[r][c] < x) {
                low = mid + 1; // Search right half
            } else {
                high = mid - 1; // Search left half
            }
        }

        return false;
    }
};

// ============================================================================
// Approach 2: Top-Right Staircase Search (O(N + M) - Striver & Love Babbar)
// ============================================================================
class SolutionStaircase {
public:
    bool searchMatrix(vector<vector<int>>& mat, int x) {
        int n = mat.size();
        int m = mat[0].size();

        // Start at top-right corner
        int r = 0;
        int c = m - 1;

        while (r < n && c >= 0) {
            if (mat[r][c] == x) {
                return true;
            } else if (mat[r][c] > x) {
                c--; // Move left
            } else {
                r++; // Move down
            }
        }

        return false;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& mat, int x) {
        SolutionOptimal solver;
        return solver.searchMatrix(mat, x);
    }
};

int main() {
    // Example 1:
    // Expected Output: true
    vector<vector<int>> mat1 = {
        {1, 5, 9},
        {14, 20, 21},
        {30, 34, 43}
    };
    int x1 = 14;

    SolutionOptimal solver1;
    cout << "Example 1 (14 in matrix): " << (solver1.searchMatrix(mat1, x1) ? "true" : "false") << "\n";

    // Example 2:
    // Expected Output: false
    vector<vector<int>> mat2 = {
        {1, 5, 9, 11},
        {14, 20, 21, 26},
        {30, 34, 43, 50}
    };
    int x2 = 42;

    SolutionStaircase solver2;
    cout << "Example 2 (42 in matrix): " << (solver2.searchMatrix(mat2, x2) ? "true" : "false") << "\n";

    return 0;
}
