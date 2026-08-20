/*
    Problem Name: Kth of spiral matrix
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a matrix mat[][] of size n x m and a number k, find the k-th element obtained while traversing
    the matrix in spiral order (1-indexed).

    Spiral Order Pattern:
    1. Move left to right on the top row.
    2. Move top to bottom on the rightmost column.
    3. Move right to left on the bottom row.
    4. Move bottom to top on the leftmost column.
    Repeat layer by layer for inner submatrices.

    Examples:
    Input: mat[][] = [[1, 2, 3, 4],
                      [5, 6, 7, 8],
                      [9, 10, 11, 12],
                      [13, 14, 15, 16]], k = 10
    Output: 13
    Explanation: Spiral sequence = [1, 2, 3, 4, 8, 12, 16, 15, 14, 13, 9, 5, 6, 7, 11, 10].
    The 10th element is 13.

    Input: mat[][] = [[1, 2, 3],
                      [4, 5, 6],
                      [7, 8, 9]], k = 4
    Output: 6
    Explanation: Spiral sequence = [1, 2, 3, 6, 9, 8, 7, 4, 5].
    The 4th element is 6.

    Constraints:
    1 <= n, m <= 1000
    1 <= k <= n * m
    -10^9 <= mat[i][j] <= 10^9

    Expected Complexities:
    Time Complexity: O(K), stopping immediately as soon as K-th element is reached.
    Space Complexity: O(1), no extra space.

    Approach 1: Spiral Layer Traversal with Counter (Optimal O(K) - Striver & Love Babbar)
    Approach 2: Ring-by-Ring Layer Mathematical Reduction (O(N) / O(1) - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Maintain 4 boundary pointers:
       - `top = 0`, `bottom = n - 1`
       - `left = 0`, `right = m - 1`
    2. Maintain `count = 0` tracking the number of elements visited so far.
    3. In each outer loop iteration:
       - Step 1: Traverse `top` row from `left` to `right`. Increment `count`. If `count == k`, return element. `top++`.
       - Step 2: Traverse `right` column from `top` to `bottom`. Increment `count`. If `count == k`, return element. `right--`.
       - Step 3: If `top <= bottom`, traverse `bottom` row from `right` down to `left`. Increment `count`. If `count == k`, return element. `bottom--`.
       - Step 4: If `left <= right`, traverse `left` column from `bottom` down to `top`. Increment `count`. If `count == k`, return element. `left++`.
*/

#include <iostream>
#include <vector>

using namespace std;

// ============================================================================
// Approach 1: Spiral Layer Traversal with Counter (Optimal O(K) - Striver & Love Babbar)
// ============================================================================
class SolutionSpiralTraversal {
public:
    int findK(vector<vector<int>>& mat, int n, int m, int k) {
        int top = 0, bottom = n - 1;
        int left = 0, right = m - 1;

        int count = 0;

        while (top <= bottom && left <= right) {
            // Step 1: Traverse Top row (left to right)
            for (int j = left; j <= right; j++) {
                count++;
                if (count == k) return mat[top][j];
            }
            top++;

            // Step 2: Traverse Right column (top to bottom)
            for (int i = top; i <= bottom; i++) {
                count++;
                if (count == k) return mat[i][right];
            }
            right--;

            // Step 3: Traverse Bottom row (right to left)
            if (top <= bottom) {
                for (int j = right; j >= left; j--) {
                    count++;
                    if (count == k) return mat[bottom][j];
                }
                bottom--;
            }

            // Step 4: Traverse Left column (bottom to top)
            if (left <= right) {
                for (int i = bottom; i >= top; i--) {
                    count++;
                    if (count == k) return mat[i][left];
                }
                left++;
            }
        }

        return -1;
    }
};

// ============================================================================
// Approach 2: Ring-by-Ring Layer Mathematical Reduction (O(N) - Striver & Love Babbar)
// ============================================================================
class SolutionMathRing {
public:
    int findK(vector<vector<int>>& mat, int n, int m, int k) {
        int r = 0, c = 0;

        while (n > 0 && m > 0) {
            // Total elements in the current outer boundary ring
            int ringCount;
            if (n == 1) ringCount = m;
            else if (m == 1) ringCount = n;
            else ringCount = 2 * n + 2 * m - 4;

            // If k lies inside the current outer ring
            if (k <= ringCount) {
                // Top row
                if (k <= m) return mat[r][c + k - 1];
                // Right column
                if (k <= m + n - 1) return mat[r + (k - m)][c + m - 1];
                // Bottom row
                if (k <= 2 * m + n - 2) return mat[r + n - 1][c + m - 1 - (k - (m + n - 1))];
                // Left column
                return mat[r + n - 1 - (k - (2 * m + n - 2))][c];
            }

            // Move to inner submatrix ring
            k -= ringCount;
            r++;
            c++;
            n -= 2;
            m -= 2;
        }

        return -1;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    int findK(vector<vector<int>>& mat, int n, int m, int k) {
        SolutionSpiralTraversal solver;
        return solver.findK(mat, n, m, k);
    }

    int findK(vector<vector<int>>& mat, int k) {
        int n = mat.size();
        int m = mat[0].size();
        return findK(mat, n, m, k);
    }
};

int main() {
    // Example 1:
    // Expected Output: 13
    vector<vector<int>> mat1 = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    int n1 = 4, m1 = 4, k1 = 10;

    SolutionSpiralTraversal solver1;
    cout << "Example 1 10th Element (Spiral Traversal): " << solver1.findK(mat1, n1, m1, k1) << "\n";

    // Example 2:
    // Expected Output: 6
    vector<vector<int>> mat2 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int n2 = 3, m2 = 3, k2 = 4;

    SolutionMathRing solver2;
    cout << "Example 2 4th Element (Math Ring): " << solver2.findK(mat2, n2, m2, k2) << "\n";

    return 0;
}
