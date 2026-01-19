#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;

/*
Problem: Best Time to Buy and Sell Stock II (Unlimited Transactions)
LeetCode 122: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/stock-buy-and-sell-1587115621/1

You are given an array prices where prices[i] is the price of a given stock on the ith day.
On each day, you may decide to buy and/or sell the stock. You can only hold at most one 
share of the stock at any time. However, you can buy it then immediately sell it on the 
same day.

Find and return the maximum profit you can achieve.

Constraints:
- You can make unlimited transactions
- You can only hold at most one share at a time
- You can buy and sell on the same day

Example:
prices = [7,1,5,3,6,4]
Buy on day 2 (price = 1), sell on day 3 (price = 5), profit = 4
Buy on day 4 (price = 3), sell on day 5 (price = 6), profit = 3
Total profit = 4 + 3 = 7

DP State: dp[i][hold] = maximum profit on day i
- hold = 0: not holding stock (can buy)
- hold = 1: holding stock (can sell)

Recurrence:
- If not holding (hold = 0):
  - dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
  - Don't buy today OR sell today (if holding)
- If holding (hold = 1):
  - dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i])
  - Don't sell today OR buy today (if not holding)

Base Cases:
- dp[0][0] = 0 (not holding, no profit)
- dp[0][1] = -prices[0] (holding, bought on day 0)

Time Complexity: O(n) where n is the number of days
Space Complexity: O(n) for DP array, O(1) for optimized approach
*/

// 1. Recursive approach (take/not take method)
class StockIIRecursive {
public:
    // TC: O(2^n) exponential, SC: O(n) recursion stack
    int solve(int day, int hold, vector<int>& prices) {
        // Base case: reached end of array
        if (day == prices.size()) return 0;
        
        if (hold == 0) {
            // Not holding: can buy or skip
            int buy = -prices[day] + solve(day + 1, 1, prices);  // Buy today
            int skip = solve(day + 1, 0, prices);               // Skip today
            return max(buy, skip);
        } else {
            // Holding: can sell or skip
            int sell = prices[day] + solve(day + 1, 0, prices); // Sell today
            int skip = solve(day + 1, 1, prices);                // Skip today
            return max(sell, skip);
        }
    }
    
    int maxProfit(vector<int>& prices) {
        return solve(0, 0, prices);
    }
};

// 2. Memoization (Top-down DP)
class StockIIMemoization {
public:
    // TC: O(n), SC: O(n) for dp array + O(n) recursion stack
    int solve(int day, int hold, vector<int>& prices, vector<vector<int>>& dp) {
        if (day == prices.size()) return 0;
        if (dp[day][hold] != -1) return dp[day][hold];
        
        if (hold == 0) {
            int buy = -prices[day] + solve(day + 1, 1, prices, dp);
            int skip = solve(day + 1, 0, prices, dp);
            return dp[day][hold] = max(buy, skip);
        } else {
            int sell = prices[day] + solve(day + 1, 0, prices, dp);
            int skip = solve(day + 1, 1, prices, dp);
            return dp[day][hold] = max(sell, skip);
        }
    }
    
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int>(2, -1));
        return solve(0, 0, prices, dp);
    }
};

// 3. Tabulation (Bottom-up DP)
class StockIITabulation {
public:
    // TC: O(n), SC: O(n) for dp array
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;
        
        // dp[i][0] = max profit on day i not holding stock
        // dp[i][1] = max profit on day i holding stock
        vector<vector<int>> dp(n, vector<int>(2, 0));
        
        // Base cases
        dp[0][0] = 0;           // Not holding on day 0
        dp[0][1] = -prices[0];  // Holding on day 0 (bought on day 0)
        
        for (int i = 1; i < n; ++i) {
            // Not holding: max(keep not holding, sell today if holding)
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
            // Holding: max(keep holding, buy today if not holding)
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
        }
        
        return dp[n - 1][0]; // Return max profit not holding (always better than holding)
    }
};


// Alternative: Greedy Approach (Capture all positive differences)
class StockIIGreedy {
public:
    // TC: O(n), SC: O(1) - single pass, capture all upward movements
    int maxProfit(vector<int>& prices) {
        int profit = 0;
        
        // Buy on every dip and sell on every peak
        // Equivalent to capturing all positive price differences
        for (int i = 1; i < prices.size(); ++i) {
            if (prices[i] > prices[i - 1]) {
                profit += prices[i] - prices[i - 1];
            }
        }
        
        return profit;
    }
};
