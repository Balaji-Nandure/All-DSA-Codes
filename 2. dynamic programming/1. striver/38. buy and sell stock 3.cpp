#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;

/*
Problem: Best Time to Buy and Sell Stock III (At Most 2 Transactions)
LeetCode 123: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/buy-and-sell-a-share-at-most-twice/1

You are given an array prices where prices[i] is the price of a given stock on the ith day.
Find the maximum profit you can achieve. You may complete at most two transactions.

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell 
the stock before you buy again).

Constraints:
- You can make at most 2 transactions
- A transaction consists of buying and then selling
- You can only hold at most one share at a time

Example:
prices = [3,3,5,0,0,3,1,4]
Buy on day 4 (price = 0), sell on day 6 (price = 3), profit = 3
Buy on day 7 (price = 1), sell on day 8 (price = 4), profit = 3
Total profit = 3 + 3 = 6

DP State: dp[i][hold][trans] = maximum profit on day i
- hold = 0: not holding stock (can buy)
- hold = 1: holding stock (can sell)
- trans = 0, 1, or 2: number of transactions completed (a transaction is completed when we sell)

Recurrence:
- If not holding (hold = 0):
  - dp[i][0][trans] = max(dp[i-1][0][trans], dp[i-1][1][trans] + prices[i])
  - Don't buy today OR sell today (if holding, transaction completed)
- If holding (hold = 1):
  - dp[i][1][trans] = max(dp[i-1][1][trans], dp[i-1][0][trans] - prices[i])
  - Don't sell today OR buy today (if not holding, no transaction yet)
  - Note: When we sell, trans increases, but we can only sell if trans < 2

Base Cases:
- dp[0][0][0] = 0 (not holding, no transactions)
- dp[0][1][0] = -prices[0] (holding, bought on day 0, no transactions completed yet)

Time Complexity: O(n * 2 * 3) = O(n) where n is the number of days
Space Complexity: O(n * 2 * 3) for DP array, O(2 * 3) = O(1) for optimized approach
*/

// 1. Recursive approach (take/not take method)
class StockIIIRecursive {
public:
    // TC: O(3^n) exponential, SC: O(n) recursion stack
    int solve(int day, int hold, int trans, vector<int>& prices) {
        // Base case: reached end of array or completed 2 transactions
        if (day == prices.size() || trans == 2) {
            return 0;
        }
        
        if (hold == 0) {
            // Not holding: can buy or skip
            int buy = -prices[day] + solve(day + 1, 1, trans, prices);  // Buy today
            int skip = solve(day + 1, 0, trans, prices);                // Skip today
            return max(buy, skip);
        } else {
            // Holding: can sell (completes transaction) or skip
            int sell = prices[day] + solve(day + 1, 0, trans + 1, prices); // Sell today
            int skip = solve(day + 1, 1, trans, prices);                     // Skip today
            return max(sell, skip);
        }
    }
    
    int maxProfit(vector<int>& prices) {
        return solve(0, 0, 0, prices);
    }
};

// 2. Memoization (Top-down DP)
class StockIIIMemoization {
public:
    // TC: O(n * 2 * 3) = O(n), SC: O(n * 2 * 3) for dp array + O(n) recursion stack
    int solve(int day, int hold, int trans, vector<int>& prices, vector<vector<vector<int>>>& dp) {
        if (day == prices.size() || trans == 2) return 0;
        if (dp[day][hold][trans] != -1) return dp[day][hold][trans];
        
        if (hold == 0) {
            int buy = -prices[day] + solve(day + 1, 1, trans, prices, dp);
            int skip = solve(day + 1, 0, trans, prices, dp);
            return dp[day][hold][trans] = max(buy, skip);
        } else {
            int sell = prices[day] + solve(day + 1, 0, trans + 1, prices, dp);
            int skip = solve(day + 1, 1, trans, prices, dp);
            return dp[day][hold][trans] = max(sell, skip);
        }
    }
    
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(3, -1)));
        return solve(0, 0, 0, prices, dp);
    }
};

/*
Optimized State Tracking Approach (O(n) time, O(1) space):

We track four states throughout the price array:
    - firstBuy:    Maximum profit after buying the first stock (most negative outlay so far).
    - firstSell:   Maximum profit after selling the first stock (real profit after the first sell).
    - secondBuy:   Maximum profit after buying the second stock (profit after using the gains from the first sell to buy again).
    - secondSell:  Maximum profit after selling the second stock (total realized profit after two sells).

At each price:
    - firstBuy:    Buy for the lowest price possible so far.
    - firstSell:   Maximize profit by selling at the current price if we've bought.
    - secondBuy:   Use the profit from firstSell to "buy" again, maximizing effective cash left after second buy.
    - secondSell:  Maximize total profit by selling again.

Algorithm:
1. Iterate over prices.
2. For each price, update the four states as described above.
3. The answer (maximum profit after at most two trades) is held in secondSell.

Implementation:
*/
class StockIIIStateTracking {
public:
    // TC: O(n), SC: O(1)
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0;
        int firstBuy = prices[0];         // Cost of first buy (minimal price so far)
        int firstSell = 0;                // Profit after first sell
        int secondBuy = prices[0];        // Effective cost for second buy (taking profit from firstSell into account)
        int secondSell = 0;               // Profit after second sell

        for (int i = 1; i < prices.size(); ++i) {
            firstBuy = min(firstBuy, prices[i]);                       // Get lowest price for first buy
            firstSell = max(firstSell, prices[i] - firstBuy);          // Maximize profit after first sell
            secondBuy = min(secondBuy, prices[i] - firstSell);         // Effective lowest price for second buy (after first profit)
            secondSell = max(secondSell, prices[i] - secondBuy);       // Maximize profit after second sell
        }
        return secondSell;
    }
};