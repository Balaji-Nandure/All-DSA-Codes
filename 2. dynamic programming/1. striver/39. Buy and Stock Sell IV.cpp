#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;

/*
Problem: Best Time to Buy and Sell Stock IV (At Most K Transactions)
LeetCode 188: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/maximum-profit4657/1

You are given an integer array prices where prices[i] is the price of a given stock on the ith day,
and an integer k. Find the maximum profit you can achieve. You may complete at most k transactions.

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell 
the stock before you buy again).

Constraints:
- You can make at most k transactions
- A transaction consists of buying and then selling
- You can only hold at most one share at a time

Example:
prices = [2,4,1], k = 2
Buy on day 0 (price = 2), sell on day 1 (price = 4), profit = 2
Total profit = 2

prices = [3,2,6,5,0,3], k = 2
Buy on day 1 (price = 2), sell on day 2 (price = 6), profit = 4
Buy on day 4 (price = 0), sell on day 5 (price = 3), profit = 3
Total profit = 4 + 3 = 7

DP State: dp[i][hold][trans] = maximum profit on day i
- hold = 0: not holding stock (can buy)
- hold = 1: holding stock (can sell)
- trans = 0, 1, ..., k: number of transactions completed (a transaction is completed when we sell)

Recurrence:
- If not holding (hold = 0):
  - dp[i][0][trans] = max(dp[i-1][0][trans], dp[i-1][1][trans-1] + prices[i])
  - Don't buy today OR sell today (if holding, transaction completed)
- If holding (hold = 1):
  - dp[i][1][trans] = max(dp[i-1][1][trans], dp[i-1][0][trans] - prices[i])
  - Don't sell today OR buy today (if not holding, no transaction yet)
  - Note: When we sell, trans increases, but we can only sell if trans < k

Base Cases:
- dp[0][0][0] = 0 (not holding, no transactions)
- dp[0][1][0] = -prices[0] (holding, bought on day 0, no transactions completed yet)

Time Complexity: O(n * 2 * k) = O(n*k) where n is the number of days
Space Complexity: O(n * 2 * k) for DP array, O(2 * k) for optimized approach

Optimization: If k >= n/2, we can make unlimited transactions (same as Stock II)
*/

// 1. Recursive approach (take/not take method)
class StockIVRecursive {
public:
    // TC: O(2^n) exponential, SC: O(n) recursion stack
    int solve(int day, int hold, int trans, int k, vector<int>& prices) {
        // Base case: reached end of array or completed k transactions
        if (day == prices.size() || trans == k) {
            return 0;
        }
        
        if (hold == 0) {
            // Not holding: can buy or skip
            int buy = -prices[day] + solve(day + 1, 1, trans, k, prices);  // Buy today
            int skip = solve(day + 1, 0, trans, k, prices);                // Skip today
            return max(buy, skip);
        } else {
            // Holding: can sell (completes transaction) or skip
            int sell = prices[day] + solve(day + 1, 0, trans + 1, k, prices); // Sell today
            int skip = solve(day + 1, 1, trans, k, prices);                     // Skip today
            return max(sell, skip);
        }
    }
    
    int maxProfit(int k, vector<int>& prices) {
        return solve(0, 0, 0, k, prices);
    }
};

// 2. Memoization (Top-down DP)
class StockIVMemoization {
public:
    // TC: O(n * 2 * k) = O(n*k), SC: O(n * 2 * k) for dp array + O(n) recursion stack
    int solve(int day, int hold, int trans, int k, vector<int>& prices, vector<vector<vector<int>>>& dp) {
        if (day == prices.size() || trans == k) return 0;
        if (dp[day][hold][trans] != -1) return dp[day][hold][trans];
        
        if (hold == 0) {
            int buy = -prices[day] + solve(day + 1, 1, trans, k, prices, dp);
            int skip = solve(day + 1, 0, trans, k, prices, dp);
            return dp[day][hold][trans] = max(buy, skip);
        } else {
            int sell = prices[day] + solve(day + 1, 0, trans + 1, k, prices, dp);
            int skip = solve(day + 1, 1, trans, k, prices, dp);
            return dp[day][hold][trans] = max(sell, skip);
        }
    }
    
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        // Optimization: if k >= n/2, we can make unlimited transactions
        if (k >= n / 2) {
            int profit = 0;
            for (int i = 1; i < n; ++i) {
                if (prices[i] > prices[i - 1]) {
                    profit += prices[i] - prices[i - 1];
                }
            }
            return profit;
        }
        
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(k + 1, -1)));
        return solve(0, 0, 0, k, prices, dp);
    }
};

