#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;

/*
Problem: Unbounded Knapsack

GeeksforGeeks: https://practice.geeksforgeeks.org/problems/knapsack-with-duplicate-items4201/1
LeetCode: N/A (similar concepts in Coin Change problems)

You are given weights and values of n items. Put these items in a knapsack of capacity W 
to get the maximum total value in the knapsack. Each item can be used unlimited times.

Constraints:
- Each item can be picked unlimited times (unbounded)
- Maximize total value without exceeding capacity W

Example:
weights = [1, 2, 3], values = [10, 15, 40], W = 6
Pick item 3 twice: value = 40 + 40 = 80, weight = 3 + 3 = 6 <= 6
Maximum value = 80

DP State: dp[i][w] = maximum value we can get using first i items with capacity w
Recurrence:
dp[i][w] = max(dp[i-1][w], dp[i][w - weights[i-1]] + values[i-1])
- dp[i-1][w]: not pick item i-1 (move to next item)
- dp[i][w - weights[i-1]] + values[i-1]: pick item i-1 (stay at same item, can reuse)

Key Difference from 0/1 Knapsack:
- When picking: use dp[i][w - weight] instead of dp[i-1][w - weight]
- This allows reusing the same item multiple times

Base Cases:
- dp[0][w] = 0 for all w (no items, no value)
- dp[i][0] = 0 for all i (no capacity, no value)

Time Complexity: O(n * W)
Space Complexity: O(n * W) for memoization/tabulation, O(W) for space optimization
*/

// 1. Recursive approach (take/not take method)
class UnboundedKnapsackRecursive {
public:
    // TC: O(2^W) exponential, SC: O(W) recursion stack
    int solve(int indx, vector<int>& weight, vector<int>& value, int capacity) {
        // Base case: no more items or no capacity left
        if (indx == weight.size() || capacity == 0) return 0;
        
        // Not pick current item (move to next item)
        int notPick = solve(indx + 1, weight, value, capacity);
        
        // Pick current item if it fits (stay at same item, can reuse)
        int pick = 0;
        if (capacity >= weight[indx])
            pick = value[indx] + solve(indx, weight, value, capacity - weight[indx]);
        
        return max(pick, notPick);
    }
    
    int knapsack(int n, int W, vector<int>& weight, vector<int>& value) {
        return solve(0, weight, value, W);
    }
};

// 2. Memoization (Top-down DP)
class Solution {
public:
    int solve(int indx, vector<int> &weight, vector<int> &value, int capacity, vector<vector<int>> &dp){
        if(indx == weight.size() || capacity == 0) return 0;
        if(dp[indx][capacity] != -1) return dp[indx][capacity];
        
        int notPick = solve(indx + 1, weight, value, capacity, dp);
        int take = 0;
        if(capacity >= weight[indx]){
            take = value[indx] + solve(indx, weight, value, capacity - weight[indx], dp);
        }
        return dp[indx][capacity] = max(take, notPick);
    }
    
    int knapSack(vector<int>& val, vector<int>& wt, int capacity) {
        // code here
        int n = val.size();
        vector<vector<int>> dp(n + 1, vector<int> (capacity + 1, -1));
        return solve(0, wt, val, capacity, dp);
    }
};

// 3. Tabulation (Bottom-up DP)
class UnboundedKnapsackTabulation {
public:
    // TC: O(n * W), SC: O(n * W) for dp array
    int knapsack(int n, int W, vector<int>& weight, vector<int>& value) {
        // dp[i][w]: max value using first (i+1) items, with knapsack capacity w
        vector<vector<int>> dp(n, vector<int>(W + 1, 0));
        
        for (int i = 0; i < n; ++i) {
            for (int w = 0; w <= W; ++w) {
                if (i == 0) {
                    // For first item, can use it multiple times
                    dp[0][w] = (w >= weight[0]) ? (w / weight[0]) * value[0] : 0;
                } else {
                    // Not pick item i (move to previous item)
                    int notTake = dp[i - 1][w];
                    // Pick item i (stay at same item, can reuse)
                    int take = (w >= weight[i]) ? value[i] + dp[i][w - weight[i]] : 0;
                    dp[i][w] = max(notTake, take);
                }
            }
        }

        return dp[n - 1][W];
    }
};

// 4. Space Optimized (O(W) DP)
class Solution {
public:
    // TC: O(n * W), SC: O(W) - only store current row
    int knapsack(int n, int W, vector<int>& weight, vector<int>& value) {
        // For unbounded knapsack, we can optimize to use only one array
        // Process items one by one, updating the same array
        vector<int> dp(W + 1, 0);
        
        for (int i = 0; i < n; ++i) {
            for (int w = 0; w <= W; ++w) {
                int notTake = dp[w];
                int take = 0;
                if (w >= weight[i]) {
                    take = value[i] + dp[w - weight[i]];
                }
                dp[w] = max(notTake, take);
            }
        }
        
        return dp[W];
    }
};
