#include <iostream>
#include <vector>
#include <string>

using namespace std;

/**
 * Problem: Count All Palindromic Subsequences in a given String
 * 
 * Given a string str of length N, find the total count of palindromic subsequences 
 * (need not be distinct in characters, but distinct in chosen index sets) modulo 10^9 + 7.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "41. Longest Palindromic Subsequence", we maximized the LENGTH of one palindrome.
 * - Here, we must COUNT all valid palindromic subsequences using Inclusion-Exclusion!
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Interval Dynamic Programming with Principle of Inclusion-Exclusion:
 *   Let dp[i][j] be the count of palindromic subsequences in substring str[i ... j].
 *   
 *   Base Case:
 *     dp[i][i] = 1 (every individual character forms 1 palindromic subsequence of length 1).
 *   
 *   Transitions for substring str[i ... j]:
 *     By Inclusion-Exclusion on the sub-intervals:
 *     - Count in str[i+1 ... j]: dp[i+1][j]
 *     - Count in str[i ... j-1]: dp[i][j-1]
 *     - Overlap counted twice:   dp[i+1][j-1]
 *     
 *     Case 1: If str[i] == str[j]:
 *       Endpoints match! They can enclose ANY palindromic subsequence inside str[i+1 ... j-1] 
 *       to form a new longer palindrome (+ dp[i+1][j-1] ways).
 *       Additionally, the two endpoints themselves form a new palindrome of length 2 (+ 1 way).
 *       Therefore:
 *       dp[i][j] = dp[i+1][j] + dp[i][j-1] - dp[i+1][j-1] + (dp[i+1][j-1] + 1)
 *                = 1 + dp[i+1][j] + dp[i][j-1]
 *     
 *     Case 2: If str[i] != str[j]:
 *       Endpoints do not match; no palindrome can use both str[i] and str[j]:
 *       dp[i][j] = dp[i+1][j] + dp[i][j-1] - dp[i+1][j-1]
 *   
 *   Modulo Arithmetic:
 *     Always add MOD before taking `% MOD` when subtracting to avoid negative numbers!
 */

class Solution {
    const long long MOD = 1e9 + 7;
public:
    long long int countPS(string str) {
        int n = str.length();
        vector<vector<long long>> dp(n, vector<long long>(n, 0));

        // Base case: Length 1 substrings
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;
        }

        // Substrings of length L from 2 to n
        for (int L = 2; L <= n; L++) {
            for (int i = 0; i <= n - L; i++) {
                int j = i + L - 1;

                if (str[i] == str[j]) {
                    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                    // When endpoints match, 1 + dp[i+1][j] + dp[i][j-1]
                    dp[i][j] = (1 + dp[i + 1][j] + dp[i][j - 1]) % MOD;
                } else {
                    // *** CRUCIAL LINE: When endpoints differ, Inclusion-Exclusion subtracts the double-counted middle ***
                    dp[i][j] = (dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1] + MOD) % MOD;
                }
            }
        }

        return dp[0][n - 1];
    }
};

int main() {
    Solution sol;
    string s1 = "abcd";
    cout << "Palindromic Subsequences in \"" << s1 << "\": " << sol.countPS(s1) << "\n";
    // Expected: 4 ('a', 'b', 'c', 'd')

    string s2 = "aab";
    cout << "Palindromic Subsequences in \"" << s2 << "\": " << sol.countPS(s2) << "\n";
    // Expected: 4 ('a', 'a', 'b', 'aa')

    string s3 = "aaaa";
    cout << "Palindromic Subsequences in \"" << s3 << "\": " << sol.countPS(s3) << "\n";
    // All 2^4 - 1 = 15 non-empty subsequences are palindromes! Expected: 15.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N^2) filling an upper-triangular N x N matrix.
 * - Space Complexity: O(N^2) for the 2D DP matrix.
 */