// 3. Tabulation (Bottom-up DP)
class StockIVTabulation {
public:
    // TC: O(n * 2 * k) = O(n*k), SC: O(n * 2 * k) for dp array
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (n == 0 || k == 0) return 0;
        
        // Optimization: if k >= n/2, we can make unlimited transactions
        if (k >= n / 2) {
            int profit = 0;
            for (int i = 1; i < n; ++i) {
                if (prices[i] > prices[i - 1]) {
                    profit += prices[i] - prices[i - 1];
                }
            }
            return profit;
        }
        
        // dp[i][hold][trans] = max profit on day i with hold state and trans transactions
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(k + 1, 0)));
        
        // Base cases
        dp[0][0][0] = 0;           // Not holding, no transactions
        dp[0][1][0] = -prices[0];  // Holding, bought on day 0, no transactions completed
        
        for (int i = 1; i < n; ++i) {
            for (int trans = 0; trans <= k; ++trans) {
                // Not holding: max(keep not holding, sell today if holding)
                dp[i][0][trans] = dp[i - 1][0][trans];
                if (trans > 0) {
                    // Can only sell if we have at least 1 transaction completed
                    // When we sell, we complete a transaction, so we look at trans-1
                    dp[i][0][trans] = max(dp[i][0][trans], dp[i - 1][1][trans - 1] + prices[i]);
                }
                
                // Holding: max(keep holding, buy today if not holding)
                dp[i][1][trans] = max(dp[i - 1][1][trans], dp[i - 1][0][trans] - prices[i]);
            }
        }
        
        // Return maximum profit with 0 to k transactions (not holding)
        int maxProfit = 0;
        for (int trans = 0; trans <= k; ++trans) {
            maxProfit = max(maxProfit, dp[n - 1][0][trans]);
        }
        return maxProfit;
    }
};

// 4. Space Optimization (O(k) DP - only 2*(k+1) states)
class Solution {
public:
    // TC: O(n * k), SC: O(k) - only track 2*(k+1) states
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (n == 0 || k == 0) return 0;
        
        // Optimization: if k >= n/2, we can make unlimited transactions
        if (k >= n / 2) {
            int profit = 0;
            for (int i = 1; i < n; ++i) {
                if (prices[i] > prices[i - 1]) {
                    profit += prices[i] - prices[i - 1];
                }
            }
            return profit;
        }
        
        // dp[hold][trans] = max profit with hold state and trans transactions
        // We only need previous day's states
        vector<vector<int>> prev(2, vector<int>(k + 1, 0));
        vector<vector<int>> curr(2, vector<int>(k + 1, 0));
        
        // Base cases
        prev[0][0] = 0;           // Not holding, no transactions
        prev[1][0] = -prices[0]; // Holding, bought on day 0
        
        for (int i = 1; i < n; ++i) {
            for (int trans = 0; trans <= k; ++trans) {
                // Not holding: max(keep not holding, sell today if holding)
                curr[0][trans] = prev[0][trans];
                if (trans > 0) {
                    curr[0][trans] = max(curr[0][trans], prev[1][trans - 1] + prices[i]);
                }
                
                // Holding: max(keep holding, buy today if not holding)
                curr[1][trans] = max(prev[1][trans], prev[0][trans] - prices[i]);
            }
            prev = curr;
        }
        
        // Return maximum profit with 0 to k transactions (not holding)
        int maxProfit = 0;
        for (int trans = 0; trans <= k; ++trans) {
            maxProfit = max(maxProfit, prev[0][trans]);
        }
        return maxProfit;
    }
};



