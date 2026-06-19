/*
GeeksforGeeks: Longest Repeating Subsequence
Difficulty: Medium

Problem:
Given string str, find the length of the longest repeating subsequence such that it can be found twice in the given string.
The two identified subsequences A and B can use the same ith character from string s if and only if that ith character has different indices in A and B.

Examples:
Input: s = "axxzxy"
Output: 2
Explanation: The longest repeating subsequence is "xx".

Input: s = "axxxy"
Output: 2
Explanation: The longest repeating subsequence is "xx".

Constraints:
1 <= s.size() <= 10^3

Core Idea:
This problem is a classic variation of the Longest Common Subsequence (LCS) problem.
We want to find the LCS of string `str` with itself, but with a constraint:
- Two characters `str[i - 1]` and `str[j - 1]` can match only if they are at different indices in the original string (i.e. `i != j`).
- Thus, the recurrence relation becomes:
  - If `str[i - 1] == str[j - 1]` and `i != j`: `dp[i][j] = 1 + dp[i - 1][j - 1]`
  - Else: `dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])`

Approach:
1. Initialize a 2D DP array `dp` of size `(n + 1) x (n + 1)` with all values as 0, where `n` is the length of `str`.
2. Loop `i` from 1 to `n` and `j` from 1 to `n`:
   - If `str[i - 1] == str[j - 1]` and `i != j`, update `dp[i][j] = 1 + dp[i - 1][j - 1]`.
   - Else, update `dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])`.
3. Return `dp[n][n]`.

Time Complexity: O(N^2) where N is the length of the string `str`.
Space Complexity: O(N^2) to store the 2D DP grid.

GFG Link: https://www.geeksforgeeks.org/problems/longest-repeating-subsequence2007/1
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int LongestRepeatingSubsequence(string str) {
        int n = str.length();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                // Characters must match and must be from different original indices
                if (str[i - 1] == str[j - 1] && i != j) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        return dp[n][n];
    }
};

/*
Dry Run — Example:
str = "axxzxy", n = 6

DP Table layout (showing matches where i != j):
- i=1 ('a'), j=1..6 -> no match under i != j
- i=2 ('x' at 1), matches j=3 ('x' at 2) and j=5 ('x' at 4):
  - dp[2][3] = 1 + dp[1][2] = 1
  - dp[2][5] = 1 + dp[1][4] = 1
- i=3 ('x' at 2), matches j=2 ('x' at 1) and j=5 ('x' at 4):
  - dp[3][2] = 1 + dp[2][1] = 1
  - dp[3][5] = 1 + dp[2][4] = 1 + dp[2][3] = 2 (since dp[2][3] = 1)
- ...
Eventually, dp[6][6] will evaluate to 2.
Output: 2 (representing repeating subsequence "xx").
*/
