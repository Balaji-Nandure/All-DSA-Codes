#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;

/*
Problem: Longest Palindromic Subsequence (LPS)
LeetCode 516: https://leetcode.com/problems/longest-palindromic-subsequence/
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/longest-palindromic-subsequence-1612327878/1

Given a string s, find the length of the longest palindromic subsequence.
A subsequence is a sequence that can be derived from another sequence by deleting 
some or no elements without changing the order of the remaining elements.

Key Insight:
LPS(s) = LCS(s, reverse(s))
- The longest palindromic subsequence is the longest common subsequence between 
  the string and its reverse

Alternative Approach:
- Use DP where dp[i][j] = longest palindromic subsequence in s[i..j]
- If s[i] == s[j]: dp[i][j] = 2 + dp[i+1][j-1]
- Else: dp[i][j] = max(dp[i+1][j], dp[i][j-1])

Example:
s = "bbbab"
LPS: "bbbb" or "bbab"
Length = 4

DP State (LCS approach): dp[i][j] = length of LCS of s[0..i-1] and rev[0..j-1]
DP State (Direct approach): dp[i][j] = length of LPS in s[i..j]

Recurrence (LCS approach):
- If s[i-1] == rev[j-1]: dp[i][j] = 1 + dp[i-1][j-1]
- Else: dp[i][j] = max(dp[i-1][j], dp[i][j-1])

Recurrence (Direct approach):
- If s[i] == s[j]: dp[i][j] = 2 + dp[i+1][j-1] (if i != j, else 1)
- Else: dp[i][j] = max(dp[i+1][j], dp[i][j-1])

Base Cases:
- dp[i][i] = 1 (single character is palindrome)
- dp[i][j] = 0 if i > j (invalid range)

Time Complexity: O(n^2) where n is string length
Space Complexity: O(n^2) for memoization/tabulation, O(n) for space optimization
*/

// 1. Recursive approach using LCS method (take/not take)
class LPSRecursiveLCS {
public:
    // TC: O(2^n) exponential, SC: O(n) recursion stack
    int solve(int i, int j, string& s1, string& s2) {
        // Base case: reached end of either string
        if (i == s1.size() || j == s2.size()) return 0;
        
        // If characters match, include both
        if (s1[i] == s2[j]) {
            return 1 + solve(i + 1, j + 1, s1, s2);
        }
        
        // If characters don't match, try skipping from either string
        int skip1 = solve(i + 1, j, s1, s2);
        int skip2 = solve(i, j + 1, s1, s2);
        
        return max(skip1, skip2);
    }
    
    int longestPalindromeSubseq(string s) {
        string rev = s;
        reverse(rev.begin(), rev.end());
        return solve(0, 0, s, rev);
    }
};

// 1.0. Recursive approach using direct DP method
class LPSRecursiveDirect {
public:
    // TC: O(2^n) exponential, SC: O(n) recursion stack
    int solve(int i, int j, string& s) {
        // Base case: invalid range
        if (i > j) return 0;
        // Base case: single character
        if (i == j) return 1;
        
        // If characters match, include both
        if (s[i] == s[j]) {
            return 2 + solve(i + 1, j - 1, s);
        }
        
        // If characters don't match, try skipping from either end
        int skipLeft = solve(i + 1, j, s);
        int skipRight = solve(i, j - 1, s);
        
        return max(skipLeft, skipRight);
    }
    
    int longestPalindromeSubseq(string s) {
        return solve(0, s.size() - 1, s);
    }
};

// 2. Memoization (Top-down DP) using LCS method
class LPSMemoizationLCS {
public:
    // TC: O(n^2), SC: O(n^2) for dp array + O(n) recursion stack
    int solve(int i, int j, string& s1, string& s2, vector<vector<int>>& dp) {
        if (i == s1.size() || j == s2.size()) return 0;
        if (dp[i][j] != -1) return dp[i][j];
        
        if (s1[i] == s2[j]) {
            return dp[i][j] = 1 + solve(i + 1, j + 1, s1, s2, dp);
        }
        
        int skip1 = solve(i + 1, j, s1, s2, dp);
        int skip2 = solve(i, j + 1, s1, s2, dp);
        
        return dp[i][j] = max(skip1, skip2);
    }
    
    int longestPalindromeSubseq(string s) {
        string rev = s;
        reverse(rev.begin(), rev.end());
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));
        return solve(0, 0, s, rev, dp);
    }
};

// 2.0. Memoization using direct DP method
class LPSMemoizationDirect {
public:
    // TC: O(n^2), SC: O(n^2) for dp array + O(n) recursion stack
    int solve(int i, int j, string& s, vector<vector<int>>& dp) {
        if (i > j) return 0;
        if (i == j) return 1;
        if (dp[i][j] != -1) return dp[i][j];
        
        if (s[i] == s[j]) {
            return dp[i][j] = 2 + solve(i + 1, j - 1, s, dp);
        }
        
        int skipLeft = solve(i + 1, j, s, dp);
        int skipRight = solve(i, j - 1, s, dp);
        
        return dp[i][j] = max(skipLeft, skipRight);
    }
    
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));
        return solve(0, n - 1, s, dp);
    }
};

// 3. Tabulation (Bottom-up DP) using LCS method
class LPSTabulationLCS {
public:
    // TC: O(n^2), SC: O(n^2) for dp array
    int longestPalindromeSubseq(string s) {
        string rev = s;
        reverse(rev.begin(), rev.end());
        int n = s.size();
        
        // dp[i][j]: length of LCS of s[0..i-1] and rev[0..j-1]
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (s[i - 1] == rev[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        return dp[n][n];
    }
};


// 4. Space Optimization (O(n) DP) using LCS method
class Solution {
public:
    // TC: O(n^2), SC: O(n) - only store previous row
    int longestPalindromeSubseq(string s) {
        string rev = s;
        reverse(rev.begin(), rev.end());
        int n = s.size();
        
        vector<int> prev(n + 1, 0);
        
        for (int i = 1; i <= n; ++i) {
            vector<int> curr(n + 1, 0);
            for (int j = 1; j <= n; ++j) {
                if (s[i - 1] == rev[j - 1]) {
                    curr[j] = 1 + prev[j - 1];
                } else {
                    curr[j] = max(prev[j], curr[j - 1]);
                }
            }
            prev = curr;
        }
        
        return prev[n];
    }
};