// This is best solution similar to  the Stock III State Tracking Approach
/*
Approach: 
=========
- We use a state compression dynamic programming method (an optimized form of DP) to solve the "Best Time to Buy and Sell Stock IV" problem in O(n*k) time and O(k) space.
- Instead of a full 3D DP (day, hold, transactions), we only track two 1D arrays: `buy` and `sell`.
    - buy[i]: minimal effective "cost" to hold a stock after i transactions (minimized through the journey)
    - sell[i]: maximal profit after i completed transactions (maximized through the journey)

- For each price and for each allowed transaction (from 1 to k):
    - buy[i] = min(buy[i], price - sell[i-1]);
        // Either keep prev buy, or "buy now" using profit up to previous sell state.
    - sell[i] = max(sell[i], price - buy[i]);
        // Either keep prev sell profit, or "sell now" using current effective buy cost.

Why this works:
===============
- We simulate the state of having completed i-1 transactions and then buying again (buy[i]), then selling for i'th transaction (sell[i]).
- Each iteration updates these states to keep the optimal "cost" for next buy and optimal "profit" for next sell.
- At the end, sell[k] holds the max profit after at most k transactions.

Dry Run Example:
================
Let prices = [3, 2, 6, 5, 0, 3], k = 2

Initialization:
    buy = [3, 3, 3]
    sell = [0, 0, 0]

Iterate over prices:
- price=3: no change, buy=[3,3,3], sell=[0,0,0]
- price=2:
    For i=1: buy[1]=min(3,2-0)=2, sell[1]=max(0,2-2)=0
    For i=2: buy[2]=min(3,2-0)=2, sell[2]=max(0,2-2)=0
    buy=[3,2,2], sell=[0,0,0]
- price=6:
    For i=1: buy[1]=min(2,6-0)=2, sell[1]=max(0,6-2)=4
    For i=2: buy[2]=min(2,6-4)=2, sell[2]=max(0,6-2)=4
    buy=[3,2,2], sell=[0,4,4]
- price=5:
    For i=1: buy[1]=min(2,5-0)=2, sell[1]=max(4,5-2)=4
    For i=2: buy[2]=min(2,5-4)=1, sell[2]=max(4,5-1)=4
    buy=[3,2,1], sell=[0,4,4]
- price=0:
    For i=1: buy[1]=min(2,0-0)=0, sell[1]=max(4,0-0)=4
    For i=2: buy[2]=min(1,0-4)=-4, sell[2]=max(4,0-(-4))=4
    buy=[3,0,-4], sell=[0,4,4]
- price=3:
    For i=1: buy[1]=min(0,3-0)=0, sell[1]=max(4,3-0)=4
    For i=2: buy[2]=min(-4,3-4)=-4, sell[2]=max(4,3-(-4))=7

Final answer: sell[2]=7

Code:
=====*/

class Solution {
public:
    // O(n * k) time, O(k) space
    int maxProfit(int k, vector<int>& prices) {
        if (prices.empty() || k == 0) return 0;

        int n = prices.size();
        // Edge optimization: if k >= n/2, it's equivalent to Stock II (unlimited transactions)
        if (k >= n / 2) {
            int profit = 0;
            for (int i = 1; i < n; ++i)
                if (prices[i] > prices[i-1]) profit += prices[i]-prices[i-1];
            return profit;
        }

        // buy[i]: minimal effective cost after i-th buy (start with first price)
        vector<int> buy(k + 1, prices[0]);
        // sell[i]: max profit after i-th sell (start with zero profit)
        vector<int> sell(k + 1, 0);

        for (int price : prices) {
            for (int i = 1; i <= k; i++) {
                // Try to get the lowest cost for buy[i], using profit after i-1 sells
                buy[i]  = min(buy[i], price - sell[i - 1]);
                // Try to maximize profit after i-th sell, based on current best buy[i]
                sell[i] = max(sell[i], price - buy[i]);
            }
        }

        return sell[k];
    }
};
