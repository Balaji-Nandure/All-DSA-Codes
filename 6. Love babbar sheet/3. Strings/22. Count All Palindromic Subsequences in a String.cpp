// Problem: Count All Palindromic Subsequences in a Given String
// Link (GFG): https://www.geeksforgeeks.org/problems/count-palindromic-subsequences/1
// Article: https://www.geeksforgeeks.org/dsa/count-palindromic-subsequence-given-string/
// Difficulty: Hard
// Topic: String, Dynamic Programming, Principle of Inclusion-Exclusion

/*
Problem Statement:
Given a string str of length N, find the total number of palindromic subsequences 
(need not be distinct) present in the string.
Since the answer can be very large, return it modulo 10^9 + 7.

Note: A subsequence is a sequence that can be derived from another sequence by deleting 
zero or more elements without changing the order of the remaining elements.

Example 1:
Input: str = "abcd"
Output: 4
Explanation: The 4 palindromic subsequences of length 1 are "a", "b", "c", "d".

Example 2:
Input: str = "aab"
Output: 4
Explanation: The palindromic subsequences are "a", "a", "b", and "aa".

Example 3:
Input: str = "b"
Output: 1

Constraints:
- 1 <= str.length() <= 1000
- str consists of lowercase English letters.
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 8 (Longest Palindromic Substring):
//   * Characters had to be strictly CONTIGUOUS (substring).
// - In Problem 22 (Count Palindromic Subsequences):
//   * Characters can be NON-CONTIGUOUS (subsequence).
//   * We do not just find the longest one; we must COUNT ALL OF THEM!
//   * The key is the Principle of Inclusion-Exclusion on overlapping subproblems 
//     `dp[i+1][j]` and `dp[i][j-1]`.

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// 2D Interval Dynamic Programming:
//   - Let `dp[i][j]` = number of palindromic subsequences in substring `str[i .. j]`.
//   - Base Cases:
//       * Length 1 (`i == j`): `dp[i][i] = 1`.
//   - For substring `str[i .. j]` of length >= 2:
//       * Case 1: If `str[i] != str[j]`:
//           By Inclusion-Exclusion:
//           `dp[i][j] = dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1]`
//           (Add subsequences excluding str[i], add excluding str[j], and subtract 
//            their shared intersection which was double-counted).
//
//       * Case 2: If `str[i] == str[j]`:
//           All palindromes from Case 1 STILL EXIST.
//           In addition:
//           1. Every palindrome inside `str[i+1 .. j-1]` can be prefixed by `str[i]` 
//              and suffixed by `str[j]` to form a NEW palindrome -> `+ dp[i+1][j-1]`.
//           2. The two-character palindrome `"str[i]str[j]"` itself -> `+ 1`.
//           Combining:
//           `dp[i][j] = (dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1]) + dp[i + 1][j - 1] + 1`
//                     = `dp[i + 1][j] + dp[i][j - 1] + 1`!
//           (The double-counted intersection cancels out completely!).
//
//   - Complexity: O(N^2) time, O(N^2) space.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    long long int countPS(string str) {
        int n = str.length();
        long long MOD = 1e9 + 7;

        // dp[i][j] stores the count of palindromic subsequences in str[i..j]
        vector<vector<long long>> dp(n, vector<long long>(n, 0));

        // Base case: Substrings of length 1
        for (int i = 0; i < n; ++i) {
            dp[i][i] = 1;
        }

        // Interval DP: Process lengths from 2 to n
        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i <= n - len; ++i) {
                int j = i + len - 1;

                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Inclusion-Exclusion Branch:
                // When boundary characters match, they can enclose all inner palindromes (+ dp[i+1][j-1])
                // and form "str[i]str[j]" (+ 1), canceling out the subtracted intersection!
                if (str[i] == str[j]) {
                    dp[i][j] = (dp[i + 1][j] + dp[i][j - 1] + 1) % MOD;
                } else {
                    // When boundary characters differ, subtract the double-counted middle region
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
    cout << "Count PS for \"" << s1 << "\": " << sol.countPS(s1) << "\n";

    string s2 = "aab";
    cout << "Count PS for \"" << s2 << "\": " << sol.countPS(s2) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N^2), solving all sub-intervals of length 2 to N.
- Space Complexity: O(N^2) auxiliary space for the DP table.

Key Takeaways:
- The algebraic cancellation `(- dp[i+1][j-1] + dp[i+1][j-1])` when boundary characters match
  is one of the most elegant examples of mathematical simplification in Dynamic Programming.
*/
