#include <iostream>
#include <vector>

using namespace std;

/**
 * Problem: Coin Change Problem (Count Ways to Make Sum)
 * 
 * Given an integer array of coin denominations coins[N] and a target sum.
 * Find the total number of distinct combinations to make the change for sum.
 * Assume an infinite supply of each coin denomination.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Greedy: Minimum number of coins" (Category 7, problem 6), we used canonical greedy choice 
 *   because standard Indian currency is a matroid/canonical system. For arbitrary denominations, 
 *   greedy FAILS and DP is mandatory.
 * - In "Backtracking: Combinational Sum" (Category 8, problem 12), we PRINTED all combinations in exponential time.
 * - Here, we only need the COUNT of ways, so 1D Dynamic Programming solves it in polynomial O(N * Sum) time!
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - 1D Unbounded Knapsack (Combinations vs Permutations):
 *   Why Outer Loop on Coins and Inner Loop on Sum?
 *   - Outer Loop on Coins: Once we finish processing coin `c`, we NEVER use coin `c` again in subsequent outer steps.
 *     This enforces a canonical sorted order of chosen coins (e.g., [1, 2] is formed, but [2, 1] is never formed).
 *     Hence, this counts COMBINATIONS (subsets).
 *   - If outer loop were on sum and inner on coins, it would count PERMUTATIONS ([1, 2] and [2, 1] counted as 2).
 *   
 *   Recurrence Relation:
 *     dp[j] += dp[j - coin]  for all j from coin to sum.
 *     Base Case: dp[0] = 1 (1 way to make sum 0: choose no coins).
 */

class Solution {
public:
    long long count(vector<int>& coins, int N, int sum) {
        // dp[j] stores the number of distinct ways to make amount j
        vector<long long> dp(sum + 1, 0);

        // Base case: There is exactly 1 way to make sum 0 (pick empty set)
        dp[0] = 1;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Outer loop over coins guarantees we count COMBINATIONS (order of coins does not matter)
        for (int i = 0; i < N; i++) {
            int coin = coins[i];

            // Inner loop traverses forward from coin to sum (unbounded supply allows reuse)
            // *** CRUCIAL LINE: Forward traversal allows using the same coin multiple times ***
            for (int j = coin; j <= sum; j++) {
                dp[j] += dp[j - coin];
            }
        }

        return dp[sum];
    }
};

int main() {
    Solution sol;
    vector<int> coins1 = {1, 2, 3};
    int sum1 = 4;
    cout << "Ways to make sum " << sum1 << ": " << sol.count(coins1, coins1.size(), sum1) << "\n";
    // Combinations for 4: {1,1,1,1}, {1,1,2}, {2,2}, {1,3} -> 4 ways.

    vector<int> coins2 = {2, 5, 3, 6};
    int sum2 = 10;
    cout << "Ways to make sum " << sum2 << ": " << sol.count(coins2, coins2.size(), sum2) << "\n";
    // Combinations for 10: {2,2,2,2,2}, {2,2,3,3}, {2,2,6}, {2,3,5}, {5,5} -> 5 ways.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N * sum). Double loop iterating through each coin and each target sum.
 * - Space Complexity: O(sum) using a single 1D rolling DP table.
 */
