// Problem: Best Time to Buy and Sell Stock III (At Most Two Transactions)
// Link (LeetCode 123): https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/maximum-profit4657/1
// Article: https://www.geeksforgeeks.org/dsa/maximum-profit-by-buying-and-selling-a-share-at-most-twice/
// Difficulty: Hard
// Topic: Array, Dynamic Programming, State Machine

/*
Problem Statement:
You are given an array `prices` where `prices[i]` is the price of a given stock on the `i`-th day.
Find the maximum profit you can achieve. You may complete AT MOST TWO transactions.
Note: You may not engage in multiple transactions simultaneously (i.e., you must sell before buying again).

Example 1:
Input: prices = [3, 3, 5, 0, 0, 3, 1, 4]
Output: 6
Explanation: 
- Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3 - 0 = 3.
- Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4 - 1 = 3.
Total profit = 3 + 3 = 6.

Example 2:
Input: prices = [1, 2, 3, 4, 5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 4.

Example 3:
Input: prices = [7, 6, 4, 3, 1]
Output: 0
Explanation: No profitable transaction possible.

Constraints:
- 1 <= prices.length <= 10^5
- 0 <= prices[i] <= 10^5
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 17 (Part 1): Exactly 1 transaction allowed -> tracked single `minPriceSoFar`.
// - In Problem 17 (Part 2): Unlimited transactions allowed -> greedily captured every positive slope.
// - In Problem 26:
//   * A STRICT BOUND of at most TWO transactions.
//   * A greedy slope collector fails here (e.g., [1, 2, 4, 2, 5, 7, 2, 4, 90] has too many slopes!).
//   * We must track the state transitions between 1st buy, 1st sell, 2nd buy, and 2nd sell!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Prefix + Suffix Profit Arrays (O(N) Time, O(N) Space)
//   - `leftProfit[i]`: max profit from day 0 to i (1 transaction).
//   - `rightProfit[i]`: max profit from day i to n - 1 (1 transaction).
//   - Max 2-transaction profit = `max(leftProfit[i] + rightProfit[i])` for all i.
//   - Good, but requires O(N) extra space.
//
// Approach 2: 4-State Financial State Machine (OPTIMAL & CHOSEN)
//   - Track our cash balance across 4 sequential financial states:
//     1. `buy1`: Max balance after buying 1st stock (we spend `price`): `max(buy1, -price)`.
//     2. `sell1`: Max profit after selling 1st stock: `max(sell1, buy1 + price)`.
//     3. `buy2`: Max balance after buying 2nd stock using profit from 1st: `max(buy2, sell1 - price)`.
//     4. `sell2`: Max profit after selling 2nd stock: `max(sell2, buy2 + price)`.
//   - Complexity: Exactly O(N) time in a single pass, O(1) space!

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // -------------------------------------------------------------------------
    // Method 1: State Machine DP (O(N) Time, O(1) Auxiliary Space - Optimal)
    // -------------------------------------------------------------------------
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0;

        // buy1 and buy2 represent our effective bank balance after buying (spending cash)
        int buy1 = INT_MIN;
        int sell1 = 0;
        int buy2 = INT_MIN;
        int sell2 = 0;

        for (int price : prices) {
            // 1. Maximize balance after 1st buy (spending 'price')
            buy1 = max(buy1, -price);

            // 2. Maximize profit after 1st sell (closing 1st trade)
            sell1 = max(sell1, buy1 + price);

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // 3. Maximize balance after 2nd buy:
            // We use the profit made from trade 1 (sell1) to subsidize the purchase of stock 2!
            // Our cash in hand becomes (sell1 - price).
            buy2 = max(buy2, sell1 - price);

            // 4. Maximize total profit after 2nd sell
            sell2 = max(sell2, buy2 + price);
        }

        return sell2;
    }

    // -------------------------------------------------------------------------
    // Method 2: Bidirectional DP (Prefix + Suffix Arrays - O(N) Time, O(N) Space)
    // -------------------------------------------------------------------------
    int maxProfitBidirectional(vector<int>& prices) {
        int n = prices.size();
        if (n <= 1) return 0;

        vector<int> leftProfit(n, 0);
        int minPrice = prices[0];
        for (int i = 1; i < n; i++) {
            minPrice = min(minPrice, prices[i]);
            leftProfit[i] = max(leftProfit[i - 1], prices[i] - minPrice);
        }

        vector<int> rightProfit(n, 0);
        int maxPrice = prices[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            maxPrice = max(maxPrice, prices[i]);
            rightProfit[i] = max(rightProfit[i + 1], maxPrice - prices[i]);
        }

        int maxTotalProfit = 0;
        for (int i = 0; i < n; i++) {
            maxTotalProfit = max(maxTotalProfit, leftProfit[i] + rightProfit[i]);
        }

        return maxTotalProfit;
    }
};

/*
Time Complexity: O(N)
- Method 1: Single pass through prices: O(N).
- Method 2: Three passes (left, right, combine): O(3N) = O(N).

Space Complexity:
- Method 1: O(1) Auxiliary Space — strictly 4 integer scalar variables.
- Method 2: O(N) Auxiliary Space — two arrays `leftProfit` and `rightProfit` of size N.

Key Insights:
1. Reinvesting Profit:
   - `buy2 = max(buy2, sell1 - price)` embodies the concept of "effective cost":
     The net cost of the second stock is `price - sell1`.
   - Selling the second stock at `price2` yields `buy2 + price2 = price2 - (price - sell1) = profit1 + profit2`!
2. Generalization to K Transactions (LeetCode 188):
   - This exact state machine scales directly to K transactions by maintaining arrays `buy[k]` and `sell[k]`.
*/
