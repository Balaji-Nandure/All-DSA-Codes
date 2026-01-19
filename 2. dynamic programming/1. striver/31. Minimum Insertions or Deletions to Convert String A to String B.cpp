#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;

/*
Problem: Minimum Insertions or Deletions to Convert String A to String B
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/minimum-number-of-deletions-and-insertions0209/1

Given two strings A and B, find the minimum number of insertions and deletions 
needed to convert string A to string B.

Key Insight:
Minimum Operations = n + m - 2 * LCS(A, B)
- Where n = length of A, m = length of B
- We keep the LCS (common characters in same order)
- Delete characters from A that are not in LCS: (n - LCS) deletions
- Insert characters into A that are in B but not in LCS: (m - LCS) insertions
- Total = (n - LCS) + (m - LCS) = n + m - 2 * LCS

Alternative Approach:
- Use DP where dp[i][j] = minimum operations to convert A[0..i-1] to B[0..j-1]
- If A[i-1] == B[j-1]: dp[i][j] = dp[i-1][j-1] (no operation needed)
- Else: dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1]) (delete from A or insert into A)

Example:
A = "heap", B = "pea"
LCS = "ea" (length 2)
Deletions = 4 - 2 = 2 (delete 'h' and 'p')
Insertions = 3 - 2 = 1 (insert 'p' at beginning)
Total = 2 + 1 = 3

DP State (LCS approach): dp[i][j] = length of LCS of A[0..i-1] and B[0..j-1]
DP State (Direct approach): dp[i][j] = minimum operations to convert A[0..i-1] to B[0..j-1]

Recurrence (LCS approach):
- Find LCS, then answer = n + m - 2 * LCS

Recurrence (Direct approach):
- If A[i-1] == B[j-1]: dp[i][j] = dp[i-1][j-1]
- Else: dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1])

Base Cases:
- dp[0][j] = j (insert all characters of B)
- dp[i][0] = i (delete all characters of A)

Time Complexity: O(n * m) where n and m are lengths of A and B
Space Complexity: O(n * m) for memoization/tabulation, O(min(n, m)) for space optimization
*/

// 1. Recursive approach using LCS method (take/not take)
class MinOperationsRecursiveLCS {
public:
    // TC: O(2^(n+m)) exponential, SC: O(n + m) recursion stack
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
    
    int minOperations(string str1, string str2) {
        int n = str1.size();
        int m = str2.size();
        int lcs = solve(0, 0, str1, str2);
        return n + m - 2 * lcs;
    }
};

// 1.0. Recursive approach using direct DP method
class MinOperationsRecursiveDirect {
public:
    // TC: O(2^(n+m)) exponential, SC: O(n + m) recursion stack
    int solve(int i, int j, string& s1, string& s2) {
        // Base case: if s1 is empty, insert all remaining characters of s2
        if (i == s1.size()) return s2.size() - j;
        // Base case: if s2 is empty, delete all remaining characters of s1
        if (j == s2.size()) return s1.size() - i;
        
        // If characters match, no operation needed
        if (s1[i] == s2[j]) {
            return solve(i + 1, j + 1, s1, s2);
        }
        
        // If characters don't match, try delete or insert
        int del = 1 + solve(i + 1, j, s1, s2);      // Delete s1[i]
        int ins = 1 + solve(i, j + 1, s1, s2);      // Insert s2[j] before s1[i]
        
        return min(del, ins);
    }
    
    int minOperations(string str1, string str2) {
        return solve(0, 0, str1, str2);
    }
};

// 2. Memoization (Top-down DP) using LCS method
class MinOperationsMemoizationLCS {
public:
    // TC: O(n * m), SC: O(n * m) for dp array + O(n + m) recursion stack
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
    
    int minOperations(string str1, string str2) {
        int n = str1.size();
        int m = str2.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        int lcs = solve(0, 0, str1, str2, dp);
        return n + m - 2 * lcs;
    }
};

// 2.0. Memoization using direct DP method
class MinOperationsMemoizationDirect {
public:
    // TC: O(n * m), SC: O(n * m) for dp array + O(n + m) recursion stack
    int solve(int i, int j, string& s1, string& s2, vector<vector<int>>& dp) {
        if (i == s1.size()) return s2.size() - j;
        if (j == s2.size()) return s1.size() - i;
        if (dp[i][j] != -1) return dp[i][j];
        
        if (s1[i] == s2[j]) {
            return dp[i][j] = solve(i + 1, j + 1, s1, s2, dp);
        }
        
        int del = 1 + solve(i + 1, j, s1, s2, dp);
        int ins = 1 + solve(i, j + 1, s1, s2, dp);
        
        return dp[i][j] = min(del, ins);
    }
    
    int minOperations(string str1, string str2) {
        int n = str1.size();
        int m = str2.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return solve(0, 0, str1, str2, dp);
    }
};

// 3. Tabulation (Bottom-up DP) using LCS method
class MinOperationsTabulationLCS {
public:
    // TC: O(n * m), SC: O(n * m) for dp array
    int minOperations(string str1, string str2) {
        int n = str1.size();
        int m = str2.size();
        
        // dp[i][j]: length of LCS of str1[0..i-1] and str2[0..j-1]
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (str1[i - 1] == str2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        int lcs = dp[n][m];
        return n + m - 2 * lcs;
    }
};

// 3.0. Tabulation using direct DP method
class MinOperationsTabulationDirect {
public:
    // TC: O(n * m), SC: O(n * m) for dp array
    int minOperations(string str1, string str2) {
        int n = str1.size();
        int m = str2.size();
        
        // dp[i][j]: minimum operations to convert str1[0..i-1] to str2[0..j-1]
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        
        // Base case: if str1 is empty, insert all characters of str2
        for (int j = 0; j <= m; ++j) {
            dp[0][j] = j;
        }
        
        // Base case: if str2 is empty, delete all characters of str1
        for (int i = 0; i <= n; ++i) {
            dp[i][0] = i;
        }
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (str1[i - 1] == str2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + min(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        return dp[n][m];
    }
};

// 4. Space Optimization (O(min(n, m)) DP) using LCS method
class Solution {
public:
    // TC: O(n * m), SC: O(min(n, m)) - only store previous row
    int minOperations(string str1, string str2) {
        int n = str1.size();
        int m = str2.size();
        
        // Use smaller dimension for space optimization
        if (n < m) {
            swap(str1, str2);
            swap(n, m);
        }
        
        // Find LCS using space optimization
        vector<int> prev(m + 1, 0);
        
        for (int i = 1; i <= n; ++i) {
            vector<int> curr(m + 1, 0);
            for (int j = 1; j <= m; ++j) {
                if (str1[i - 1] == str2[j - 1]) {
                    curr[j] = 1 + prev[j - 1];
                } else {
                    curr[j] = max(prev[j], curr[j - 1]);
                }
            }
            prev = curr;
        }
        
        int lcs = prev[m];
        return n + m - 2 * lcs;
    }
};
