#include <bits/stdc++.h>
using namespace std;

/*
 * @brief   Count Matching Subsequences (GeeksforGeeks)
 * @link    https://practice.geeksforgeeks.org/problems/count-matching-subsequences/1
 *
 * Problem Statement:
 *   Given two strings, s1 and s2, count the number of subsequences of string s1 equal to string s2.
 *   Return the total count modulo 1e9+7 (1000000007).
 *
 * Core Intuition / Idea:
 *   - Let dp[i][j] represent the number of times the prefix of s2 of length j matches as a subsequence in the prefix of s1 of length i.
 *   - If s1[i-1] == s2[j-1], we have two choices:
 *     1. Match the current character s1[i-1] with s2[j-1]: The problem reduces to finding matches for s2 of length j-1 in s1 of length i-1.
 *     2. Do not match the current character (skip it): The problem reduces to finding matches for s2 of length j in s1 of length i-1.
 *     So, dp[i][j] = dp[i-1][j-1] + dp[i-1][j].
 *   - If s1[i-1] != s2[j-1], we cannot match the current character. We must skip it:
 *     So, dp[i][j] = dp[i-1][j].
 *
 * Love Babbar 3-Step DP Formula:
 *   1️⃣ **Identify State:** dp[i][j] is the count of matching subsequences for s1[0...i-1] and s2[0...j-1].
 *   2️⃣ **Base Cases:**
 *       - If s2 is empty (j == 0), there is exactly 1 way to form it (by taking an empty subsequence). Thus, dp[i][0] = 1.
 *       - If s1 is empty but s2 is not (i == 0, j > 0), there are 0 ways. Thus, dp[0][j] = 0.
 *   3️⃣ **Transition Relation:**
 *       If s1[i-1] == s2[j-1] -> dp[i][j] = (dp[i-1][j-1] + dp[i-1][j]) % MOD.
 *       Else                  -> dp[i][j] = dp[i-1][j].
 *
 * Complexity Analysis:
 *   - Time Complexity (TC): O(N * M) where N = s1.length() and M = s2.length().
 *   - Space Complexity (SC):
 *     - Recursive: O(N + M) recursion stack.
 *     - Memoization: O(N * M) memoization table.
 *     - Tabulation: O(N * M) DP table.
 *     - Space-Optimized: O(M) using a 1D DP array.
 *
 * Dry Run:
 *   s1 = "geeksforgeeks", s2 = "gks"
 *   Let's check with the Space-Optimized version:
 *   - Initialize dp array of size 4 with: dp = [1, 0, 0, 0] (since dp[0] = 1 represents empty s2 matches).
 *   - For char in s1:
 *     - 'g': Matches s2[0] ('g') -> j = 1: dp[1] = (dp[1] + dp[0]) = 0 + 1 = 1. dp = [1, 1, 0, 0]
 *     - 'e': No matches. dp = [1, 1, 0, 0]
 *     - 'e': No matches. dp = [1, 1, 0, 0]
 *     - 'k': Matches s2[1] ('k') -> j = 2: dp[2] = (dp[2] + dp[1]) = 0 + 1 = 1. dp = [1, 1, 1, 0]
 *     - 's': Matches s2[2] ('s') -> j = 3: dp[3] = (dp[3] + dp[2]) = 0 + 1 = 1. dp = [1, 1, 1, 1]
 *     - ... (and so on).
 *   - Finally, we return the value of dp[3].
 */

// ================= STAGE 1: RECURSION =================
class CountSubsequencesRecursive {
private:
    int MOD = 1e9 + 7;
    int solve(int i, int j, string &s1, string &s2) {
        // Base case: if target string s2 is fully matched
        if (j < 0) return 1;
        // Base case: if s1 is exhausted but s2 is not
        if (i < 0) return 0;
        
        if (s1[i] == s2[j]) {
            return (solve(i - 1, j - 1, s1, s2) + solve(i - 1, j, s1, s2)) % MOD;
        } else {
            return solve(i - 1, j, s1, s2);
        }
    }
public:
    int countWays(string s1, string s2) {
        return solve(s1.length() - 1, s2.length() - 1, s1, s2);
    }
};

// ================= STAGE 2: MEMOIZATION =================
class CountSubsequencesMemoization {
private:
    int MOD = 1e9 + 7;
    int solve(int i, int j, string &s1, string &s2, vector<vector<int>> &dp) {
        // Base case: if target string s2 is fully matched
        if (j < 0) return 1;
        // Base case: if s1 is exhausted but s2 is not
        if (i < 0) return 0;
        
        // Since negative base cases are handled above, i and j are guaranteed to be >= 0 here
        if (dp[i][j] != -1) return dp[i][j];
        
        if (s1[i] == s2[j]) {
            return dp[i][j] = (solve(i - 1, j - 1, s1, s2, dp) + solve(i - 1, j, s1, s2, dp)) % MOD;
        } else {
            return dp[i][j] = solve(i - 1, j, s1, s2, dp);
        }
    }
    
public:
    int countWays(string s1, string s2) {
        int n = s1.length();
        int m = s2.length();
        // Since we index from 0 to n-1 and 0 to m-1, the DP table size is n x m
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return solve(n - 1, m - 1, s1, s2, dp);
    }
};

// ================= STAGE 3: TABULATION =================
class CountSubsequencesTabulation {
private:
    int MOD = 1e9 + 7;
public:
    int countWays(string s1, string s2) {
        int n = s1.length();
        int m = s2.length();
        
        // dp[i][j] stores matches for s1[0...i-1] and s2[0...j-1]
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        
        // Base case: empty s2 has 1 match in all prefixes of s1
        for (int i = 0; i <= n; i++) {
            dp[i][0] = 1;
        }
        
        // Fill DP table
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % MOD;
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        
        return dp[n][m];
    }
};

// ================= STAGE 4: SPACE OPTIMIZED =================
class Solution {
private:
    int MOD = 1e9 + 7;
public:
    int countWays(string s1, string s2) {
        int n = s1.length();
        int m = s2.length();
        
        // We only need 1D array of size m + 1
        vector<int> dp(m + 1, 0);
        dp[0] = 1; // Empty target string has 1 match
        
        for (int i = 1; i <= n; i++) {
            // We iterate from m down to 1 to use values from the previous row (i-1)
            for (int j = m; j >= 1; j--) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[j] = (dp[j] + dp[j - 1]) % MOD;
                }
            }
        }
        
        return dp[m];
    }
};

// Driver code (optional, for local testing)
int main() {
    Solution sol;
    cout << "Test 1 (geeksforgeeks, gks): " << sol.countWays("geeksforgeeks", "gks") << " (Expected: 4)" << endl;
    cout << "Test 2 (problemoftheday, geek): " << sol.countWays("problemoftheday", "geek") << " (Expected: 0)" << endl;
    return 0;
}
