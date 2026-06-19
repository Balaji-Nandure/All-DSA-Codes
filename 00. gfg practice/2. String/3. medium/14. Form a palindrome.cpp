/*
GeeksforGeeks: Form a palindrome
Difficulty: Medium

Problem:
Given a string s, the task is to find the minimum number of characters to be inserted to convert it to a palindrome.

Examples:
Input: s = "abcd"
Output: 3
Explanation: Here we can append 3 characters in the beginning and the resultant string will be a palindrome "dcbabcd".

Input: s = "aba"
Output: 0
Explanation: Given string is already a palindrome hence no insertions are required.

Constraints:
1 <= s.size() <= 500

Core Idea:
To convert a string `s` into a palindrome with the minimum number of insertions:
- We can find the Longest Palindromic Subsequence (LPS) of the string.
- Any character that is already part of the LPS does not need to be matched by insertion.
- The remaining characters (which are not part of the LPS) must each be paired with an insertion.
- Thus, the minimum number of insertions is:
  `Insertions = Length(s) - Length(LPS(s))`
- The Longest Palindromic Subsequence `LPS(s)` is equivalent to the Longest Common Subsequence (LCS) between `s` and its reversed string `rev(s)`.

Approach:
1. Store a reversed copy of `s` in `rev`.
2. Compute the LCS between `s` and `rev` using a 2D DP array of size `(n + 1) x (n + 1)`:
   - If `s[i-1] == rev[j-1]`, then `dp[i][j] = 1 + dp[i-1][j-1]`.
   - Else, `dp[i][j] = max(dp[i-1][j], dp[i][j-1])`.
3. The length of LPS is `dp[n][n]`.
4. Return `n - dp[n][n]`.

Time Complexity: O(N^2) where N is the length of string `s`.
Space Complexity: O(N^2) to store the 2D DP table.

GFG Link: https://www.geeksforgeeks.org/problems/form-a-palindrome1455/1
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findMinInsertions(string s) {
        int n = s.length();
        string rev = s;
        reverse(rev.begin(), rev.end());
        
        // dp[i][j] will store the LCS of s[0..i-1] and rev[0..j-1]
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == rev[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        int lpsLength = dp[n][n];
        return n - lpsLength;
    }
};

/*
Dry Run — Example:
s = "abcd", n = 4
rev = "dcba"

LCS of "abcd" and "dcba":
- The only characters that match in both in the same relative order are single characters (e.g. "a", "b", "c", or "d").
- Thus, the length of the LCS (and LPS) is 1.
- Minimum insertions = n - LPS = 4 - 1 = 3.
(Insertions needed: e.g., prepending "dcb" to get "dcbabcd", or appending "cba" to get "abcdcba")
*/
