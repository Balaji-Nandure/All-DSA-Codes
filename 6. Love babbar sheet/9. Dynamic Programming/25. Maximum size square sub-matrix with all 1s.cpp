#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Problem: Maximum size square sub-matrix with all 1s
 * 
 * Given a binary matrix of dimensions N x M, find the maximum side length 
 * of a square sub-matrix composed entirely of 1s.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Unlike "10. Gold Mine" where we tracked path sums,
 *   here we determine geometric 2D contiguous structural validity (squares).
 * - A square requires uniform expansion in both dimensions simultaneously:
 *   width = height = S.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - 2D Dynamic Programming (Corner-Expansion Recurrence):
 *   Let dp[i][j] represent the side length of the largest square of all 1s 
 *   whose BOTTOM-RIGHT corner is positioned at cell (i, j).
 *   
 *   Base Case:
 *     If mat[i][j] == 0: dp[i][j] = 0.
 *     If i == 0 or j == 0 (boundary rows/cols): dp[i][j] = mat[i][j].
 *   
 *   Transitions for i >= 1 and j >= 1:
 *     If mat[i][j] == 1:
 *       dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]})
 *   
 *   Why MIN of Top, Left, and Diagonal?
 *     For a cell (i, j) to expand a square of size S, ALL THREE surrounding regions:
 *     - The square above it: dp[i-1][j]
 *     - The square to its left: dp[i][j-1]
 *     - The square top-left diagonally: dp[i-1][j-1]
 *     MUST have side length at least S - 1!
 *     The weakest (minimum) of the three acts as the bottleneck limiting expansion.
 *   
 *   Space Optimization:
 *     Row i only depends on row i - 1 and the current row, enabling O(M) space.
 */

class Solution {
public:
    int maxSquare(int n, int m, vector<vector<int>>& mat) {
        vector<vector<int>> dp(n, vector<int>(m, 0));
        int max_side = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mat[i][j] == 1) {
                    if (i == 0 || j == 0) {
                        dp[i][j] = 1;
                    } else {
                        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                        // Square expansion bottlenecked by minimum of top, left, and diagonal neighbors
                        dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
                    }
                    max_side = max(max_side, dp[i][j]);
                }
            }
        }

        return max_side;
    }

    // Space-optimized O(M) version
    int maxSquareOptimized(int n, int m, vector<vector<int>>& mat) {
        vector<int> dp(m, 0);
        int max_side = 0;
        int prev_diag = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int temp = dp[j]; // stores dp[i-1][j]
                if (mat[i][j] == 1) {
                    if (i == 0 || j == 0) {
                        dp[j] = 1;
                    } else {
                        dp[j] = 1 + min({dp[j], dp[j - 1], prev_diag});
                    }
                    max_side = max(max_side, dp[j]);
                } else {
                    dp[j] = 0;
                }
                prev_diag = temp;
            }
        }

        return max_side;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> mat1 = {
        {0, 1, 1, 0, 1},
        {1, 1, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0}
    };
    int n1 = mat1.size(), m1 = mat1[0].size();
    cout << "Max Square Side: " << sol.maxSquare(n1, m1, mat1) << "\n"; // Expected: 3
    cout << "Max Square Side (Optimized): " << sol.maxSquareOptimized(n1, m1, mat1) << "\n";

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N * M) visiting every cell once.
 * - Space Complexity: O(N * M) for 2D DP; O(M) for optimized 1D version.
 */
