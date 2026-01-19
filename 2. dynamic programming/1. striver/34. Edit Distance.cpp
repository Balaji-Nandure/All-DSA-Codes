#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;

/*
Problem: Edit Distance (Levenshtein Distance)
LeetCode 72: https://leetcode.com/problems/edit-distance/
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/edit-distance3702/1

Given two strings word1 and word2, return the minimum number of operations 
required to convert word1 to word2.

Allowed operations:
1. Insert a character
2. Delete a character
3. Replace a character

Key Insight:
- For each position, we can perform one of three operations
- If characters match, no operation needed
- If characters don't match, choose the minimum cost operation

Example:
word1 = "horse", word2 = "ros"
Operations:
1. horse -> rorse (replace 'h' with 'r')
2. rorse -> rose (remove 'r')
3. rose -> ros (remove 'e')
Answer = 3

DP State: dp[i][j] = minimum operations to convert word1[0..i-1] to word2[0..j-1]

Recurrence:
- If word1[i-1] == word2[j-1]: 
  - dp[i][j] = dp[i-1][j-1] (no operation needed, characters already match)
- Else:
  - dp[i][j] = 1 + min(
      dp[i-1][j],      // Delete word1[i-1]
      dp[i][j-1],      // Insert word2[j-1] at position i
      dp[i-1][j-1]     // Replace word1[i-1] with word2[j-1]
    )

Base Cases:
- dp[0][j] = j (insert all characters of word2)
- dp[i][0] = i (delete all characters of word1)

Time Complexity: O(n * m) where n and m are lengths of word1 and word2
Space Complexity: O(n * m) for memoization/tabulation, O(min(n, m)) for space optimization
*/

// 1. Recursive approach (take/not take method)
class EditDistanceRecursive {
public:
    // TC: O(3^(n+m)) exponential, SC: O(n + m) recursion stack
    int solve(int i, int j, string& word1, string& word2) {
        // Base case: if word1 is exhausted, insert all remaining characters of word2
        if (i == word1.size()) return word2.size() - j;
        // Base case: if word2 is exhausted, delete all remaining characters of word1
        if (j == word2.size()) return word1.size() - i;
        
        // If characters match, no operation needed
        if (word1[i] == word2[j]) {
            return solve(i + 1, j + 1, word1, word2);
        }
        
        // If characters don't match, try all three operations
        int del = 1 + solve(i + 1, j, word1, word2);        // Delete word1[i]
        int ins = 1 + solve(i, j + 1, word1, word2);        // Insert word2[j] at position i
        int rep = 1 + solve(i + 1, j + 1, word1, word2);    // Replace word1[i] with word2[j]
        
        return min({del, ins, rep});
    }
    
    int minDistance(string word1, string word2) {
        return solve(0, 0, word1, word2);
    }
};

// 2. Memoization (Top-down DP)
class EditDistanceMemoization {
public:
    // TC: O(n * m), SC: O(n * m) for dp array + O(n + m) recursion stack
    int solve(int i, int j, string& word1, string& word2, vector<vector<int>>& dp) {
        if (i == word1.size()) return word2.size() - j;
        if (j == word2.size()) return word1.size() - i;
        if (dp[i][j] != -1) return dp[i][j];
        
        if (word1[i] == word2[j]) {
            return dp[i][j] = solve(i + 1, j + 1, word1, word2, dp);
        }
        
        int del = 1 + solve(i + 1, j, word1, word2, dp);
        int ins = 1 + solve(i, j + 1, word1, word2, dp);
        int rep = 1 + solve(i + 1, j + 1, word1, word2, dp);
        
        return dp[i][j] = min({del, ins, rep});
    }
    
    int minDistance(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return solve(0, 0, word1, word2, dp);
    }
};

// 3. Tabulation (Bottom-up DP)
class EditDistanceTabulation {
public:
    // TC: O(n * m), SC: O(n * m) for dp array
    int minDistance(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        
        // dp[i][j]: minimum operations to convert word1[0..i-1] to word2[0..j-1]
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        
        // Base case: if word1 is empty, insert all characters of word2
        for (int j = 0; j <= m; ++j) {
            dp[0][j] = j;
        }
        
        // Base case: if word2 is empty, delete all characters of word1
        for (int i = 0; i <= n; ++i) {
            dp[i][0] = i;
        }
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (word1[i - 1] == word2[j - 1]) {
                    // Characters match, no operation needed
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    // Try all three operations and take minimum
                    int del = dp[i - 1][j];          // Delete word1[i-1]
                    int ins = dp[i][j - 1];           // Insert word2[j-1]
                    int rep = dp[i - 1][j - 1];       // Replace word1[i-1] with word2[j-1]
                    dp[i][j] = 1 + min({del, ins, rep});
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
    int minDistance(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        
        // Use smaller dimension for space optimization
        if (n < m) {
            swap(word1, word2);
            swap(n, m);
        }
        
        vector<int> prev(m + 1, 0);
        
        // Initialize base case: if word2 is empty, delete all characters of word1
        for (int j = 0; j <= m; ++j) {
            prev[j] = j;
        }
        
        for (int i = 1; i <= n; ++i) {
            vector<int> curr(m + 1, 0);
            curr[0] = i; // Base case: if word2 is empty, delete all characters of word1
            
            for (int j = 1; j <= m; ++j) {
                if (word1[i - 1] == word2[j - 1]) {
                    // Characters match, no operation needed
                    curr[j] = prev[j - 1];
                } else {
                    // Try all three operations and take minimum
                    int del = prev[j];            // Delete word1[i-1]
                    int ins = curr[j - 1];         // Insert word2[j-1]
                    int rep = prev[j - 1];         // Replace word1[i-1] with word2[j-1]
                    curr[j] = 1 + min({del, ins, rep});
                }
            }
            prev = curr;
        }
        
        return prev[m];
    }
};
