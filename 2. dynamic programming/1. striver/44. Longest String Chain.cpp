#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;

/*
Problem: Longest String Chain
LeetCode 1048: https://leetcode.com/problems/longest-string-chain/
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/longest-string-chain/1

Given a list of words, each word consists of English lowercase letters.

Let's say word1 is a predecessor of word2 if and only if we can add exactly one letter
anywhere in word1 to make it equal to word2. For example, "abc" is a predecessor of "abac".

A word chain is a sequence of words [word_1, word_2, ..., word_k] with k >= 1, where
word_1 is a predecessor of word_2, word_2 is a predecessor of word_3, and so on.

Return the longest possible word chain with words chosen from the given list of words.

Constraints:
- 1 <= words.length <= 1000
- 1 <= words[i].length <= 16
- words[i] only consists of English lowercase letters

Example:
words = ["a","b","ba","bca","bda","bdca"]
Longest String Chain: ["a","ba","bca","bdca"] or ["a","ba","bda","bdca"]
Length = 4

Key Insight:
- Sort words by length first (ascending order)
- A word1 is a predecessor of word2 if:
  - word2.length == word1.length + 1
  - word1 can be formed by deleting exactly one character from word2
  - This is equivalent to checking if word1 is a subsequence of word2 with exactly one deletion
- This is similar to LIS, but with string predecessor condition instead of increasing condition

DP State: dp[i] = length of longest string chain ending at index i

Recurrence:
- dp[i] = 1 + max(dp[j]) for all j < i where words[j] is a predecessor of words[i]
- If no such j exists, dp[i] = 1 (only the word itself)

Base Cases:
- dp[0] = 1 (single word is always a chain of length 1)

Time Complexity: O(n^2 * L) where n is number of words and L is average word length
Space Complexity: O(n) for dp array

Helper Function:
- isPredecessor(word1, word2): Check if word1 is a predecessor of word2
  - word2.length must be word1.length + 1
  - word1 must be a subsequence of word2 (can be formed by deleting one char from word2)
*/

// Helper function to check if word1 is a predecessor of word2
bool isPredecessor(const string& word1, const string& word2) {
    int n1 = word1.size();
    int n2 = word2.size();
    
    // word2 must be exactly one character longer than word1
    if (n2 != n1 + 1) return false;
    
    // Check if word1 is a subsequence of word2 (can be formed by deleting one char)
    int i = 0, j = 0;
    while (i < n1 && j < n2) {
        if (word1[i] == word2[j]) {
            i++;
        }
        j++;
    }
    
    // word1 is a predecessor if all characters of word1 are found in word2 in order
    return i == n1;
}

// 1. Recursive approach (take/not take method)
class LongestStringChainRecursive {
public:
    // TC: O(2^n) exponential, SC: O(n) recursion stack
    int solve(int idx, int prevIdx, vector<string>& words) {
        // Base case: reached end of array
        if (idx == words.size()) return 0;
        
        // Option 1: Don't take current word
        int notTake = solve(idx + 1, prevIdx, words);
        
        // Option 2: Take current word (if it's a valid successor of previous)
        int take = 0;
        if (prevIdx == -1 || isPredecessor(words[prevIdx], words[idx])) {
            take = 1 + solve(idx + 1, idx, words);
        }
        
        return max(take, notTake);
    }
    
    int longestStrChain(vector<string>& words) {
        // Sort by length to ensure we process shorter words before longer ones
        sort(words.begin(), words.end(), [](const string& a, const string& b) {
            return a.size() < b.size();
        });
        return solve(0, -1, words);
    }
};

// 2. Memoization (Top-down DP)
class LongestStringChainMemoization {
public:
    // TC: O(n^2 * L), SC: O(n^2) for dp array + O(n) recursion stack
    int solve(int idx, int prevIdx, vector<string>& words, vector<vector<int>>& dp) {
        if (idx == words.size()) return 0;
        // Use prevIdx+1 to handle -1 case (prevIdx = -1 maps to index 0)
        if (dp[idx][prevIdx + 1] != -1) return dp[idx][prevIdx + 1];
        
        int notTake = solve(idx + 1, prevIdx, words, dp);
        
        int take = 0;
        if (prevIdx == -1 || isPredecessor(words[prevIdx], words[idx])) {
            take = 1 + solve(idx + 1, idx, words, dp);
        }
        
        return dp[idx][prevIdx + 1] = max(take, notTake);
    }
    
    int longestStrChain(vector<string>& words) {
        sort(words.begin(), words.end(), [](const string& a, const string& b) {
            return a.size() < b.size();
        });
        int n = words.size();
        // dp[i][j+1] where j can be -1 to n-1, so we need n+1 columns
        vector<vector<int>> dp(n, vector<int>(n + 1, -1));
        return solve(0, -1, words, dp);
    }
};

// 3. Tabulation (Bottom-up DP)
class LongestStringChainTabulation {
public:
    // TC: O(n^2 * L), SC: O(n) for dp array
    int longestStrChain(vector<string>& words) {
        int n = words.size();
        if (n == 0) return 0;
        
        // Sort by length to ensure we process shorter words before longer ones
        sort(words.begin(), words.end(), [](const string& a, const string& b) {
            return a.size() < b.size();
        });
        
        // dp[i] = length of longest string chain ending at index i
        vector<int> dp(n, 1);
        int result = 1;
        for(int i = 1; i < n; i++){
            for(int j = 0; j < i; j++){
                if(isPredecessor(words[j], words[i]) && dp[i] < dp[j] + 1){
                    dp[i] = 1 + dp[j];
                    result = max(result, dp[i]);
                }
            }
        }

        return result;
    }
};
