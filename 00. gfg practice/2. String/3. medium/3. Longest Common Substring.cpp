/*
GeeksforGeeks: Longest Common Substring
Difficulty: Medium

Problem:
Given two strings s1 and s2, determine the length of the longest substring that appears in both strings.

Examples:
Input: s1 = "ABCDGH", s2 = "ACDGHR"
Output: 4
Explanation: The longest common substring is "CDGH" with a length of 4.

Input: s1 = "abc", s2 = "acb"
Output: 1
Explanation: The longest common substrings are "a", "b", "c" all having length 1.

Input: s1 = "YZ", s2 = "yz"
Output: 0
Explanation: Comparison is case-sensitive, so 'Y' ≠ 'y' and 'Z' ≠ 'z'. Hence, no common substring exists.

Core Idea:
This is a classic Dynamic Programming problem. 
Let `dp[i][j]` be the length of the longest common substring ending exactly at index `i-1` of `s1` and index `j-1` of `s2`.
If `s1[i-1] == s2[j-1]`, then `dp[i][j] = dp[i-1][j-1] + 1`.
If they do not match, the common substring is broken, so `dp[i][j] = 0`.
The maximum value anywhere in this DP table will be our final answer.

Optimization:
Notice that to compute the current row `dp[i]`, we only ever need values from the strictly previous row `dp[i-1]`.
Because of this, we do not need the entire massive 2D table! We can optimize this to use a single 1D array `dp` of size `m + 1`.
To ensure we don't accidentally overwrite `dp[j-1]` before we need it to calculate `dp[j]`, we simply iterate `j` backwards from `m` down to `1`.
When there is no match, we must explicitly set `dp[j] = 0` to reset the contiguous streak.

Approach:
1. Let `n` be the length of `s1` and `m` be the length of `s2`.
2. Initialize a 1D vector `dp` of size `m + 1` with all zeros.
3. Keep a `max_len` variable initialized to 0.
4. Iterate `i` from 1 to `n`:
   - Iterate `j` backwards from `m` down to 1:
     - If `s1[i - 1] == s2[j - 1]`, then `dp[j] = dp[j - 1] + 1`, and update `max_len = max(max_len, dp[j])`.
     - Else, `dp[j] = 0` (breaks the contiguous substring).
5. Return `max_len`.

Time Complexity: O(N * M), where N and M are the lengths of the two strings. We iterate through every character pair exactly once.
Space Complexity: O(M) auxiliary space, as we heavily optimized the DP table down to a single 1D array.

GFG Link: https://www.geeksforgeeks.org/problems/longest-common-substring1452/1
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int longestCommonSubstr(string s1, string s2) {
        int n = s1.length();
        int m = s2.length();
        
        // 1D DP array for intense space optimization
        vector<int> dp(m + 1, 0);
        int max_len = 0;
        
        for (int i = 1; i <= n; i++) {
            // Traverse backwards to avoid overwriting dp[j-1] before we use it
            for (int j = m; j >= 1; j--) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[j] = dp[j - 1] + 1;
                    max_len = max(max_len, dp[j]);
                } else {
                    // Reset to 0 since the contiguous substring breaks
                    dp[j] = 0;
                }
            }
        }
        
        return max_len;
    }
};

/*
Dry Run — Example 1 Simplified:
Input: s1 = "ABC", s2 = "ABC"
n = 3, m = 3. 
dp array initialized: [0, 0, 0, 0]

i = 1 ('A'):
  j = 3..1: matches at j=1 ('A').
  dp[1] = dp[0] + 1 = 1.
  max_len = 1.
  dp = [0, 1, 0, 0]

i = 2 ('B'):
  j = 3..1: matches at j=2 ('B').
  dp[2] = dp[1] + 1 = 1 + 1 = 2.
  max_len = 2.
  j=1 ('A'!='B'), so dp[1] = 0.
  dp = [0, 0, 2, 0]

i = 3 ('C'):
  j = 3..1: matches at j=3 ('C').
  dp[3] = dp[2] + 1 = 2 + 1 = 3.
  max_len = 3.
  j=2 ('B'!='C'), so dp[2] = 0.
  dp = [0, 0, 0, 3]

Return max_len = 3.
*/
