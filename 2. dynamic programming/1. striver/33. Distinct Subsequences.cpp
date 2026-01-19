#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;

/*
Problem: Distinct Subsequences
LeetCode 115: https://leetcode.com/problems/distinct-subsequences/
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/number-of-distinct-subsequences0909/1

Given two strings s and t, return the number of distinct subsequences of s which equals t.
A subsequence is a sequence that can be derived from another sequence by deleting 
some or no elements without changing the order of the remaining elements.

Key Insight:
- Count the number of ways to form t as a subsequence of s
- For each character in s, we can either use it (if it matches t) or skip it
- This is a counting DP problem

Example:
s = "rabbbit", t = "rabbit"
Answer = 3
Ways to form "rabbit" from "rabbbit":
1. r-a-b-b-i-t (skip first 'b')
2. r-a-b-b-i-t (skip second 'b')
3. r-a-b-b-i-t (skip third 'b')

DP State: dp[i][j] = number of ways to form t[0..j-1] using s[0..i-1]

Recurrence:
- If s[i-1] == t[j-1]: 
  - We can use this character: dp[i-1][j-1]
  - We can skip this character: dp[i-1][j]
  - dp[i][j] = dp[i-1][j-1] + dp[i-1][j]
- Else:
  - We must skip s[i-1]
  - dp[i][j] = dp[i-1][j]

Base Cases:
- dp[0][j] = 0 for j > 0 (can't form non-empty t from empty s)
- dp[i][0] = 1 for all i (empty t can be formed in 1 way - by taking nothing)

Time Complexity: O(n * m) where n and m are lengths of s and t
Space Complexity: O(n * m) for memoization/tabulation, O(min(n, m)) for space optimization
*/

// 1. Recursive approach (take/not take method)
class DistinctSubsequencesRecursive {
public:
    // TC: O(2^n) exponential, SC: O(n + m) recursion stack
    int solve(int i, int j, string& s, string& t) {
        // Base case: if t is exhausted, we found one way
        if (j == t.size()) return 1;
        // Base case: if s is exhausted but t is not, no way
        if (i == s.size()) return 0;
        
        // If characters match, we can either use it or skip it
        if (s[i] == t[j]) {
            int use = solve(i + 1, j + 1, s, t);      // Use s[i] to match t[j]
            int skip = solve(i + 1, j, s, t);         // Skip s[i]
            return use + skip;
        }
        
        // If characters don't match, we must skip s[i]
        return solve(i + 1, j, s, t);
    }
    
    int numDistinct(string s, string t) {
        return solve(0, 0, s, t);
    }
};

// Another way of recursioin just ofr understanding
class DistinctSubsequencesPickNotPick {
public:
    int solve(int i, int j, string& s, string& t) {

        if (j == t.size()) return 1;
        if (i == s.size()) return 0;

        int ways = 0;

        // Pick s[i] if it matches t[j]
        if (s[i] == t[j]) {
            ways += solve(i + 1, j + 1, s, t);
        }

        // Always allowed to skip s[i]
        ways += solve(i + 1, j, s, t);

        return ways;
    }

    int numDistinct(string s, string t) {
        return solve(0, 0, s, t);
    }
};

// 2. Memoization (Top-down DP)
class DistinctSubsequencesMemoization {
public:
    // TC: O(n * m), SC: O(n * m) for dp array + O(n + m) recursion stack
    int solve(int i, int j, string& s, string& t, vector<vector<int>>& dp) {
        if (j == t.size()) return 1;
        if (i == s.size()) return 0;
        if (dp[i][j] != -1) return dp[i][j];
        
        if (s[i] == t[j]) {
            int use = solve(i + 1, j + 1, s, t, dp);
            int skip = solve(i + 1, j, s, t, dp);
            return dp[i][j] = use + skip;
        }
        
        return dp[i][j] = solve(i + 1, j, s, t, dp);
    }
    
    int numDistinct(string s, string t) {
        int n = s.size();
        int m = t.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return solve(0, 0, s, t, dp);
    }
};

// 3. Tabulation (Bottom-up DP)
class DistinctSubsequencesTabulation {
public:
    // TC: O(n * m), SC: O(n * m) for dp array
    int numDistinct(string s, string t) {
        int n = s.size();
        int m = t.size();
        
        // dp[i][j]: number of ways to form t[0..j-1] using s[0..i-1]
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        
        // Base case: empty t can be formed in 1 way (by taking nothing)
        for (int i = 0; i <= n; ++i) {
            dp[i][0] = 1;
        }
        // Base case: dp[0][j] = 0 for j > 0 (already initialized)
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (s[i - 1] == t[j - 1]) {
                    // Use s[i-1] to match t[j-1] OR skip s[i-1]
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
                } else {
                    // Must skip s[i-1]
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        
        return dp[n][m];
    }
};

// 4. Space Optimization (O(m) DP)
class Solution {
public:
    // TC: O(n * m), SC: O(m) - only store previous row
    int numDistinct(string s, string t) {
        int n = s.size();
        int m = t.size();
        
        vector<int> prev(m + 1, 0);
        prev[0] = 1; // Base case: empty t can be formed in 1 way
        
        for (int i = 1; i <= n; ++i) {
            vector<int> curr(m + 1, 0);
            curr[0] = 1; // Base case: empty t can be formed in 1 way
            for (int j = 1; j <= m; ++j) {
                if (s[i - 1] == t[j - 1]) {
                    // Use s[i-1] to match t[j-1] OR skip s[i-1]
                    curr[j] = prev[j - 1] + prev[j];
                } else {
                    curr[j] = prev[j];
                }
            }
            prev = curr;
        }
        
        return prev[m];
    }
};
