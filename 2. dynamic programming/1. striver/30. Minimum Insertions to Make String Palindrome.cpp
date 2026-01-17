#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;

/*
Problem: Minimum Insertions to Make String Palindrome
LeetCode 1312: https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/form-a-palindrome1455/1

Given a string s, find the minimum number of insertions needed to make it a palindrome.

Key Insight:
Minimum Insertions = n - LPS(s)
- Where n is the length of the string and LPS is the longest palindromic subsequence
- We keep the LPS and insert characters to match the remaining characters
- For each character not in LPS, we need to insert its mirror

Alternative Approach:
- Use DP where dp[i][j] = minimum insertions needed for s[i..j]
- If s[i] == s[j]: dp[i][j] = dp[i+1][j-1] (no insertion needed)
- Else: dp[i][j] = 1 + min(dp[i+1][j], dp[i][j-1]) (insert one character)

Example:
s = "mbadm"
LPS = "mam" or "mdm" (length 3)
Minimum insertions = 5 - 3 = 2
Insert 'b' and 'a' to make "mbadabm"

DP State (LPS approach): dp[i][j] = length of LPS in s[i..j]
DP State (Direct approach): dp[i][j] = minimum insertions for s[i..j]

Recurrence (LPS approach):
- Find LPS, then answer = n - LPS

Recurrence (Direct approach):
- If s[i] == s[j]: dp[i][j] = dp[i+1][j-1]
- Else: dp[i][j] = 1 + min(dp[i+1][j], dp[i][j-1])

Base Cases:
- dp[i][i] = 0 (single character is already palindrome)
- dp[i][j] = 0 if i > j (invalid range)

Time Complexity: O(n^2) where n is string length
Space Complexity: O(n^2) for memoization/tabulation, O(n) for space optimization
*/

// 1. Recursive approach using LPS method (take/not take)
class MinInsertionsRecursiveLPS {
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
    
    int minInsertions(string s) {
        int n = s.size();
        int lps = solve(0, n - 1, s);
        return n - lps;
    }
};

// 1.0. Recursive approach using direct DP method
class MinInsertionsRecursiveDirect {
public:
    // TC: O(2^n) exponential, SC: O(n) recursion stack
    int solve(int i, int j, string& s) {
        // Base case: invalid range or single character
        if (i >= j) return 0;
        
        // If characters match, no insertion needed
        if (s[i] == s[j]) {
            return solve(i + 1, j - 1, s);
        }
        
        // If characters don't match, insert one character
        int insertLeft = 1 + solve(i + 1, j, s);  // Insert s[j] at position i
        int insertRight = 1 + solve(i, j - 1, s); // Insert s[i] at position j
        
        return min(insertLeft, insertRight);
    }
    
    int minInsertions(string s) {
        return solve(0, s.size() - 1, s);
    }
};

// 2. Memoization (Top-down DP) using LPS method
class MinInsertionsMemoizationLPS {
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
    
    int minInsertions(string s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));
        int lps = solve(0, n - 1, s, dp);
        return n - lps;
    }
};

// 2.0. Memoization using direct DP method
class MinInsertionsMemoizationDirect {
public:
    // TC: O(n^2), SC: O(n^2) for dp array + O(n) recursion stack
    int solve(int i, int j, string& s, vector<vector<int>>& dp) {
        if (i >= j) return 0;
        if (dp[i][j] != -1) return dp[i][j];
        
        if (s[i] == s[j]) {
            return dp[i][j] = solve(i + 1, j - 1, s, dp);
        }
        
        int insertLeft = 1 + solve(i + 1, j, s, dp);
        int insertRight = 1 + solve(i, j - 1, s, dp);
        
        return dp[i][j] = min(insertLeft, insertRight);
    }
    
    int minInsertions(string s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));
        return solve(0, n - 1, s, dp);
    }
};