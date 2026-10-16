#include <iostream>
#include <vector>
#include <string>

using namespace std;

/**
 * Problem: Find if a string is interleaved of two other strings
 * 
 * Given three strings A, B, and C, determine whether C is formed by an interleaving 
 * of characters of A and B such that the relative order of characters in each string is preserved.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Unlike "14. LCS" where characters could be omitted,
 *   here EVERY single character from A and B MUST be used, and their combined lengths 
 *   must exactly equal length of C: len(A) + len(B) == len(C).
 * - Unlike Greedy (which gets trapped if A[i] == B[j] == C[k]), DP branches on both possibilities.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - 2D / 1D Space-Optimized Dynamic Programming:
 *   Let dp[i][j] be a boolean indicating whether C[0 ... i + j - 1] can be formed by 
 *   interleaving prefix A[0 ... i - 1] and prefix B[0 ... j - 1].
 *   
 *   Feasibility Check:
 *     If A.length() + B.length() != C.length(), return false immediately.
 *   
 *   Base Case:
 *     dp[0][0] = true (empty prefixes form empty C).
 *   
 *   Transitions for i in [0..M] and j in [0..N]:
 *     Character C[i + j - 1] can come from:
 *     1. String A (if i > 0, dp[i - 1][j] is true, and A[i - 1] == C[i + j - 1]).
 *     2. String B (if j > 0, dp[i][j - 1] is true, and B[j - 1] == C[i + j - 1]).
 *     
 *     dp[i][j] = (i > 0 && dp[i - 1][j] && A[i - 1] == C[i + j - 1]) ||
 *                (j > 0 && dp[i][j - 1] && B[j - 1] == C[i + j - 1])
 *   
 *   Space Optimization:
 *     Since row i only accesses row i - 1 and current row, space reduces to O(N) using a 1D vector!
 */

class Solution {
public:
    bool isInterleave(string A, string B, string C) {
        int m = A.length();
        int n = B.length();

        // Length mismatch check
        if (m + n != (int)C.length()) {
            return false;
        }

        // Space-optimized 1D boolean DP array of size n + 1
        vector<bool> dp(n + 1, false);

        // Base case: empty A and empty B
        dp[0] = true;

        // Initialize first row (i = 0, using only characters from B)
        for (int j = 1; j <= n; j++) {
            dp[j] = dp[j - 1] && (B[j - 1] == C[j - 1]);
        }

        for (int i = 1; i <= m; i++) {
            // First column of row i (using only characters from A)
            dp[0] = dp[0] && (A[i - 1] == C[i - 1]);

            for (int j = 1; j <= n; j++) {
                char target = C[i + j - 1];

                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Interleaving allows extending from A (from previous row: dp[j]) OR from B (from current row: dp[j - 1])
                bool from_A = dp[j] && (A[i - 1] == target);
                bool from_B = dp[j - 1] && (B[j - 1] == target);

                dp[j] = from_A || from_B;
            }
        }

        return dp[n];
    }
};

int main() {
    Solution sol;
    string A1 = "aabcc", B1 = "dbbca", C1 = "aadbbcbcac";
    cout << "Is \"" << C1 << "\" interleaved: " << (sol.isInterleave(A1, B1, C1) ? "YES" : "NO") << "\n";
    // Expected: YES

    string A2 = "aabcc", B2 = "dbbca", C2 = "aadbbbaccc";
    cout << "Is \"" << C2 << "\" interleaved: " << (sol.isInterleave(A2, B2, C2) ? "YES" : "NO") << "\n";
    // Expected: NO

    string A3 = "YX", B3 = "X", C3 = "XXY";
    cout << "Is \"" << C3 << "\" interleaved: " << (sol.isInterleave(A3, B3, C3) ? "YES" : "NO") << "\n";
    // Expected: NO

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(M * N) filling an M x N grid.
 * - Space Complexity: O(N) auxiliary space using a single 1D rolling vector.
 */
