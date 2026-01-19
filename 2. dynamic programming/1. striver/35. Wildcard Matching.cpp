#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;

/*
Problem: Wildcard Matching
LeetCode 44: https://leetcode.com/problems/wildcard-matching/
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/wildcard-pattern-matching/1

Given an input string (s) and a pattern (p), implement wildcard pattern matching.
The matching should support:
- '?' matches any single character
- '*' matches any sequence of characters (including empty sequence)

Key Insight:
- '*' can match zero or more characters
- '?' matches exactly one character
- We need to check all possible ways '*' can match

Example:
s = "adceb", p = "*a*b"
Matches: '*' matches empty, 'a' matches 'a', '*' matches "dce", 'b' matches 'b'
Answer = true

DP State: dp[i][j] = whether s[0..i-1] matches p[0..j-1]

Recurrence:
- If p[j-1] == '*':
  - dp[i][j] = dp[i][j-1] || dp[i-1][j]
  - dp[i][j-1]: '*' matches zero characters (skip '*')
  - dp[i-1][j]: '*' matches one or more characters (use '*' to match s[i-1])
- Else if p[j-1] == '?' or p[j-1] == s[i-1]:
  - dp[i][j] = dp[i-1][j-1] (match one character)
- Else:
  - dp[i][j] = false (no match)

Base Cases:
- dp[0][0] = true (empty string matches empty pattern)
- dp[0][j] = true if p[0..j-1] consists only of '*' (empty string matches all '*')
- dp[i][0] = false for i > 0 (non-empty string doesn't match empty pattern)

Time Complexity: O(n * m) where n and m are lengths of s and p
Space Complexity: O(n * m) for memoization/tabulation, O(min(n, m)) for space optimization
*/

// 1. Recursive approach (take/not take method)
class WildcardMatchingRecursive {
public:
    // TC: O(2^(n+m)) exponential, SC: O(n + m) recursion stack
    bool solve(int i, int j, string& s, string& p) {
        // Base case: both strings exhausted
        if (i == s.size() && j == p.size()) return true;
        // Base case: pattern exhausted but string not
        if (j == p.size()) return false;
        // Base case: string exhausted but pattern not
        if (i == s.size()) {
            // Only matches if remaining pattern is all '*'
            for (int k = j; k < p.size(); ++k) {
                if (p[k] != '*') return false;
            }
            return true;
        }
        
        // If pattern character is '*'
        if (p[j] == '*') {
            // Match zero characters (skip '*') OR match one or more characters (use '*')
            return solve(i, j + 1, s, p) || solve(i + 1, j, s, p);
        }
        
        // If pattern character is '?' or matches
        if (p[j] == '?' || p[j] == s[i]) {
            return solve(i + 1, j + 1, s, p);
        }
        
        // No match
        return false;
    }
    
    bool isMatch(string s, string p) {
        return solve(0, 0, s, p);
    }
};

// 2. Memoization (Top-down DP)
class WildcardMatchingMemoization {
public:
    // TC: O(n * m), SC: O(n * m) for dp array + O(n + m) recursion stack
    bool solve(int i, int j, string& s, string& p, vector<vector<int>>& dp) {
        // Base case: both strings exhausted
        if (i == s.size() && j == p.size()) return true;
        // Base case: pattern exhausted but string not
        if (j == p.size()) return false;
        // Base case: string exhausted but pattern not
        if (i == s.size()) {
            // Only matches if remaining pattern is all '*'
            for (int k = j; k < p.size(); ++k) {
                if (p[k] != '*') return false;
            }
            return true;
        }
        
        if (dp[i][j] != -1) return dp[i][j];
        
        // If pattern character is '*'
        if (p[j] == '*') {
            // Match zero characters (skip '*') OR match one or more characters (use '*')
            return dp[i][j] = solve(i, j + 1, s, p, dp) || solve(i + 1, j, s, p, dp);
        }
        
        // If pattern character is '?' or matches
        if (p[j] == '?' || p[j] == s[i]) {
            return dp[i][j] = solve(i + 1, j + 1, s, p, dp);
        }
        
        // No match
        return dp[i][j] = false;
    }
    
    bool isMatch(string s, string p) {
        int n = s.size();
        int m = p.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return solve(0, 0, s, p, dp);
    }
};

// 3. Tabulation (Bottom-up DP)
class WildcardMatchingTabulation {
public:
    // TC: O(n * m), SC: O(n * m) for dp array
    bool isMatch(string s, string p) {
        int n = s.size();
        int m = p.size();
        
        // dp[i][j]: whether s[0..i-1] matches p[0..j-1]
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
        
        // Base case: empty string matches empty pattern
        dp[0][0] = true;
        
        // Base case: empty string matches pattern of all '*'
        for (int j = 1; j <= m; ++j) {
            if (p[j - 1] == '*') {
                dp[0][j] = dp[0][j - 1];
            } else {
                dp[0][j] = false;
            }
        }
        
        // Base case: non-empty string doesn't match empty pattern (already false)
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (p[j - 1] == '*') {
                    // Match zero characters (skip '*') OR match one or more characters (use '*')
                    dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
                } else if (p[j - 1] == '?' || p[j - 1] == s[i - 1]) {
                    // Match one character
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    // No match
                    dp[i][j] = false;
                }
            }
        }
        
        return dp[n][m];
    }
};

// 4. Space Optimization (O(min(n, m)) DP)
class Solution {
public:
    // TC: O(n * m), SC: O(min(n, m)) - only store previous row
    bool isMatch(string s, string p) {
        int n = s.size();
        int m = p.size();
        
        // Do not swap it will cause error (think)

        // if (n < m) {
        //     swap(s, p);
        //     swap(n, m);
        // }
        
        vector<bool> prev(m + 1, false);
        
        // Base case: empty string matches empty pattern
        prev[0] = true;
        
        // Base case: empty string matches pattern of all '*'
        for (int j = 1; j <= m; ++j) {
            if (p[j - 1] == '*') {
                prev[j] = prev[j - 1];
            } else {
                prev[j] = false;
            }
        }
        
        for (int i = 1; i <= n; ++i) {
            vector<bool> curr(m + 1, false);
            curr[0] = false; // Non-empty string doesn't match empty pattern
            
            for (int j = 1; j <= m; ++j) {
                if (p[j - 1] == '*') {
                    // Match zero characters (skip '*') OR match one or more characters (use '*')
                    curr[j] = curr[j - 1] || prev[j];
                } else if (p[j - 1] == '?' || p[j - 1] == s[i - 1]) {
                    // Match one character
                    curr[j] = prev[j - 1];
                } else {
                    // No match
                    curr[j] = false;
                }
            }
            prev = curr;
        }
        
        return prev[m];
    }
};
