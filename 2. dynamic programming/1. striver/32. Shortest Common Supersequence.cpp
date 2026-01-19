#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;

/*
Problem: Shortest Common Supersequence (SCS)
LeetCode 1092: https://leetcode.com/problems/shortest-common-supersequence/
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/shortest-common-supersequence0322/1

Given two strings A and B, find the shortest string that contains both A and B as subsequences.
A supersequence is a sequence that contains both strings as subsequences.

Key Insight:
Length of SCS = n + m - LCS(A, B)
- Where n = length of A, m = length of B
- We include the LCS once and add all remaining characters from both strings
- For each character in LCS, we use it once (instead of twice)

To construct the actual SCS string:
1. Find LCS using DP
2. Backtrack through DP table to build SCS:
   - If characters match: add once and move diagonally
   - If characters don't match: add the character from the direction we came from

Example:
A = "abac", B = "cab"
LCS = "ab" (length 2)
SCS length = 4 + 3 - 2 = 5
SCS = "cabac" (contains both "abac" and "cab" as subsequences)

DP State: dp[i][j] = length of LCS of A[0..i-1] and B[0..j-1]
Recurrence:
- If A[i-1] == B[j-1]: dp[i][j] = 1 + dp[i-1][j-1]
- Else: dp[i][j] = max(dp[i-1][j], dp[i][j-1])

Time Complexity: O(n * m) where n and m are lengths of A and B
Space Complexity: O(n * m) for memoization/tabulation, O(min(n, m)) for space optimization (length only)
*/

// 1.0. Recursive approach to construct SCS string
class SCSRecursiveString {
public:
    // TC: O(2^(n+m)) exponential, SC: O(n + m) recursion stack
    string solve(int i, int j, string& s1, string& s2) {
        // Base case: if s1 is exhausted, add remaining characters of s2
        if (i == s1.size()) return s2.substr(j);
        // Base case: if s2 is exhausted, add remaining characters of s1
        if (j == s2.size()) return s1.substr(i);
        
        // If characters match, include once and recurse
        if (s1[i] == s2[j]) {
            return s1[i] + solve(i + 1, j + 1, s1, s2);
        }
        
        // If characters don't match, try both options and take shorter
        string take1 = s1[i] + solve(i + 1, j, s1, s2);
        string take2 = s2[j] + solve(i, j + 1, s1, s2);
        
        return (take1.size() < take2.size()) ? take1 : take2;
    }
    
    string shortestCommonSupersequence(string str1, string str2) {
        return solve(0, 0, str1, str2);
    }
};

// 2.0. Memoization to construct SCS string
class SCSMemoizationString {
public:
    // TC: O(n * m), SC: O(n * m) for dp array + O(n + m) recursion stack
    string solve(int i, int j, string& s1, string& s2, vector<vector<string>>& dp) {
        if (i == s1.size()) return s2.substr(j);
        if (j == s2.size()) return s1.substr(i);
        if (!dp[i][j].empty()) return dp[i][j];
        
        if (s1[i] == s2[j]) {
            return dp[i][j] = s1[i] + solve(i + 1, j + 1, s1, s2, dp);
        }
        
        string take1 = s1[i] + solve(i + 1, j, s1, s2, dp);
        string take2 = s2[j] + solve(i, j + 1, s1, s2, dp);
        
        return dp[i][j] = (take1.size() < take2.size()) ? take1 : take2;
    }
    
    string shortestCommonSupersequence(string str1, string str2) {
        int n = str1.size();
        int m = str2.size();
        vector<vector<string>> dp(n, vector<string>(m));
        return solve(0, 0, str1, str2, dp);
    }
};

// 3.0. Tabulation to construct SCS string
// Optimal
class SCSTabulationString {
public:
    // TC: O(n * m), SC: O(n * m) for dp array
    string shortestCommonSupersequence(string str1, string str2) {
        int n = str1.size();
        int m = str2.size();
        
        // dp[i][j]: length of LCS of str1[0..i-1] and str2[0..j-1]
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        
        // Build LCS DP table
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (str1[i - 1] == str2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        // Backtrack to construct SCS
        string result = "";
        int i = n, j = m;
        
        while (i > 0 && j > 0) {
            if (str1[i - 1] == str2[j - 1]) {
                // Characters match, add once and move diagonally
                result += str1[i - 1];
                i--;
                j--;
            } else if (dp[i - 1][j] > dp[i][j - 1]) {
                // Move up, add character from str1
                result += str1[i - 1];
                i--;
            } else {
                // Move left, add character from str2
                result += str2[j - 1];
                j--;
            }
        }
        
        // Add remaining characters
        while (i > 0) {
            result += str1[i - 1];
            i--;
        }
        while (j > 0) {
            result += str2[j - 1];
            j--;
        }
        
        reverse(result.begin(), result.end());
        return result;
    }
};
