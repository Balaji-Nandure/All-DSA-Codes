#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;

/*
Problem: Best Time to Buy and Sell Stock with Cooldown
LeetCode 309: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/buy-stock-with-cooldown/1

You are given an array prices where prices[i] is the price of a given stock on the ith day.
Find the maximum profit you can achieve. You may complete as many transactions as you like 
(i.e., buy one and sell one share of the stock multiple times) with the following constraints:

- After you sell your stock, you cannot buy stock on the next day (i.e., cooldown 1 day).

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell 
the stock before you buy again).

Constraints:
- You can make unlimited transactions
- You can only hold at most one share at a time
- After selling, you must wait 1 day before buying again (cooldown)

Example:
prices = [1,2,3,0,2]
Buy on day 0 (price = 1), sell on day 1 (price = 2), cooldown on day 2
Buy on day 3 (price = 0), sell on day 4 (price = 2)
Total profit = (2-1) + (2-0) = 3

DP State: dp[i][state] = maximum profit on day i
- state = 0: not holding, can buy (not in cooldown)
- state = 1: holding stock (can sell)
- state = 2: not holding, in cooldown (just sold yesterday, cannot buy today)

Alternative simpler state:
- state = 0: not holding (can buy if not in cooldown)
- state = 1: holding (can sell)

But we need to track cooldown, so we use:
- dp[i][hold][cooldown] where cooldown = 0 or 1
OR
- Use three states as above

Recurrence (3-state approach):
- If state = 0 (not holding, can buy):
  - dp[i][0] = max(dp[i-1][0], dp[i-1][2])
  - Stay not holding OR come from cooldown
- If state = 1 (holding):
  - dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i])
  - Keep holding OR buy today (from state 0)
- If state = 2 (cooldown):
  - dp[i][2] = dp[i-1][1] + prices[i]
  - Must have sold today (from state 1)

Base Cases:
- dp[0][0] = 0 (not holding, can buy)
- dp[0][1] = -prices[0] (holding, bought on day 0)
- dp[0][2] = 0 (cooldown, but we haven't sold yet)

Time Complexity: O(n) where n is the number of days
Space Complexity: O(n) for DP array, O(1) for optimized approach
*/

// 1. Recursive approach (take/not take method)
class StockCooldownRecursive {
public:
    // TC: O(3^n) exponential, SC: O(n) recursion stack
    int solve(int day, int state, vector<int>& prices) {
        // Base case: reached end of array
        if (day == prices.size()) return 0;
        
        if (state == 0) {
            // Not holding, can buy: buy or skip
            int buy = -prices[day] + solve(day + 1, 1, prices);  // Buy today
            int skip = solve(day + 1, 0, prices);                // Skip today
            return max(buy, skip);
        } else if (state == 1) {
            // Holding: sell or skip
            int sell = prices[day] + solve(day + 1, 2, prices); // Sell today (go to cooldown)
            int skip = solve(day + 1, 1, prices);                // Skip today
            return max(sell, skip);
        } else {
            // Cooldown: must skip (cannot buy)
            return solve(day + 1, 0, prices); // After cooldown, can buy again
        }
    }
    
    int maxProfit(vector<int>& prices) {
        return solve(0, 0, prices);
    }
};

// 2. Memoization (Top-down DP)
class StockCooldownMemoization {
public:
    // TC: O(n * 3) = O(n), SC: O(n * 3) for dp array + O(n) recursion stack
    int solve(int day, int state, vector<int>& prices, vector<vector<int>>& dp) {
        if (day == prices.size()) return 0;
        if (dp[day][state] != -1) return dp[day][state];
        
        if (state == 0) {
            int buy = -prices[day] + solve(day + 1, 1, prices, dp);
            int skip = solve(day + 1, 0, prices, dp);
            return dp[day][state] = max(buy, skip);
        } else if (state == 1) {
            int sell = prices[day] + solve(day + 1, 2, prices, dp);
            int skip = solve(day + 1, 1, prices, dp);
            return dp[day][state] = max(sell, skip);
        } else {
            return dp[day][state] = solve(day + 1, 0, prices, dp);
        }
    }
    
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int>(3, -1));
        return solve(0, 0, prices, dp);
    }
};

// 3. Tabulation (Bottom-up DP)
class StockCooldownTabulation {
public:
    // TC: O(n), SC: O(n * 3) for dp array
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;
        
        // dp[i][state] = max profit on day i with state
        // state 0: not holding, can buy
        // state 1: holding
        // state 2: cooldown
        vector<vector<int>> dp(n, vector<int>(3, 0));
        
        // Base cases
        dp[0][0] = 0;           // Not holding, can buy
        dp[0][1] = -prices[0];  // Holding, bought on day 0
        dp[0][2] = 0;           // Cooldown (not applicable on day 0)
        
        for (int i = 1; i < n; ++i) {
            // State 0: not holding, can buy
            // Can come from: state 0 (stayed not holding) or state 2 (cooldown ended)
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][2]);
            
            // State 1: holding
            // Can come from: state 1 (kept holding) or state 0 (bought today)
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
            
            // State 2: cooldown (just sold yesterday)
            // Can only come from: state 1 (sold today)
            dp[i][2] = dp[i - 1][1] + prices[i];
        }
        
        // Return max of not holding (state 0) or cooldown (state 2)
        return max(dp[n - 1][0], dp[n - 1][2]);
    }
};

// 4. Space Optimization (O(1) DP - only 3 states)
class Solution {
public:
    // TC: O(n), SC: O(1) - only track 3 states
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;
        
        // Track three states: notHold, hold, cooldown
        int notHold = 0;        // Not holding, can buy
        int hold = -prices[0];  // Holding
        int cooldown = 0;       // Cooldown
        
        for (int i = 1; i < n; ++i) {
            int prevNotHold = notHold;
            int prevHold = hold;
            int prevCooldown = cooldown;
            
            // Not holding: max(stay not holding, come from cooldown)
            notHold = max(prevNotHold, prevCooldown);
            
            // Holding: max(keep holding, buy today from not holding)
            hold = max(prevHold, prevNotHold - prices[i]);
            
            // Cooldown: must have sold today (from holding)
            cooldown = prevHold + prices[i];
        }
        
        // Return max of not holding or cooldown
        return max(notHold, cooldown);
    }
};