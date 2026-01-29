#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: Maximum Length of a Concatenated String with Unique Characters
LeetCode 1239: https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/

Given an array of strings arr, return the maximum possible length of a string s formed by 
concatenating a subsequence of arr such that s has unique characters.

Constraints:
- 1 <= arr.length <= 16
- 1 <= arr[i].length <= 26
- arr[i] contains only lowercase English letters

Example:
arr = ["un","iq","ue"]
Output: 4
Explanation: Possible concatenations are "un" + "iq" = "uniq" (4 chars) or "un" + "ue" = "unue" (4 chars)

Key Insight:
- Use bitmasking to represent which characters are present (26 bits for 26 letters)
- For each string, check if it has duplicate characters internally
- Use DP to track maximum length with a given character set (bitmask)
- For each string, decide to take it or not take it

DP State:
- dp[mask] = maximum length achievable with character set represented by bitmask

Recurrence Relation:
- For each string arr[i]:
  - If string has no internal duplicates and doesn't conflict with current mask:
    - newMask = mask | stringMask
    - dp[newMask] = max(dp[newMask], dp[mask] + len(arr[i]))
- Base: dp[0] = 0 (empty string)

Time Complexity: O(n * 2^26) where n is number of strings
Space Complexity: O(2^26) for DP array
*/

// Helper function to get bitmask for a string
int getMask(const string& s) {
    int mask = 0;
    for (char c : s) {
        int bit = 1 << (c - 'a');
        // If character already present, return -1 (invalid)
        if (mask & bit) return -1;
        mask |= bit;
    }
    return mask;
}

// memoisation do MLE error so recursive is correct way to submit.
// Approach 1: Pure Recursion (take/not take method)
class Solution1_Recursion {
public:
    // TC: O(2^n * n * m) exponential, SC: O(n) recursion stack
    int solve(int idx, int mask, vector<string>& arr) {
        // Base case: processed all strings
        if (idx == arr.size()) return 0;
        
        // Option 1: Don't take current string
        int notTake = solve(idx + 1, mask, arr);
        
        // Option 2: Take current string (if valid)
        int take = 0;
        int strMask = getMask(arr[idx]);
        if (strMask != -1 && (mask & strMask) == 0) {
            // String has no duplicates and doesn't conflict with current mask
            take = (int)arr[idx].length() + solve(idx + 1, mask | strMask, arr);
        }
        
        return max(notTake, take);
    }
    
    int maxLength(vector<string>& arr) {
        return solve(0, 0, arr);
    }
};


// Approach 2: Memoization (memory limit exceeded error)
class Solution2_Memoization {
public:
    // TC: O(n * 2^26), SC: O(n * 2^26) for memo + O(n) recursion stack
    int solve(int idx, int mask, vector<string>& arr, vector<vector<int>>& dp) {
        // Base case
        if (idx == arr.size()) return 0;
        
        // Check memo
        if (dp[idx][mask] != -1) return dp[idx][mask];
        
        // Don't take
        int notTake = solve(idx + 1, mask, arr, dp);
        
        // Take if valid
        int take = 0;
        int strMask = getMask(arr[idx]);
        if (strMask != -1 && (mask & strMask) == 0) {
            take = (int)arr[idx].length() + solve(idx + 1, mask | strMask, arr, dp);
        }
        
        return dp[idx][mask] = max(notTake, take);
    }
    
    int maxLength(vector<string>& arr) {
        int n = arr.size();
        int maxMask = 1 << 26; // 2^26 possible masks
        vector<vector<int>> dp(n, vector<int>(maxMask, -1));
        return solve(0, 0, arr, dp);
    }
};
