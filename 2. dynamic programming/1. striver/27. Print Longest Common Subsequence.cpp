#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;

/*
Problem: Print Longest Common Subsequence
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/print-longest-common-subsequence/0

Given two strings, find and print the longest common subsequence (not just the length).
A subsequence is a sequence that appears in the same relative order, but not necessarily contiguous.

Constraints:
- Characters must appear in the same relative order in both strings
- Not necessarily contiguous (can skip characters)
- Return the actual LCS string

Example:
text1 = "abcde", text2 = "ace"
LCS: "ace"
Output: "ace"

Approach:
1. First build DP table to find LCS length (same as LCS problem)
2. Backtrack through DP table to construct the actual LCS string

DP State: dp[i][j] = length of LCS of text1[0..i-1] and text2[0..j-1]
Recurrence:
- If text1[i-1] == text2[j-1]: dp[i][j] = 1 + dp[i-1][j-1]
- Else: dp[i][j] = max(dp[i-1][j], dp[i][j-1])

Backtracking:
- Start from dp[n][m]
- If text1[i-1] == text2[j-1]: add character and move diagonally
- Else: move in direction of maximum (up or left)

Time Complexity: O(n * m) for DP + O(n + m) for backtracking = O(n * m)
Space Complexity: O(n * m) for DP table (needed for backtracking)
*/

// 1. Recursive approach (construct LCS while recursing)
class PrintLCSRecursive {
public:
    // TC: O(2^(n+m)) exponential, SC: O(n + m) recursion stack
    string solve(int i, int j, string& text1, string& text2) {
        // Base case: reached end of either string
        if (i == text1.size() || j == text2.size()) return "";
        
        // If characters match, include in result
        if (text1[i] == text2[j]) {
            return text1[i] + solve(i + 1, j + 1, text1, text2);
        }
        
        // If characters don't match, try skipping from either string
        string skip1 = solve(i + 1, j, text1, text2); // Skip text1[i]
        string skip2 = solve(i, j + 1, text1, text2); // Skip text2[j]
        
        return (skip1.size() > skip2.size()) ? skip1 : skip2;
    }
    
    string printLCS(string text1, string text2) {
        return solve(0, 0, text1, text2);
    }
};

// 2. Memoization (Top-down DP) with backtracking
// ❌
class PrintLCSMemoization {
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
        int skip1 = solve(i + 1, j, text1, text2, dp);
        int skip2 = solve(i, j + 1, text1, text2, dp);
        
        return dp[i][j] = max(skip1, skip2);
    }
    
    string constructLCS(int i, int j, string& text1, string& text2, vector<vector<int>>& dp) {
        // Base case: reached end of either string
        if (i == text1.size() || j == text2.size()) return "";
        
        // If characters match, include in result
        if (text1[i] == text2[j]) {
            return text1[i] + constructLCS(i + 1, j + 1, text1, text2, dp);
        }
        
        // Move in direction of maximum
        if (dp[i + 1][j] >= dp[i][j + 1]) {
            return constructLCS(i + 1, j, text1, text2, dp);
        } else {
            return constructLCS(i, j + 1, text1, text2, dp);
        }
    }
    
    string printLCS(string text1, string text2) {
        int n = text1.size(), m = text2.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        solve(0, 0, text1, text2, dp);
        return constructLCS(0, 0, text1, text2, dp);
    }
};

// 3. Tabulation (Bottom-up DP) with backtracking
class PrintLCSTabulation {
public:
    // TC: O(n * m), SC: O(n * m) for dp array
    string printLCS(string text1, string text2) {
        int n = text1.size(), m = text2.size();
        // dp[i][j]: length of LCS of text1[0..i-1] and text2[0..j-1]
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        
        // Build DP table
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                // If characters match, include both
                if (text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    // If characters don't match, take maximum of skipping either
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        // Backtrack to construct LCS string
        string lcs = "";
        int i = n, j = m;
        while (i > 0 && j > 0) {
            // If characters match, include in result and move diagonally
            if (text1[i - 1] == text2[j - 1]) {
                lcs = text1[i - 1] + lcs;
                i--;
                j--;
            } else {
                // Move in direction of maximum
                if (dp[i - 1][j] > dp[i][j - 1]) {
                    i--;
                } else {
                    j--;
                }
            }
        }
        
        return lcs;
    }
};