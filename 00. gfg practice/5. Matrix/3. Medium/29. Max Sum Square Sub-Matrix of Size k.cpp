/*
    Problem Name: Max Sum Square Sub-Matrix of Size k
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given an n x n grid mat[][] of integers where values can be negative, find the maximum sum among all
    possible k x k sub-grids.

    Examples:
    Input: k = 3, mat[][] = [[1, 2, -1, 4],
                            [-8, -3, 4, 2],
                            [3, 8, 10, -8],
                            [-4, -1, 1, 7]]
    Output: 20
    Explanation: The 3x3 sub-grid from (1,1) to (3,3) has sum = 20.

    Input: k = 1, mat[][] = [[4]]
    Output: 4

    Constraints:
    1 <= n <= 1000
    1 <= k <= n
    -1000 <= mat[i][j] <= 1000

    Expected Complexities:
    Time Complexity: O(N^2), precomputing 2D Prefix Sum matrix.
    Space Complexity: O(N^2), for 2D Prefix Sum matrix.

    Approach 1: Brute Force (O(N^2 * K^2) Time, O(1) Space - Striver & Love Babbar)
    Approach 2: 2D Prefix Sum Precomputation (Optimal O(N^2) Time, O(N^2) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Brute Force (Approach 1):
       - Try every possible k x k submatrix.
       - For each starting top-left position (i, j) where `0 <= i, j <= n - k`, iterate through all its
         k x k elements to compute the sum.
       - Time: O(N^2 * K^2), Space: O(1).
    2. 2D Prefix Sum (Approach 2):
       - Eliminate redundant overlap calculations by building a 2D Prefix Sum matrix `prefix[n+1][n+1]`.
       - `prefix[i][j]` stores the sum of the rectangle from `(0, 0)` to `(i-1, j-1)`.
       - Recurrence: `prefix[i + 1][j + 1] = mat[i][j] + prefix[i][j + 1] + prefix[i + 1][j] - prefix[i][j]`.
       - Any k x k submatrix sum starting at `(i, j)` is queried in O(1):
         `sum = prefix[i + k][j + k] - prefix[i][j + k] - prefix[i + k][j] + prefix[i][j]`.
       - Time: O(N^2), Space: O(N^2).
*/

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

// ============================================================================
// Approach 1: Brute Force (O(N^2 * K^2) Time, O(1) Space - Striver & Love Babbar)
// ============================================================================
class SolutionBruteForce {
public:
    int maxSumSubmatrix(vector<vector<int>>& mat, int k) {
        int n = mat.size();
        int ans = INT_MIN;

        for (int i = 0; i <= n - k; i++) {
            for (int j = 0; j <= n - k; j++) {
                int sum = 0;

                // Calculate sum of current k x k submatrix
                for (int x = i; x < i + k; x++) {
                    for (int y = j; y < j + k; y++) {
                        sum += mat[x][y];
                    }
                }

                ans = max(ans, sum);
            }
        }

        return ans;
    }
};

// ============================================================================
// Approach 2: 2D Prefix Sum (Optimal O(N^2) Time, O(N^2) Space - Striver & Love Babbar)
// ============================================================================
class SolutionPrefixSum {
public:
    int maxSumSubmatrix(vector<vector<int>>& mat, int k) {
        int n = mat.size();

        vector<vector<int>> prefix(n + 1, vector<int>(n + 1, 0));

        // Build 2D prefix sum
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                prefix[i + 1][j + 1] = mat[i][j]
                                     + prefix[i][j + 1]
                                     + prefix[i + 1][j]
                                     - prefix[i][j];
            }
        }

        int ans = INT_MIN;

        // Try every k x k submatrix
        for (int i = 0; i <= n - k; i++) {
            for (int j = 0; j <= n - k; j++) {
                int sum = prefix[i + k][j + k]
                        - prefix[i][j + k]
                        - prefix[i + k][j]
                        + prefix[i][j];

                ans = max(ans, sum);
            }
        }

        return ans;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& mat, int k) {
        SolutionPrefixSum solver;
        return solver.maxSumSubmatrix(mat, k);
    }

    int MaximumSum(vector<vector<int>>& mat, int k) {
        return maxSumSubmatrix(mat, k);
    }
};

int main() {
    // Example 1:
    // Expected Output: 20
    vector<vector<int>> mat1 = {
        {1, 2, -1, 4},
        {-8, -3, 4, 2},
        {3, 8, 10, -8},
        {-4, -1, 1, 7}
    };
    int k1 = 3;

    SolutionBruteForce solver1;
    cout << "Example 1 (Brute Force O(N^2 * K^2)): " << solver1.maxSumSubmatrix(mat1, k1) << "\n";

    SolutionPrefixSum solver2;
    cout << "Example 1 (2D Prefix Sum O(N^2)): " << solver2.maxSumSubmatrix(mat1, k1) << "\n";

    // Example 2:
    // Expected Output: 4
    vector<vector<int>> mat2 = {
        {4}
    };
    int k2 = 1;

    cout << "Example 2 (2D Prefix Sum): " << solver2.maxSumSubmatrix(mat2, k2) << "\n";

    return 0;
}
