#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/**
 * Problem: Longest Palindromic Subsequence (LPS)
 * 
 * Given a string S, find the length of the longest palindromic subsequence in S.
 * A subsequence is palindromic if it reads the same backwards as forwards.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Unlike "43. Longest Palindromic Substring", here characters do NOT need to be contiguous!
 * - Unlike "14. LCS" which compared two independent strings, LPS is evaluated on a single string.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Method 1: The Brilliant Reduction to LCS (LPS(S) = LCS(S, reverse(S))):
 *   Theorem:
 *     A subsequence of S that reads the same in forward order and reverse order 
 *     is by definition common to BOTH S and reverse(S)!
 *     Therefore, finding the Longest Palindromic Subsequence of S is IDENTICAL 
 *     to computing the Longest Common Subsequence between S and its reverse!
 *   
 * - Method 2: Direct Interval Dynamic Programming:
 *   Let dp[i][j] be the length of LPS in substring S[i ... j].
 *   
 *   Base Case:
 *     dp[i][i] = 1 (every single character is a palindrome of length 1).
 *   
 *   Transitions for length L from 2 to N:
 *     Let j = i + L - 1.
 *     If S[i] == S[j]:
 *       dp[i][j] = 2 + (i + 1 <= j - 1 ? dp[i + 1][j - 1] : 0)
 *     Else:
 *       dp[i][j] = max(dp[i + 1][j], dp[i][j - 1])
 *   
 *   Space Optimization:
 *     Method 1 using space-optimized LCS runs in O(N^2) time and strictly O(N) space.
 */

class Solution {
public:
    // Method 1: Space-Optimized LCS(S, reverse(S)) in O(N) Space
    int longestPalinSubseq(string A) {
        string B = A;
        reverse(B.begin(), B.end());

        int n = A.length();
        vector<int> prev(n + 1, 0);
        vector<int> curr(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (A[i - 1] == B[j - 1]) {
                    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                    // S matching its reverse extends the palindromic boundary from both ends
                    curr[j] = 1 + prev[j - 1];
                } else {
                    curr[j] = max(prev[j], curr[j - 1]);
                }
            }
            prev = curr;
        }

        return prev[n];
    }

    // Method 2: Direct Interval DP
    int longestPalinSubseqInterval(string s) {
        int n = s.length();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // Base case: Length 1 substrings
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;
        }

        // Lengths from 2 to n
        for (int L = 2; L <= n; L++) {
            for (int i = 0; i <= n - L; i++) {
                int j = i + L - 1;
                if (s[i] == s[j]) {
                    // *** CRUCIAL LINE: Matching endpoints contribute 2 to inner LPS ***
                    dp[i][j] = 2 + (L == 2 ? 0 : dp[i + 1][j - 1]);
                } else {
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }

        return dp[0][n - 1];
    }
};

int main() {
    Solution sol;
    string s1 = "bbbab";
    cout << "LPS Length 1: " << sol.longestPalinSubseq(s1) << "\n"; // Expected: 4 ("bbbb")

    string s2 = "cbbd";
    cout << "LPS Length 2: " << sol.longestPalinSubseq(s2) << "\n"; // Expected: 2 ("bb")

    string s3 = "geeksforgeeks";
    cout << "LPS Length 3: " << sol.longestPalinSubseq(s3) << "\n"; // Expected: 5 ("eefee" or "eekee")

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N^2) where N is string length.
 * - Space Complexity: O(N) using space-optimized LCS reduction; O(N^2) for interval DP.
 */
