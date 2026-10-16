/**
 * ============================================================================
 * Problem: Buy Maximum Stocks if i Stocks Can Be Bought on i-th Day
 * Category: Greedy
 * 
 * Problem Statement:
 * In a stock market, the price of a stock on N consecutive days is given in an 
 * array `price[]`.
 * On the i-th day (1-indexed), an investor is allowed to buy at most `i` stocks.
 * The investor has a total budget of `K` money.
 * 
 * Find the maximum total number of stocks the investor can buy.
 * 
 * Example 1:
 * Input:
 *   price[] = {10, 7, 19}
 *   K = 45
 * Output: 4
 * Explanation:
 *   Day 1: price = 10, max stocks = 1
 *   Day 2: price = 7,  max stocks = 2
 *   Day 3: price = 19, max stocks = 3
 *   Sorted by price:
 *     Day 2 (price 7): buy 2 stocks for 2 * 7 = 14 (remaining K = 31, total = 2)
 *     Day 1 (price 10): buy 1 stock for 1 * 10 = 10 (remaining K = 21, total = 3)
 *     Day 3 (price 19): buy 1 stock for 19 (remaining K = 2, total = 4)
 *   Max stocks = 4.
 * 
 * Constraints:
 * 1 <= N <= 10^5
 * 1 <= price[i] <= 10^4
 * 1 <= K <= 10^9
 * Must run in O(N log N) time and O(N) space.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Price-Prioritized Budget Maximization:
 *    - In Fractional Knapsack (Problem 5), we maximized value within weight W.
 *    - Here, every stock unit counts equally (+1 stock), but costs `price[i]`.
 *    - Therefore, the greedy choice is strictly to buy stocks with the CHEAPEST
 *      unit price first, exhausting their quota before moving to more expensive days.
 * 2. Day-Dependent Quotas:
 *    - The maximum quantity purchasable on day i is fixed to `i`.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Greedy by Unit Price:
 *   - Step 1: Pair each day's price with its available stock quota:
 *       `days[i] = {price[i], i + 1}` (1-indexed day).
 *   - Step 2: Sort days in ascending order of `price`.
 *   - Step 3: Iterate through sorted days:
 *       - At price P and quota Q:
 *           `canAfford = K / P;`
 *           `take = min((long long)Q, canAfford);`
 *           `totalBought += take;`
 *           `K -= take * P;`
 *       - If `K < P`, terminate immediately (budget cannot afford even 1 stock at
 *         current or any subsequent higher price).
 *   - Return `totalBought`.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    /**
     * Calculates the maximum number of stocks that can be bought within budget K.
     * @param n Number of days.
     * @param k Total budget money.
     * @param price Array of prices per day.
     * @return Maximum stocks purchased.
     */
    int buyMaximumProducts(int n, int k, int price[]) {
        // Step 1: Pair price with max allowable quantity (day index i + 1)
        vector<pair<int, int>> stockOffer(n);
        for (int i = 0; i < n; ++i) {
            stockOffer[i] = {price[i], i + 1};
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // To maximize total quantity under budget constraint K, we must greedily
        // exhaust stocks from the lowest unit price to the highest unit price.
        sort(stockOffer.begin(), stockOffer.end());

        int totalStocks = 0;
        long long remainingBudget = k;

        for (int i = 0; i < n; ++i) {
            long long unitPrice = stockOffer[i].first;
            long long maxQuantity = stockOffer[i].second;

            // Compute how many stocks we can afford from this day's quota
            long long affordableQuantity = remainingBudget / unitPrice;
            long long take = min(maxQuantity, affordableQuantity);

            totalStocks += take;
            remainingBudget -= (take * unitPrice);

            // Early exit if budget is too small to buy even 1 stock
            if (remainingBudget < unitPrice) {
                break;
            }
        }

        return totalStocks;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case: price[] = {10, 7, 19}, K = 45 -> Expected: 4
    int price[] = {10, 7, 19};
    int n = sizeof(price) / sizeof(price[0]);
    int k = 45;

    cout << "Max Stocks Bought = " << solver.buyMaximumProducts(n, k, price) 
         << " (Expected: 4)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Sorting N pairs by price: O(N log N).
 *   - Linear greedy consumption loop: O(N).
 *   - Total Time: O(N log N).
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(N) to store price-quantity pairs.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Unit price minimization guarantees the maximum count of purchased items.
 * 2. Multiply and subtract using `long long` to prevent integer overflow.
 */
