#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

/**
 * Problem: Maximum profit by buying and selling a share at most twice
 * 
 * Given daily stock prices, find the maximum profit that can be achieved 
 * by completing AT MOST TWO transactions (2 buys and 2 sells).
 * You cannot hold two shares simultaneously (you must sell before buying again).
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - With 1 transaction, Kadane-like min-price tracking takes O(N) time and O(1) space.
 * - With unlimited transactions, greedy local peak-valley addition takes O(N).
 * - With EXACTLY AT MOST 2 transactions, early profit can be reinvested into a later trade.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - 4-State Machine Dynamic Programming in O(N) Time and O(1) Space:
 *   Track the maximum capital balance across the 4 sequential milestones:
 *   
 *   1. `buy1`: Maximum balance after the FIRST BUY:
 *      buy1 = max(buy1, -price)
 *      (We want to buy at the cheapest possible price, minimizing the negative impact on cash).
 *   
 *   2. `sell1`: Maximum balance after the FIRST SELL:
 *      sell1 = max(sell1, buy1 + price)
 *      (Cash balance after realizing profit from trade 1).
 *   
 *   3. `buy2`: Maximum balance after the SECOND BUY:
 *      buy2 = max(buy2, sell1 - price)
 *      (Reinvesting trade 1's cash balance into purchasing stock for trade 2).
 *   
 *   4. `sell2`: Maximum balance after the SECOND SELL:
 *      sell2 = max(sell2, buy2 + price)
 *      (Final realized net profit from both transactions).
 *   
 *   Why this 4-variable update works:
 *     Updating in order (buy1 -> sell1 -> buy2 -> sell2) simulates an optimal online trader 
 *     who dynamically determines whether 0, 1, or 2 trades maximizes the final return.
 */

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n <= 1) return 0;

        int buy1 = INT_MIN;
        int sell1 = 0;
        int buy2 = INT_MIN;
        int sell2 = 0;

        for (int p : prices) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // 4-state pipeline updating maximum balance through each transaction phase
            buy1  = max(buy1,  -p);          // First buy: minimize purchase cost
            sell1 = max(sell1, buy1 + p);    // First sell: lock in first trade profit
            buy2  = max(buy2,  sell1 - p);   // Second buy: reinvest trade 1 profits
            sell2 = max(sell2, buy2 + p);    // Second sell: final combined profit
        }

        return sell2;
    }

    // Alternative: Prefix-Suffix Split in O(N) Time and O(N) Space
    int maxProfitPrefixSuffix(vector<int>& prices) {
        int n = prices.size();
        if (n <= 1) return 0;

        // left[i]: max profit from 1 transaction on or before day i
        vector<int> left(n, 0);
        int min_price = prices[0];
        for (int i = 1; i < n; i++) {
            min_price = min(min_price, prices[i]);
            left[i] = max(left[i - 1], prices[i] - min_price);
        }

        // right[i]: max profit from 1 transaction on or after day i
        vector<int> right(n, 0);
        int max_price = prices[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            max_price = max(max_price, prices[i]);
            right[i] = max(right[i + 1], max_price - prices[i]);
        }

        int max_total = 0;
        for (int i = 0; i < n; i++) {
            max_total = max(max_total, left[i] + right[i]);
        }

        return max_total;
    }
};

int main() {
    Solution sol;
    vector<int> p1 = {3, 3, 5, 0, 0, 3, 1, 4};
    cout << "Max Profit 1 (O(1) space): " << sol.maxProfit(p1) << "\n"; // Buy day 4 (0), sell day 6 (3) + buy day 7 (1), sell day 8 (4) = 3 + 3 = 6.
    cout << "Max Profit 1 (Prefix-Suffix): " << sol.maxProfitPrefixSuffix(p1) << "\n";

    vector<int> p2 = {1, 2, 3, 4, 5};
    cout << "Max Profit 2: " << sol.maxProfit(p2) << "\n"; // Expected: 4 (single trade from 1 to 5)

    vector<int> p3 = {7, 6, 4, 3, 1};
    cout << "Max Profit 3: " << sol.maxProfit(p3) << "\n"; // Expected: 0 (no profitable trades)

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N) single linear scan over the prices vector.
 * - Space Complexity: O(1) auxiliary space using 4 integer state variables.
 */
