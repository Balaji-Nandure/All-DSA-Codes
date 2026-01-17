#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;

/*
Problem: Rod Cutting Problem

GeeksforGeeks: https://practice.geeksforgeeks.org/problems/rod-cutting0840/1
LeetCode: N/A (similar to unbounded knapsack)

You are given a rod of length n and an array price[] where price[i] denotes the value 
of a piece of length i+1. You need to determine the maximum value obtainable by cutting 
up the rod and selling the pieces.

Constraints:
- Rod can be cut into pieces of lengths 1, 2, 3, ..., n
- Each length can be used unlimited times (unbounded)
- Maximize total price

Example:
n = 8, price = [1, 5, 8, 9, 10, 17, 17, 20]
Cut into pieces: length 2 (price 5) + length 6 (price 17) = 22
Or: length 6 (price 17) + length 2 (price 5) = 22
Maximum value = 22

This is equivalent to unbounded knapsack where:
- Capacity = rod length n
- Weights = lengths [1, 2, 3, ..., n]
- Values = prices [price[0], price[1], ..., price[n-1]]

DP State: dp[i][len] = maximum price we can get using first i lengths with rod length len
Recurrence:
dp[i][len] = max(dp[i-1][len], dp[i][len - (i+1)] + price[i])
- dp[i-1][len]: not use length i+1 (move to next length)
- dp[i][len - (i+1)] + price[i]: use length i+1 (stay at same length, can reuse)

Key Difference from 0/1 Knapsack:
- When picking: use dp[i][len - length] instead of dp[i-1][len - length]
- This allows reusing the same length multiple times

Base Cases:
- dp[0][len] = 0 for all len (no lengths, no price)
- dp[i][0] = 0 for all i (no rod length, no price)

Time Complexity: O(n * n) = O(n^2)
Space Complexity: O(n^2) for memoization/tabulation, O(n) for space optimization
*/

// 1. Recursive approach (take/not take method)
class RodCuttingRecursive {
public:
    // TC: O(2^n) exponential, SC: O(n) recursion stack
    int solve(int indx, vector<int>& price, int rodLength) {
        // Base case: no more lengths or no rod length left
        if (indx >= price.size() || rodLength == 0) return 0;
        
        int length = indx + 1; // Length corresponding to price[indx]
        
        // Not use current length (move to next length)
        int notPick = solve(indx + 1, price, rodLength);
        
        // Use current length if it fits (stay at same length, can reuse)
        int pick = 0;
        if (rodLength >= length)
            pick = price[indx] + solve(indx, price, rodLength - length);
        
        return max(pick, notPick);
    }
    
    int cutRod(int n, vector<int>& price) {
        return solve(0, price, n);
    }
};

// 2. Memoization (Top-down DP)
class Solution {
public:
    // TC: O(n^2), SC: O(n^2) for dp array + O(n) recursion stack
    int solve(int indx, vector<int>& price, int rodLength, vector<vector<int>>& dp) {
        // Base case: no more lengths or no rod length left
        if (indx >= price.size() || rodLength == 0) return 0;
        
        // Return cached result
        if (dp[indx][rodLength] != -1) return dp[indx][rodLength];
        
        int length = indx + 1; // Length corresponding to price[indx]
        
        // Not use current length (move to next length)
        int notPick = solve(indx + 1, price, rodLength, dp);
        
        // Use current length if it fits (stay at same length, can reuse)
        int take = 0;
        if (rodLength >= length) {
            take = price[indx] + solve(indx, price, rodLength - length, dp);
        }
        
        return dp[indx][rodLength] = max(take, notPick);
    }
    
    int cutRod(int n, vector<int>& price) {
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
        return solve(0, price, n, dp);
    }
};

// 3. Tabulation (Bottom-up DP)
class RodCuttingTabulation {
public:
    // TC: O(n^2), SC: O(n^2) for dp array
    int cutRod(int n, vector<int>& price) {
        // dp[i][len]: max price using first (i+1) lengths, with rod length len
        vector<vector<int>> dp(n, vector<int>(n + 1, 0));
        
        for (int i = 0; i < n; ++i) {
            int length = i + 1; // Length corresponding to price[i]
            for (int len = 0; len <= n; ++len) {
                if (i == 0) {
                    // For first length, can use it multiple times
                    dp[0][len] = (len >= length) ? (len / length) * price[0] : 0;
                } else {
                    // Not use length i+1 (move to previous length)
                    int notTake = dp[i - 1][len];
                    // Use length i+1 (stay at same length, can reuse)
                    int take = (len >= length) ? price[i] + dp[i][len - length] : 0;
                    dp[i][len] = max(notTake, take);
                }
            }
        }
        
        return dp[n - 1][n];
    }
};

// 4. Space Optimized (O(n) DP)
class Solution {
public:
    // TC: O(n^2), SC: O(n) - only store current row
    int cutRod(int n, vector<int>& price) {
        // For unbounded knapsack variant, we can optimize to use only one array
        vector<int> dp(n + 1, 0);
        
        for (int i = 0; i < n; ++i) {
            int length = i + 1; // Length corresponding to price[i]
            for (int len = 0; len <= n; ++len) {
                int notTake = dp[len];
                int take = 0;
                if (len >= length) {
                    take = price[i] + dp[len - length];
                }
                dp[len] = max(notTake, take);
            }
        }
        
        return dp[n];
    }
};
