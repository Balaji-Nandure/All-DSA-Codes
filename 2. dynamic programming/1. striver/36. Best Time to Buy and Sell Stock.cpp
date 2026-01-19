#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;

/*
Problem: Best Time to Buy and Sell Stock (One Transaction)
LeetCode 121: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/stock-buy-and-sell2615/1

You are given an array prices where prices[i] is the price of a given stock on the ith day.
You want to maximize your profit by choosing a single day to buy one stock and choosing 
a different day in the future to sell that stock.

Return the maximum profit you can achieve from this transaction. If you cannot achieve 
any profit, return 0.

Constraints:
- You can only buy once and sell once
- You must buy before you sell
- You cannot sell on the same day you buy

Example:
prices = [7,1,5,3,6,4]
Buy on day 2 (price = 1) and sell on day 5 (price = 6)
Profit = 6 - 1 = 5

DP State: dp[i] = maximum profit we can get by day i
Alternative: Track minimum price seen so far and maximum profit

Recurrence:
- For each day i, we can either:
  1. Not sell (keep previous profit): dp[i] = dp[i-1]
  2. Sell on day i: profit = prices[i] - minPrice (where minPrice is minimum price from day 0 to i-1)
- dp[i] = max(dp[i-1], prices[i] - minPrice)

Base Cases:
- dp[0] = 0 (can't sell on first day)
- minPrice = prices[0]

Time Complexity: O(n) where n is the number of days
Space Complexity: O(n) for DP array, O(1) for optimized approach
*/

// 4. Space Optimization (O(1) DP)
class Solution {
public:
    // TC: O(n), SC: O(1) - only track minPrice and maxProfit
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;
        
        int minPrice = prices[0];
        int maxProfit = 0;
        
        for (int i = 1; i < n; ++i) {
            // Update minimum price seen so far
            minPrice = min(minPrice, prices[i]);
            // Update maximum profit
            maxProfit = max(maxProfit, prices[i] - minPrice);
        }
        
        return maxProfit;
    }
};
