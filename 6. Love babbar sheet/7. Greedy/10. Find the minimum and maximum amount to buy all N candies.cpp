/**
 * ============================================================================
 * Problem: Shop in Candy Store (Find Minimum and Maximum Amount to Buy All N Candies)
 * Category: Greedy
 * 
 * Problem Statement:
 * In a candy store, there are N different candies, where `candies[i]` represents
 * the price of the i-th candy.
 * The store has a special promotional offer:
 *   For every candy you buy at its market price, you can take at most K other
 *   candies from the store completely for FREE!
 * 
 * You want to acquire all N candies.
 * Find:
 *   1. The MINIMUM amount of money you must spend.
 *   2. The MAXIMUM amount of money you can spend.
 * 
 * Example:
 * Input:
 *   N = 4, K = 2
 *   candies[] = {3, 2, 1, 4}
 * Output:
 *   Minimum Amount = 3
 *   Maximum Amount = 7
 * Explanation:
 *   Sorted prices: {1, 2, 3, 4}
 *   For Minimum: Buy candy priced 1, get candies priced 4 and 3 for free.
 *                Now buy candy priced 2. Total cost = 1 + 2 = 3.
 *   For Maximum: Buy candy priced 4, get candies priced 1 and 2 for free.
 *                Now buy candy priced 3. Total cost = 4 + 3 = 7.
 * 
 * Constraints:
 * 1 <= N <= 10^5
 * 0 <= K <= N - 1
 * 1 <= candies[i] <= 10^4
 * Must run in O(N log N) time and O(1) auxiliary space.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Dual Symmetric Extremization (Min Cost vs Max Cost):
 *    - In most optimization problems, we seek only a single minimum or maximum.
 *    - Here, the promotional coupon (1 paid -> K free) is symmetric:
 *        * Minimum cost: Pay for the CHEAPEST, take the MOST EXPENSIVE for free.
 *        * Maximum cost: Pay for the MOST EXPENSIVE, take the CHEAPEST for free.
 * 2. Two-Pointer Window Consumption:
 *    - In each purchase transaction, (1 + K) items are removed from the store:
 *      1 from the active purchase pointer, and K from the opposing promotional pointer.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Greedy Dual-Pointer Convergent Consumption:
 *   - Step 1: Sort `candies[]` in ascending order.
 *   - Step 2: Minimum Cost Calculation:
 *       `buy = 0; free = N - 1; minCost = 0;`
 *       While `buy <= free`:
 *           `minCost += candies[buy++];`
 *           `free -= K;`
 *   - Step 3: Maximum Cost Calculation:
 *       `buy = N - 1; free = 0; maxCost = 0;`
 *       While `buy >= free`:
 *           `maxCost += candies[buy--];`
 *           `free += K;`
 *   - Return `{minCost, maxCost}`.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    /**
     * Calculates the minimum and maximum cost to acquire all N candies.
     * @param candies Array of candy prices.
     * @param N Total number of candies.
     * @param K Number of free candies per purchase.
     * @return Vector [minCost, maxCost].
     */
    vector<int> candyStore(int candies[], int N, int K) {
        // Step 1: Sort candy prices in ascending order
        sort(candies, candies + N);

        // Step 2: Calculate Minimum Cost
        int minCost = 0;
        int buyMin = 0;
        int freeMin = N - 1;

        while (buyMin <= freeMin) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Pay for the cheapest available candy at 'buyMin', and claim the K most
            // expensive candies at 'freeMin' for free to minimize total expenditure.
            minCost += candies[buyMin++];
            freeMin -= K;
        }

        // Step 3: Calculate Maximum Cost
        int maxCost = 0;
        int buyMax = N - 1;
        int freeMax = 0;

        while (buyMax >= freeMax) {
            // Invert the heuristic: Pay for the most expensive candy at 'buyMax',
            // and claim the K cheapest candies at 'freeMax' for free to maximize expenditure.
            maxCost += candies[buyMax--];
            freeMax += K;
        }

        return {minCost, maxCost};
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case: N = 4, K = 2, candies[] = {3, 2, 1, 4}
    int candies[] = {3, 2, 1, 4};
    int N = sizeof(candies) / sizeof(candies[0]);
    int K = 2;

    vector<int> ans = solver.candyStore(candies, N, K);
    cout << "Minimum Cost = " << ans[0] << " (Expected: 3)\n";
    cout << "Maximum Cost = " << ans[1] << " (Expected: 7)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Sorting candy array: O(N log N).
 *   - Two-pointer passes: O(N / (K + 1)) operations.
 *   - Total Time: O(N log N).
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) in-place without auxiliary arrays.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. For minimum cost, pair the cheapest purchases with the most expensive freebies.
 * 2. For maximum cost, pair the most expensive purchases with the cheapest freebies.
 */
