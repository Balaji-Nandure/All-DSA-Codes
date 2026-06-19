/*
GeeksforGeeks: Shortest Common Supersequence
Difficulty: Medium

Problem:
Given two strings s1 and s2, find the length of the smallest string which has both s1 and s2 as its sub-sequences.
Note: s1 and s2 can have both uppercase and lowercase English letters.

Examples:
Input: s1 = "geek", s2 = "eke"
Output: 5
Explanation: String "geeke" has both string "geek" and "eke" as subsequences.

Input: s1 = "AGGTAB", s2 = "GXTXAYB"
Output: 9
Explanation: String "AGXGTXAYB" has both string "AGGTAB" and "GXTXAYB" as subsequences.

Input: s1 = "geek", s2 = "ek"
Output: 4
Explanation: String "geek" has both string "geek" and "ek" as subsequences.

Constraints:
1 <= s1.size(), s2.size() <= 500

Core Idea:
The shortest common supersequence (SCS) of two strings s1 and s2 is a string that contains both s1 and s2 as subsequences.
The length of SCS is given by the formula:
`Length(SCS) = length(s1) + length(s2) - length(LCS(s1, s2))`
where `LCS(s1, s2)` is the Longest Common Subsequence of s1 and s2.
By identifying the longest sequence of characters that are common and in the same order (LCS), we only need to write those common characters once in the supersequence, while writing the remaining unique characters of s1 and s2 alongside them.

Approach:
1. Use dynamic programming to find the length of LCS of two strings `X` and `Y` of lengths `m` and `n`.
2. Construct a 2D DP array `dp` of size `(m + 1) x (n + 1)` initialized to 0.
3. Fill the DP array:
   - If `X[i - 1] == Y[j - 1]`, then `dp[i][j] = 1 + dp[i - 1][j - 1]`.
   - Else, `dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])`.
4. The length of LCS is `dp[m][n]`.
5. Return `m + n - dp[m][n]`.

Time Complexity: O(M * N) where M and N are the lengths of the two strings.
Space Complexity: O(M * N) to store the 2D DP table.

GFG Link: https://www.geeksforgeeks.org/problems/shortest-common-supersequence0322/1
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Function to find length of shortest common supersequence of two strings.
    int shortestCommonSupersequence(string X, string Y, int m, int n) {
        // dp[i][j] will store the length of LCS of X[0..i-1] and Y[0..j-1]
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (X[i - 1] == Y[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        int lcsLength = dp[m][n];
        return m + n - lcsLength;
    }
};

/*
Dry Run — Example:
X = "geek", Y = "eke", m = 4, n = 3

DP Grid:
     -   e   k   e
 - [ 0   0   0   0 ]
 g [ 0   0   0   0 ]
 e [ 0   1   1   1 ]
 e [ 0   1   1   2 ]
 k [ 0   1   2   2 ]

LCS length = dp[4][3] = 2  (which corresponds to "ek" or "ee")
SCS length = m + n - LCS length = 4 + 3 - 2 = 5
SCS string: "geeke" (contains "geek" and "eke" as subsequences)
*/
