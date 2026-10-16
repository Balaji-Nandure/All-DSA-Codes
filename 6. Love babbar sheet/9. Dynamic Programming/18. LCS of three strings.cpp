#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/**
 * Problem: LCS of three strings
 * 
 * Given three strings A, B, and C, find the length of their Longest Common Subsequence.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "14. Longest Common Subsequence", we had 2 strings with a 2D state space (i, j).
 * - Here, we have THREE strings, extending the state space to 3 dimensions (i, j, k).
 * - Crucial Pitfall: You CANNOT simply find LCS(A, B) and then find LCS(result, C)!
 *   Counter-example: A = "abac", B = "cab", C = "cba".
 *   LCS(A, B) could be "ab" or "cb". If we pick "ab", LCS("ab", C) = "b" (length 1).
 *   However, "ba" is common to all three (length 2)!
 *   Therefore, all three strings MUST be processed simultaneously in 3D DP.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - 3D Dynamic Programming:
 *   Let dp[i][j][k] be the length of LCS of A[0...i-1], B[0...j-1], and C[0...k-1].
 *   
 *   Base Case:
 *     dp[0][j][k] = dp[i][0][k] = dp[i][j][0] = 0.
 *   
 *   Transitions for 1 <= i <= n1, 1 <= j <= n2, 1 <= k <= n3:
 *     If A[i-1] == B[j-1] && B[j-1] == C[k-1]:
 *       All 3 characters match!
 *       dp[i][j][k] = 1 + dp[i-1][j-1][k-1]
 *     Else:
 *       At least one string's current character must be discarded:
 *       dp[i][j][k] = max({
 *         dp[i-1][j][k],   // Drop from A
 *         dp[i][j-1][k],   // Drop from B
 *         dp[i][j][k-1]    // Drop from C
 *       })
 */

class Solution {
public:
    int LCSof3(string A, string B, string C, int n1, int n2, int n3) {
        // 3D DP table of size (n1 + 1) x (n2 + 1) x (n3 + 1)
        vector<vector<vector<int>>> dp(n1 + 1, vector<vector<int>>(n2 + 1, vector<int>(n3 + 1, 0)));

        for (int i = 1; i <= n1; i++) {
            for (int j = 1; j <= n2; j++) {
                for (int k = 1; k <= n3; k++) {
                    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                    // Simultaneous character equality across all three strings
                    if (A[i - 1] == B[j - 1] && B[j - 1] == C[k - 1]) {
                        dp[i][j][k] = 1 + dp[i - 1][j - 1][k - 1];
                    } else {
                        // Discard from string A, B, or C
                        dp[i][j][k] = max({dp[i - 1][j][k], dp[i][j - 1][k], dp[i][j][k - 1]});
                    }
                }
            }
        }

        return dp[n1][n2][n3];
    }
};

int main() {
    Solution sol;
    string A = "geeks", B = "geeksfor", C = "geeksforgeeks";
    cout << "LCS of 3 strings: " << sol.LCSof3(A, B, C, A.length(), B.length(), C.length()) << "\n";
    // Expected: 5 ("geeks")

    string A2 = "abcd1e2", B2 = "bc12ea", C2 = "bd1ea";
    cout << "LCS of 3 strings: " << sol.LCSof3(A2, B2, C2, A2.length(), B2.length(), C2.length()) << "\n";
    // Common: "b1e" (length 3)

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N1 * N2 * N3) iterating through the 3D tensor once.
 * - Space Complexity: O(N1 * N2 * N3) for the 3D DP table (can be optimized to O(N2 * N3) using two 2D layers).
 */
