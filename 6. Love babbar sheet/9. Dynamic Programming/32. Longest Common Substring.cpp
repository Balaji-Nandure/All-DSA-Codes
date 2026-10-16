#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/**
 * Problem: Longest Common Substring
 * 
 * Given two strings s1 and s2, find the length of their longest common substring.
 * A substring is a CONTIGUOUS sequence of characters within a string.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "14. Longest Common Subsequence (LCS)", characters could be skipped (non-contiguous).
 *   On mismatch, LCS carried over max(dp[i-1][j], dp[i][j-1]).
 * - In Longest Common Substring, characters MUST be contiguous!
 *   Therefore, on mismatch: dp[i][j] = 0 (the contiguous chain is instantly broken!).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Dynamic Programming (Prefix-Contiguity Recurrence):
 *   Let dp[i][j] be the length of the common substring ending AT EXACTLY s1[i-1] and s2[j-1].
 *   
 *   Transitions for 1 <= i <= n, 1 <= j <= m:
 *     If s1[i-1] == s2[j-1]:
 *       dp[i][j] = 1 + dp[i-1][j-1]
 *       max_len = max(max_len, dp[i][j])
 *     Else:
 *       dp[i][j] = 0   <-- *** CRUCIAL LINE: Chain reset on mismatch ***
 *   
 *   Space Optimization to O(min(M, N)):
 *     Notice that dp[i][j] only references dp[i-1][j-1].
 *     By traversing j BACKWARD from m down to 1, a single 1D array can be updated in-place!
 */

class Solution {
public:
    int longestCommonSubstr(string s1, string s2) {
        int n = s1.length();
        int m = s2.length();

        // 2D DP table
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        int max_len = 0;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                    // Contiguous extension from previous adjacent character match
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                    max_len = max(max_len, dp[i][j]);
                } else {
                    // *** CRUCIAL LINE: Reset to 0 because contiguity is broken ***
                    dp[i][j] = 0;
                }
            }
        }

        return max_len;
    }

    // Space-Optimized O(M) version
    int longestCommonSubstrOptimized(string s1, string s2) {
        if (s1.length() < s2.length()) swap(s1, s2);
        int n = s1.length();
        int m = s2.length();

        vector<int> dp(m + 1, 0);
        int max_len = 0;

        for (int i = 1; i <= n; i++) {
            for (int j = m; j >= 1; j--) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[j] = 1 + dp[j - 1];
                    max_len = max(max_len, dp[j]);
                } else {
                    dp[j] = 0;
                }
            }
        }

        return max_len;
    }
};

int main() {
    Solution sol;
    string s1 = "ABCDGH", s2 = "ACDGHR";
    cout << "Longest Common Substring: " << sol.longestCommonSubstr(s1, s2) << "\n";
    // Common substring "CDGH" has length 4. Expected: 4.

    string s3 = "ABC", s4 = "ACB";
    cout << "Longest Common Substring: " << sol.longestCommonSubstr(s3, s4) << "\n";
    // Substring length 1 ("A", "B", or "C"). Expected: 1.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N * M) iterating through all pairs.
 * - Space Complexity: O(N * M) for 2D DP; O(min(N, M)) for 1D backward version.
 */
