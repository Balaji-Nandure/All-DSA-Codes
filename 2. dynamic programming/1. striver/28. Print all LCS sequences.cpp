#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;

/*
Problem: Print All Longest Common Subsequences
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/print-all-lcs-sequences3413/1

Given two strings, find and print all distinct longest common subsequences (not just one).
A subsequence is a sequence that appears in the same relative order, but not necessarily contiguous.

Constraints:
- Characters must appear in the same relative order in both strings
- Not necessarily contiguous (can skip characters)
- Return all distinct LCS strings (sorted)

Example:
text1 = "abaaa", text2 = "baabaca"
LCS length = 4
All LCS: ["aaaa", "abaa", "baaa"]

Key Difference from Print One LCS:
- When dp[i-1][j] == dp[i][j-1], we must explore BOTH paths
- Use set to store distinct sequences
- Need to backtrack through all possible paths

DP State: dp[i][j] = length of LCS of text1[0..i-1] and text2[0..j-1]
Recurrence:
- If text1[i-1] == text2[j-1]: dp[i][j] = 1 + dp[i-1][j-1]
- Else: dp[i][j] = max(dp[i-1][j], dp[i][j-1])

Backtracking for All LCS:
- Start from dp[n][m]
- If text1[i-1] == text2[j-1]: add character and move diagonally
- Else if dp[i-1][j] > dp[i][j-1]: move up
- Else if dp[i-1][j] < dp[i][j-1]: move left
- Else: explore BOTH paths (when equal)

Time Complexity: O(n * m) for DP + O(2^(n+m)) worst case for backtracking
Space Complexity: O(n * m) for DP table + O(2^(n+m)) for storing all sequences
*/

// 1. Recursive approach (generate all LCS while recursing)
class PrintAllLCSRecursive {
public:
    // TC: O(2^(n+m)) exponential, SC: O(n + m) recursion stack
    void solve(int i, int j, string& text1, string& text2, string current, 
               set<string>& result, int maxLen) {
        // Base case: reached end of either string
        if (i == text1.size() || j == text2.size()) {
            if (current.size() == maxLen) {
                result.insert(current);
            }
            return;
        }
        
        // If characters match, include in result
        if (text1[i] == text2[j]) {
            solve(i + 1, j + 1, text1, text2, current + text1[i], result, maxLen);
        } else {
            // Try skipping from both strings
            solve(i + 1, j, text1, text2, current, result, maxLen);
            solve(i, j + 1, text1, text2, current, result, maxLen);
        }
    }
    
    vector<string> all_longest_common_subsequences(string text1, string text2) {
        // First find LCS length
        int n = text1.size(), m = text2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        int maxLen = dp[n][m];
        set<string> result;
        solve(0, 0, text1, text2, "", result, maxLen);
        
        return vector<string>(result.begin(), result.end());
    }
};