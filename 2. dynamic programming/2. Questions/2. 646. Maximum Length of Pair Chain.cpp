#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: Maximum Length of Pair Chain
LeetCode 646: https://leetcode.com/problems/maximum-length-of-pair-chain/
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/maximum-length-chain-of-pairs/1

You are given an array of n pairs where pairs[i] = [a, b] and a < b.

A pair c2 = [c, d] follows another pair c1 = [a, b] if and only if b < c.
A chain of pairs can be formed in this fashion.

Return the length of the longest chain which can be formed.

Constraints:
- n == pairs.length
- 1 <= n <= 1000
- -1000 <= pairs[i][0] < pairs[i][1] <= 1000

Example:
pairs = [[1,2], [2,3], [3,4]]
Chain: [1,2] -> [3,4]
Length = 2

Key Insight:
- Sort pairs by their second element (end) first
- Then it becomes similar to LIS - we want to find longest chain where pairs[j].second < pairs[i].first
- After sorting by end, we can use DP to find longest chain
- Alternatively, we can use greedy: always pick the pair with smallest end that can extend the chain

DP State: dp[i] = length of longest chain ending at index i

Recurrence:
- dp[i] = 1 + max(dp[j]) for all j < i where pairs[j][1] < pairs[i][0]
- If no such j exists, dp[i] = 1 (only the pair itself)

Base Cases:
- dp[0] = 1 (single pair is always a chain of length 1)

Time Complexity: O(n^2) for DP approach, O(n log n) for greedy approach
Space Complexity: O(n) for DP array
*/

// 1. Recursive approach (take/not take method)
class MaxPairChainRecursive {
public:
    // TC: O(2^n) exponential, SC: O(n) recursion stack
    int solve(int idx, int prevIdx, vector<vector<int>>& pairs) {
        // Base case: reached end of array
        if (idx == pairs.size()) return 0;
        
        // Option 1: Don't take current pair
        int notTake = solve(idx + 1, prevIdx, pairs);
        
        // Option 2: Take current pair (if it can follow previous pair)
        int take = 0;
        if (prevIdx == -1 || pairs[prevIdx][1] < pairs[idx][0]) {
            take = 1 + solve(idx + 1, idx, pairs);
        }
        
        return max(take, notTake);
    }
    
    int findLongestChain(vector<vector<int>>& pairs) {
        // Sort pairs by their second element (end) for optimal chain building
        sort(pairs.begin(), pairs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });
        return solve(0, -1, pairs);
    }
};

// 2. Memoization (Top-down DP)
class MaxPairChainMemoization {
public:
    // TC: O(n^2), SC: O(n^2) for dp array + O(n) recursion stack
    int solve(int idx, int prevIdx, vector<vector<int>>& pairs, vector<vector<int>>& dp) {
        if (idx == pairs.size()) return 0;
        // Use prevIdx+1 to handle -1 case (prevIdx = -1 maps to index 0)
        if (dp[idx][prevIdx + 1] != -1) return dp[idx][prevIdx + 1];
        
        int notTake = solve(idx + 1, prevIdx, pairs, dp);
        
        int take = 0;
        if (prevIdx == -1 || pairs[prevIdx][1] < pairs[idx][0]) {
            take = 1 + solve(idx + 1, idx, pairs, dp);
        }
        
        return dp[idx][prevIdx + 1] = max(take, notTake);
    }
    
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(), pairs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });
        int n = pairs.size();
        // dp[i][j+1] where j can be -1 to n-1, so we need n+1 columns
        vector<vector<int>> dp(n, vector<int>(n + 1, -1));
        return solve(0, -1, pairs, dp);
    }
};

// 3. Tabulation (Bottom-up DP)
class MaxPairChainTabulation {
public:
    // TC: O(n^2), SC: O(n) for dp array
    int findLongestChain(vector<vector<int>>& pairs) {
        int n = pairs.size();
        if (n == 0) return 0;
        
        // Sort pairs by their second element (end)
        sort(pairs.begin(), pairs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });
        
        // dp[i] = length of longest chain ending at index i
        vector<int> dp(n, 1);
        int result = 1;
        
        // For each pair, check all previous pairs
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                // If pairs[j] can be followed by pairs[i] (pairs[j][1] < pairs[i][0])
                if (pairs[j][1] < pairs[i][0]) {
                    dp[i] = max(dp[i], 1 + dp[j]);
                    result = max(result, dp[i]);
                }
            }
        }
        
        return result;
    }
};

// 4. Space Optimization (Greedy Approach - O(n log n))
class Solution {
public:
    // TC: O(n log n), SC: O(1) - greedy approach
    int findLongestChain(vector<vector<int>>& pairs) {
        int n = pairs.size();
        if (n == 0) return 0;
        
        // Sort pairs by their second element (end)
        sort(pairs.begin(), pairs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });
        
        // Greedy: always pick the pair with smallest end that can extend the chain
        int chainLength = 1;
        int lastEnd = pairs[0][1];
        
        for (int i = 1; i < n; i++) {
            // If current pair can extend the chain (its start > last end)
            if (pairs[i][0] > lastEnd) {
                chainLength++;
                lastEnd = pairs[i][1];
            }
        }
        
        return chainLength;
    }
};
