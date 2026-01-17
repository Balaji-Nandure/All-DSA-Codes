#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;

/*
Problem: Longest Common Subsequence (LCS)
LeetCode 1143: https://leetcode.com/problems/longest-common-subsequence/
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/longest-common-subsequence-1587115620/1

Given two strings text1 and text2, return the length of their longest common subsequence.
A subsequence is a sequence that appears in the same relative order, but not necessarily contiguous.

Constraints:
- Characters must appear in the same relative order in both strings
- Not necessarily contiguous (can skip characters)
- Find the maximum length of such subsequence

Example:
text1 = "abcde", text2 = "ace"
LCS: "ace" (a, c, e appear in both in same order)
Length = 3

DP State: dp[i][j] = length of LCS of text1[0..i-1] and text2[0..j-1]
Recurrence:
- If text1[i-1] == text2[j-1]: dp[i][j] = 1 + dp[i-1][j-1] (match, include both)
- Else: dp[i][j] = max(dp[i-1][j], dp[i][j-1]) (skip one character from either string)

Base Cases:
- dp[0][j] = 0 for all j (empty text1, no common subsequence)
- dp[i][0] = 0 for all i (empty text2, no common subsequence)

Time Complexity: O(n * m) where n and m are lengths of text1 and text2
Space Complexity: O(n * m) for memoization/tabulation, O(min(n, m)) for space optimization
*/

// 1. Recursive approach (take/not take method)
class LCSRecursive {
public:
    // TC: O(2^(n+m)) exponential, SC: O(n + m) recursion stack
    int solve(int i, int j, string& text1, string& text2) {
        // Base case: reached end of either string
        if (i == text1.size() || j == text2.size()) return 0;
        
        // If characters match, include both
        if (text1[i] == text2[j]) {
            return 1 + solve(i + 1, j + 1, text1, text2);
        }
        
        // If characters don't match, try skipping from either string
        int skip1 = solve(i + 1, j, text1, text2); // Skip text1[i]
        int skip2 = solve(i, j + 1, text1, text2); // Skip text2[j]
        
        return max(skip1, skip2);
    }
    
    int longestCommonSubsequence(string text1, string text2) {
        return solve(0, 0, text1, text2);
    }
};

// 2. Memoization (Top-down DP)
class LCSMemoization {
public:
    // TC: O(n * m), SC: O(n * m) for dp array + O(n + m) recursion stack
    int solve(int i, int j, string& text1, string& text2, vector<vector<int>>& dp) {
        // Base case: reached end of either string
        if (i == text1.size() || j == text2.size()) return 0;
        
        // Return cached result
        if (dp[i][j] != -1) return dp[i][j];
        
        // If characters match, include both
        if (text1[i] == text2[j]) {
            return dp[i][j] = 1 + solve(i + 1, j + 1, text1, text2, dp);
        }
        
        // If characters don't match, try skipping from either string
        int skip1 = solve(i + 1, j, text1, text2, dp); // Skip text1[i]
        int skip2 = solve(i, j + 1, text1, text2, dp); // Skip text2[j]
        
        return dp[i][j] = max(skip1, skip2);
    }
    
    int longestCommonSubsequence(string text1, string text2) {
        int n = text1.size(), m = text2.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return solve(0, 0, text1, text2, dp);
    }
};

// 3. Tabulation (Bottom-up DP)
class LCSTabulation {
public:
    // TC: O(n * m), SC: O(n * m) for dp array
    int longestCommonSubsequence(string text1, string text2) {
        int n = text1.size(), m = text2.size();
        // dp[i][j]: length of LCS of text1[0..i-1] and text2[0..j-1]
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        
        // Build DP table
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                // If characters match, include both
                if (text1[i - 1] == text2[j - 1]) {
                    // if not at 0-index, add previous diagonal, else just 1
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    // If characters don't match, take maximum of skipping either
                    int skip1 = dp[i-1][j];
                    int skip2 = dp[i][j-1];
                    dp[i][j] = max(skip1, skip2);
                }
            }
        }
        
        return dp[n][m];
    }
};

// 4. Space Optimization (O(min(n, m)) DP)
class Solution {
public:
    // TC: O(n * m), SC: O(m) - only store current row (fully space optimized)
    int longestCommonSubsequence(string text1, string text2) {
        int n = text1.size();
        int m = text2.size();
        // Always use the shorter string for the columns for best space
        if (m > n) {
            swap(text1, text2);
            swap(n, m);
        }
        // One vector for DP, LCS up to text1[0..i], text2[0..j]
        vector<int> prev(m + 1, 0);

        for (int i = 1; i <= n; ++i) {
            vector<int> curr(m + 1, 0);
            for (int j = 1; j <= m; ++j) {
                if (text1[i - 1] == text2[j - 1])
                    curr[j] = 1 + prev[j - 1];
                else
                    curr[j] = max(prev[j], curr[j - 1]);
            }
            prev = curr;
        }

        return prev[m];
    }
};
    