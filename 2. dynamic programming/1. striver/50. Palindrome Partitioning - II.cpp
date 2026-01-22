#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: Palindrome Partitioning - II
LeetCode 132: https://leetcode.com/problems/palindrome-partitioning-ii/
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/palindromic-patitioning4845/1

Given a string s, partition s such that every substring of the partition is a palindrome.
Return the minimum cuts needed for a palindrome partitioning of s.

Constraints:
- 1 <= s.length <= 2000
- s consists of lowercase English letters only

Example:
s = "aab"
Partition: ["aa","b"] -> 1 cut
Or: ["a","a","b"] -> 2 cuts
Minimum cuts = 1

Key Insight:
- We need to find minimum cuts such that all substrings are palindromes
- Precompute palindrome table: isPal[i][j] = true if s[i..j] is palindrome
- dp[i] = minimum cuts needed for substring s[0..i]
- For each position i, try all possible partitions ending at i

DP State: dp[i] = minimum cuts needed for substring s[0..i]

Recurrence:
- dp[i] = min(dp[j-1] + 1) for all j from 0 to i where s[j..i] is palindrome
- If s[0..i] is palindrome, dp[i] = 0 (no cuts needed)

Base Cases:
- dp[0] = 0 (single character is palindrome, no cuts needed)

Time Complexity: O(n^2) where n is string length
Space Complexity: O(n^2) for palindrome table, O(n) for dp array

Alternative: Can optimize palindrome checking to O(n^2) using DP
*/

// Helper function to check if substring is palindrome
bool isPalindrome(string& s, int i, int j) {
    while (i < j) {
        if (s[i] != s[j]) return false;
        i++;
        j--;
    }
    return true;
}

// 1. Recursive approach
class PalindromePartitioningRecursive {
public:
    // TC: O(2^n) exponential, SC: O(n) recursion stack
    int solve(int idx, string& s) {
        // Base case: reached beginning or substring is palindrome
        if (idx < 0) return -1; // -1 because we'll add 1, so 0 cuts
        if (isPalindrome(s, 0, idx)) return 0; // No cuts needed
        
        int minCuts = INF;
        
        // Try all possible partitions ending at idx
        for (int j = idx; j >= 0; j--) {
            if (isPalindrome(s, j, idx)) {
                int cuts = 1 + solve(j - 1, s);
                minCuts = min(minCuts, cuts);
            }
        }
        
        return minCuts;
    }
    
    int minCut(string s) {
        int n = s.size();
        return solve(n - 1, s);
    }
};

// 2. Memoization (Top-down DP)
class PalindromePartitioningMemoization {
public:
    // TC: O(n^2), SC: O(n) for dp array + O(n) recursion stack
    int solve(int idx, string& s, vector<int>& dp) {
        if (idx < 0) return -1;
        if (isPalindrome(s, 0, idx)) return 0;
        if (dp[idx] != -1) return dp[idx];
        
        int minCuts = INF;
        
        for (int j = idx; j >= 0; j--) {
            if (isPalindrome(s, j, idx)) {
                int cuts = 1 + solve(j - 1, s, dp);
                minCuts = min(minCuts, cuts);
            }
        }
        
        return dp[idx] = minCuts;
    }
    
    int minCut(string s) {
        int n = s.size();
        vector<int> dp(n, -1);
        return solve(n - 1, s, dp);
    }
};
