/*
GeeksforGeeks: Longest Common Substring
Difficulty: Medium

Problem:
Given two strings s1 and s2, determine the length of the longest substring that appears in both strings.

Core Idea (Striver's DP Progression):
Following Striver's 4-step framework:
1. Recursion: Express the problem in terms of indices (i, j) and a `count` to track the current matching streak. 
2. Memoization: Store the results of the recursive calls. Because the `count` is a state variable, this requires a 3D DP array, which is memory-heavy.
3. Tabulation: We can drop the 3D array by realizing that `dp[i][j]` can just represent the longest common substring ending EXACTLY at `i` and `j`. If they match, `dp[i][j] = 1 + dp[i-1][j-1]`. If not, we just reset the streak by putting `0`. We keep a global `max_len`.
4. Space Optimization: Since the Tabulation's current row `dp[i]` only depends on the previous row `dp[i-1]`, we can compress the 2D table into two 1D arrays: `prev` and `curr`.

Below are the completely separated classes for each step of the DP evolution.

GFG Link: https://www.geeksforgeeks.org/problems/longest-common-substring1452/1
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// ==========================================================
// STEP 1: Recursion
// Time: O(3^(N+M)), Space: O(N+M) auxiliary stack space
// ==========================================================
class Solution_Recursion {
private:
    int solveRec(int i, int j, int count, string &s1, string &s2) {
        // Base case: If either string is exhausted, return the max streak we've found
        if (i < 0 || j < 0) return count;
        
        // If characters match, we increase the streak and move both pointers
        if (s1[i] == s2[j]) {
            count = solveRec(i - 1, j - 1, count + 1, s1, s2);
        }
        
        // Even if they match, we must explore other start points. If they don't match, streak resets to 0.
        // we are setting count to 0 again because we are looking for the maximum common substring and it can be present anywhere in the strings. and not maximum common subsequence.
        // if we didn't set it to 0 then it would have been a longest common subsequence problem.

        int count1 = solveRec(i - 1, j, 0, s1, s2);
        int count2 = solveRec(i, j - 1, 0, s1, s2);
        
        return max({count, count1, count2});
    }

public:
    int longestCommonSubstr(string s1, string s2) {
        // Passing s.length() - 1 for intuitive 0-based indexing
        return solveRec(s1.length() - 1, s2.length() - 1, 0, s1, s2);
    }
};

// ==========================================================
// STEP 2: Memoization (Top-Down DP)
// Time: O(N * M * min(N,M)), Space: O(N * M * min(N,M))
// Note: 3D DP is required because 'count' is a changing state.
// ==========================================================
class Solution_Memoization {
private:
    int solveMem(int i, int j, int count, string &s1, string &s2, vector<vector<vector<int>>> &dp) {
        if (i < 0 || j < 0) return count;
        
        if (dp[i][j][count] != -1) return dp[i][j][count];
        
        int res = count;
        if (s1[i] == s2[j]) {
            res = solveMem(i - 1, j - 1, count + 1, s1, s2, dp);
        }
        
        int ans1 = solveMem(i - 1, j, 0, s1, s2, dp);
        int ans2 = solveMem(i, j - 1, 0, s1, s2, dp);
        
        return dp[i][j][count] = max({res, ans1, ans2});
    }

public:
    int longestCommonSubstr(string s1, string s2) {
        int n = s1.length(), m = s2.length();
        // The max count can be at most min(n, m)
        int max_c = min(n, m); 
        // 0-based indexing means our DP size only needs to be n x m
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(max_c + 1, -1)));
        return solveMem(n - 1, m - 1, 0, s1, s2, dp);
    }
};

// ==========================================================
// STEP 3: Tabulation (Bottom-Up DP)
// Time: O(N * M), Space: O(N * M)
// We drop the 3D 'count' requirement by letting dp[i][j] specifically mean 
// the max streak ENDING exactly at i and j.
// ==========================================================
class Solution_Tabulation {
public:
    int longestCommonSubstr(string s1, string s2) {
        int n = s1.length(), m = s2.length();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        int max_len = 0;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                    max_len = max(max_len, dp[i][j]);
                } else {
                    dp[i][j] = 0; // Streak breaks
                }
            }
        }
        return max_len;
    }
};

// ==========================================================
// STEP 4: Space Optimization
// Time: O(N * M), Space: O(M)
// Since we only need dp[i-1] to calculate dp[i], we compress 
// the 2D matrix into two 1D vectors: prev and curr.
// ==========================================================
class Solution_SpaceOptimization {
public:
    int longestCommonSubstr(string s1, string s2) {
        int n = s1.length(), m = s2.length();
        vector<int> prev(m + 1, 0), curr(m + 1, 0);
        int max_len = 0;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    curr[j] = 1 + prev[j - 1];
                    max_len = max(max_len, curr[j]);
                } else {
                    curr[j] = 0;
                }
            }
            // Move to the next row
            prev = curr;
        }
        return max_len;
    }
};

/*
Dry Run — Example (Tabulation Logic):
Input: s1 = "ABC", s2 = "ABC"

1. i=1 ('A'), j=1 ('A'): Match! curr[1] = 1 + prev[0] = 1. max_len = 1.
   prev becomes [0, 1, 0, 0]
   
2. i=2 ('B'), j=2 ('B'): Match! curr[2] = 1 + prev[1] = 1 + 1 = 2. max_len = 2.
   prev becomes [0, 0, 2, 0]
   
3. i=3 ('C'), j=3 ('C'): Match! curr[3] = 1 + prev[2] = 1 + 2 = 3. max_len = 3.
   
Result is 3.
*/
