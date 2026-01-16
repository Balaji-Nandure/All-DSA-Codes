#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;

/*
Problem: 0/1 Knapsack

GeeksforGeeks: https://practice.geeksforgeeks.org/problems/0-1-knapsack-problem0945/1
LeetCode: N/A (similar concepts in various problems)

You are given weights and values of n items. Put these items in a knapsack of capacity W 
to get the maximum total value in the knapsack. Each item can be used at most once.

Constraints:
- Each item can be picked at most once (0 or 1)
- Maximize total value without exceeding capacity W

Example:
weights = [1, 2, 3], values = [10, 15, 40], W = 6
Pick items 2 and 3: value = 15 + 40 = 55, weight = 2 + 3 = 5 <= 6
Maximum value = 55

DP State: dp[i][w] = maximum value we can get using first i items with capacity w
Recurrence:
dp[i][w] = max(dp[i-1][w], dp[i-1][w - weights[i-1]] + values[i-1])
- dp[i-1][w]: not pick item i-1
- dp[i-1][w - weights[i-1]] + values[i-1]: pick item i-1 (if w >= weights[i-1])

Base Cases:
- dp[0][w] = 0 for all w (no items, no value)
- dp[i][0] = 0 for all i (no capacity, no value)

Time Complexity: O(n * W)
Space Complexity: O(n * W) for memoization/tabulation, O(W) for space optimization
*/

// 1. Recursive approach (take/not take method)
class KnapsackRecursive {
public:
    // TC: O(2^n) exponential, SC: O(n) recursion stack
    int solve(int indx, vector<int>& weight, vector<int>& value, int capacity) {
        // Base case: no more items or no capacity left
        if (indx == weight.size() || capacity == 0) return 0;
        
        // Not pick current item
        int notPick = solve(indx + 1, weight, value, capacity);
        
        // Pick current item if it fits
        int pick = 0;
        if (capacity >= weight[indx])
            pick = value[indx] + solve(indx + 1, weight, value, capacity - weight[indx]);
        
        return max(pick, notPick);
    }
    
    int knapsack(int n, int W, vector<int>& weight, vector<int>& value) {
        return solve(0, weight, value, W);
    }
};

// 2. Memoization (Top-down DP)
class KnapsackMemoization {
public:
    // TC: O(n * W), SC: O(n * W) for dp array + O(n) recursion stack
    int solve(int indx, int capacity, vector<int>& weight, vector<int>& value, 
              vector<vector<int>>& dp) {
        // Base case: no more items or no capacity left
        if (indx == weight.size() || capacity == 0) return 0;
        
        // Return cached result
        if (dp[indx][capacity] != -1) return dp[indx][capacity];
        
        // Not pick current item
        int notPick = solve(indx + 1, capacity, weight, value, dp);
        
        // Pick current item if it fits
        int pick = 0;
        if (capacity >= weight[indx])
            pick = value[indx] + solve(indx + 1, capacity - weight[indx], weight, value, dp);
        
        return dp[indx][capacity] = max(pick, notPick);
    }
    
    int knapsack(int n, int W, vector<int>& weight, vector<int>& value) {
        vector<vector<int>> dp(n + 1, vector<int>(W + 1, -1));
        return solve(0, W, weight, value, dp);
    }
};

// 3. Tabulation (Bottom-up DP)
class KnapsackTabulation {
public:
    // TC: O(n * W), SC: O(n * W) for dp array
    int knapsack(int n, int W, vector<int>& weight, vector<int>& value) {
        // dp[i][w]: maximum value using first i items with capacity w
        // Improved: clearer variable names, explicit initialization, concise logic, consistent comments

        // dp[i][w]: max value using first (i+1) items, with knapsack capacity w
        vector<vector<int>> dp(n, vector<int>(W + 1, 0));
        // Merge the initialization of dp[0][w] into the main loop to avoid separate base case
        for (int i = 0; i < n; ++i) {
            for (int w = 0; w <= W; ++w) {
                if (i == 0) {
                    dp[0][w] = (w >= weight[0]) ? value[0] : 0;
                } else {
                    int notTake = dp[i - 1][w];
                    int take = (w >= weight[i]) ? value[i] + dp[i - 1][w - weight[i]] : 0;
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
    // TC: O(n * W), SC: O(W) - only store previous row
    int knapsack(int n, int W, vector<int>& weight, vector<int>& value) {
        vector<int> prev(W + 1, 0);
        
        for (int i = 0; i < n; ++i) {
            vector<int> curr(W + 1, 0);
            for (int w = 0; w <= W; ++w) {
                // Not pick weight[i]
                curr[w] = prev[w];
                // Pick weight[i] if it fits
                if (w >= weight[i])
                    curr[w] = max(curr[w], prev[w - weight[i]] + value[i]);
            }
            prev = curr;
        }
        
        return prev[W];
    }
};
