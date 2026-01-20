#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;

/*
Problem: Best Time to Buy and Sell Stock with Transaction Fee
LeetCode 714: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/buy-stock-with-transaction-fee/1

You are given an array prices where prices[i] is the price of a given stock on the ith day,
and an integer fee representing a transaction fee.

Find the maximum profit you can achieve. You may complete as many transactions as you like,
but you need to pay the transaction fee for each transaction.

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell 
the stock before you buy again).

Constraints:
- You can make unlimited transactions
- You can only hold at most one share at a time
- You pay a transaction fee when you sell the stock

Example:
prices = [1,3,2,8,4,9], fee = 2
Buy on day 0 (price = 1), sell on day 3 (price = 8), profit = 8-1-2 = 5
Buy on day 4 (price = 4), sell on day 5 (price = 9), profit = 9-4-2 = 3
Total profit = 5 + 3 = 8

DP State: dp[i][hold] = maximum profit on day i
- hold = 0: not holding stock (can buy)
- hold = 1: holding stock (can sell)

Recurrence:
- If not holding (hold = 0):
  - dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i] - fee)
  - Don't buy today OR sell today (if holding, pay fee when selling)
- If holding (hold = 1):
  - dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i])
  - Don't sell today OR buy today (if not holding, no transaction yet)

Base Cases:
- dp[0][0] = 0 (not holding, no profit)
- dp[0][1] = -prices[0] (holding, bought on day 0)

Time Complexity: O(n) where n is the number of days
Space Complexity: O(n) for DP array, O(1) for optimized approach

Note: The transaction fee is typically paid when selling, but can also be paid when buying.
The implementation below assumes fee is paid when selling.
*/

// 1. Recursive approach (take/not take method)
class StockFeeRecursive {
public:
    // TC: O(2^n) exponential, SC: O(n) recursion stack
    int solve(int day, int hold, vector<int>& prices, int fee) {
        // Base case: reached end of array
        if (day == prices.size()) return 0;
        
        if (hold == 0) {
            // Not holding: can buy or skip
            int buy = -prices[day] + solve(day + 1, 1, prices, fee);  // Buy today
            int skip = solve(day + 1, 0, prices, fee);               // Skip today
            return max(buy, skip);
        } else {
            // Holding: can sell (pay fee) or skip
            int sell = prices[day] - fee + solve(day + 1, 0, prices, fee); // Sell today, pay fee
            int skip = solve(day + 1, 1, prices, fee);                      // Skip today
            return max(sell, skip);
        }
    }
    
    int maxProfit(vector<int>& prices, int fee) {
        return solve(0, 0, prices, fee);
    }
};

// 2. Memoization (Top-down DP)
class StockFeeMemoization {
public:
    // TC: O(n), SC: O(n) for dp array + O(n) recursion stack
    int solve(int day, int hold, vector<int>& prices, int fee, vector<vector<int>>& dp) {
        if (day == prices.size()) return 0;
        if (dp[day][hold] != -1) return dp[day][hold];
        
        if (hold == 0) {
            int buy = -prices[day] + solve(day + 1, 1, prices, fee, dp);
            int skip = solve(day + 1, 0, prices, fee, dp);
            return dp[day][hold] = max(buy, skip);
        } else {
            int sell = prices[day] - fee + solve(day + 1, 0, prices, fee, dp);
            int skip = solve(day + 1, 1, prices, fee, dp);
            return dp[day][hold] = max(sell, skip);
        }
    }
    
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int>(2, -1));
        return solve(0, 0, prices, fee, dp);
    }
};

// 3. Tabulation (Bottom-up DP)
class StockFeeTabulation {
public:
    // TC: O(n), SC: O(n) for dp array
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        if (n == 0) return 0;
        
        // dp[i][0] = max profit on day i not holding stock
        // dp[i][1] = max profit on day i holding stock
        vector<vector<int>> dp(n, vector<int>(2, 0));
        
        // Base cases
        dp[0][0] = 0;           // Not holding on day 0
        dp[0][1] = -prices[0];  // Holding on day 0 (bought on day 0)
        
        for (int i = 1; i < n; ++i) {
            // Not holding: max(keep not holding, sell today if holding, pay fee)
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i] - fee);
            // Holding: max(keep holding, buy today if not holding)
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
        }
        
        return dp[n - 1][0]; // Return max profit not holding (always better than holding)
    }
};

// 4. Space Optimization (O(1) DP)
class Solution {
public:
    // TC: O(n), SC: O(1) - only track two states
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        if (n == 0) return 0;
        
        int notHold = 0;              // Not holding stock
        int hold = prices[0];         // Holding stock: store the minimal "cost to acquire" (positive, i.e., spent so far)
        
        for (int i = 1; i < n; ++i) {
            int prevNotHold = notHold;
            int prevHold = hold;
            
            // Not holding: max(keep not holding, sell today if holding, pay fee)
            notHold = max(prevNotHold, prices[i] - prevHold - fee);
            // Holding: min(keep holding cost, buy today if not holding)
            hold = min(prevHold, prices[i] - prevNotHold);
        }
        
        return notHold; // Return max profit not holding
    }
};
