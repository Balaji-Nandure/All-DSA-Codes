// Problem: Best Time to Buy and Sell Stock (Single & Multiple Transactions)
// Link (LeetCode 121): https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
// Link (LeetCode 122 - Multiple): https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/stock-buy-and-sell-1587115621/1
// Article: https://www.geeksforgeeks.org/dsa/best-time-to-buy-and-sell-stock/
// Difficulty: Easy
// Topic: Array, Dynamic Programming, Greedy

/*
Problem Statement:
You are given an array `prices` where `prices[i]` is the price of a given stock on the `i`-th day.
You want to maximize your profit by choosing a single day to buy one stock and choosing a 
different day in the future to sell that stock.
Return the maximum profit you can achieve from this transaction. If no profit can be achieved, return 0.

Also covers Part II: Where you can buy and sell multiple times (at most one stock held at any time).

Example 1:
Input: prices = [7, 1, 5, 3, 6, 4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6 - 1 = 5.

Example 2:
Input: prices = [7, 6, 4, 3, 1]
Output: 0
Explanation: Prices continuously decrease, no profitable transaction possible.

Constraints:
- 1 <= prices.length <= 10^5
- 0 <= prices[i] <= 10^4
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 8 (Kadane): Subarray elements were summed cumulatively.
// - In Problem 16 (Inversions): Counted all pairs where `i < j` and `arr[i] > arr[j]`.
// - In Problem 17 (Stock Buy and Sell):
//   * We want to MAXIMIZE the difference `prices[j] - prices[i]` subject to the constraint `i < j`.
//   * For any selling day `j`, the optimal buying day `i` is ALWAYS the minimum price seen in `[0 ... j - 1]`.

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Brute Force O(N^2)
//   - Check all pairs (buy, sell): O(N^2). TLE for N = 10^5.
//
// Approach 2: One-Pass Greedy Tracking Minimum (OPTIMAL & CHOSEN)
//   - Maintain:
//     * `minPriceSoFar`: The lowest buying price encountered up to the current day.
//     * `maxProfit`: The highest profit achieved if sold today.
//   - For each day's price:
//     * Profit if sold today = `price - minPriceSoFar`.
//     * Update `maxProfit = max(maxProfit, price - minPriceSoFar)`.
//     * Update `minPriceSoFar = min(minPriceSoFar, price)`.
//   - Complexity: Exactly O(N) time in a single pass, O(1) space!

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // -------------------------------------------------------------------------
    // Part 1: Single Transaction Allowed (LeetCode 121 - O(N) Time, O(1) Space)
    // -------------------------------------------------------------------------
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0;

        int minPriceSoFar = prices[0];
        int maxProfit = 0;

        for (int i = 1; i < (int)prices.size(); i++) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // If we sell today at prices[i], the best possible buying day is the day
            // with the minimum price seen so far.
            // We update maxProfit BEFORE updating minPriceSoFar to enforce i < j!
            int currentProfit = prices[i] - minPriceSoFar;
            maxProfit = max(maxProfit, currentProfit);

            // Update the historical low price for future selling days
            minPriceSoFar = min(minPriceSoFar, prices[i]);
        }

        return maxProfit;
    }

    // -------------------------------------------------------------------------
    // Part 2: Multiple Transactions Allowed (LeetCode 122 - Peak-Valley Greedy)
    // -------------------------------------------------------------------------
    int maxProfitMultiple(vector<int>& prices) {
        int totalProfit = 0;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Whenever price increases from day i-1 to day i, we capture that upward slope!
        // Cumulative slope gains equal the optimal peak-to-valley profit.
        for (int i = 1; i < (int)prices.size(); i++) {
            if (prices[i] > prices[i - 1]) {
                totalProfit += (prices[i] - prices[i - 1]);
            }
        }

        return totalProfit;
    }
};

/*
Time Complexity: O(N)
- Single pass through the prices array. Constant O(1) work per element.

Space Complexity: O(1) Auxiliary Space
- Requires only two scalar variables (`minPriceSoFar`, `maxProfit`).

Key Insights:
1. Dynamic Programming in O(1) Space:
   - This is State-reduction DP: `dp[i]` depends ONLY on `min(prices[0 ... i-1])`.
   - Instead of maintaining an array of minimums, a single scalar variable `minPriceSoFar` suffices.
2. Kadane's Connection:
   - If we convert `prices` into daily differences `diff[i] = prices[i] - prices[i-1]`,
     finding the max single stock profit is MATHEMATICALLY IDENTICAL to finding the Maximum Subarray Sum
     on `diff[]` using Kadane's Algorithm!
*/
