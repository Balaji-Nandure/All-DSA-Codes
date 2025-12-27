/*
 * Problem: Best Time to Buy and Sell Stock II
 * 
 * LeetCode: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/
 * GeeksforGeeks: https://www.geeksforgeeks.org/stock-buy-sell/
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/stock-buy-and-sell-1587115621/1
 * 
 * LeetCode 122: Best Time to Buy and Sell Stock II
 * 
 * You are given an integer array prices where prices[i] is the price of a given 
 * stock on the ith day.
 * 
 * On each day, you may decide to buy and/or sell the stock. You can only hold 
 * at most one share of the stock at any time. However, you can buy it then 
 * immediately sell it on the same day.
 * 
 * Find and return the maximum profit you can achieve.
 * 
 * Example 1:
 * Input: prices = [7,1,5,3,6,4]
 * Output: 7
 * Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5), 
 *              profit = 5-1 = 4. Then buy on day 4 (price = 3) and sell on 
 *              day 5 (price = 6), profit = 6-3 = 3. Total profit = 4+3 = 7.
 * 
 * Example 2:
 * Input: prices = [1,2,3,4,5]
 * Output: 4
 * Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), 
 *              profit = 5-1 = 4. Or buy on day 1, sell on day 2, buy on day 2, 
 *              sell on day 3, etc. Total profit = 4.
 * 
 * Example 3:
 * Input: prices = [7,6,4,3,1]
 * Output: 0
 * Explanation: No transaction is done, max profit = 0.
 * 
 * Constraints:
 * - 1 <= prices.length <= 3 * 10^4
 * - 0 <= prices[i] <= 10^4
 * 
 * Approach:
 * - Greedy: Capture every positive price difference
 * - If price[i] > price[i-1], add the difference to profit
 * - This is equivalent to buying on every dip and selling on every peak
 * - Since we can do multiple transactions, we can capture all upward movements
 * 
 * Time: O(n) - single pass through the array
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // APPROACH 1: Greedy (Optimal) - Capture all positive differences
    int maxProfit(vector<int>& prices) {
        int profit = 0;
        
        for (int i = 1; i < prices.size(); i++) {
            // If price increased, add the difference to profit
            if (prices[i] > prices[i - 1]) {
                profit += prices[i] - prices[i - 1];
            }
        }
        
        return profit;
    }
};