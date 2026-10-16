#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

/**
 * Problem: Minimum cost to fill given weight in a bag
 * 
 * Given an array cost[] of size N, where cost[i] represents the cost of an (i + 1) kg packet.
 * If cost[i] == -1, the (i + 1) kg packet is unavailable.
 * You want to buy EXACTLY W kg of items.
 * Each available packet can be purchased an UNLIMITED number of times.
 * Find the minimum cost to achieve exact weight W. If impossible, return -1.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "2. 0-1 Knapsack", each item was picked at most once (backward loop) and value was MAXIMIZED.
 * - In "1. Coin Change", coins were unbounded and we COUNTED ways.
 * - Here, packets have UNBOUNDED supply, unavailable items (-1) must be ignored,
 *   and we want to MINIMIZE the total cost to reach the EXACT weight W.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - 1D Unbounded Knapsack (Minimization):
 *   Let dp[w] be the minimum cost to purchase exactly w kg of fruit.
 *   
 *   Base Case:
 *     dp[0] = 0 (0 kg costs 0).
 *     dp[w] = INT_MAX for w > 0 (initialized to infinity to denote currently unreachable weights).
 *   
 *   Transitions:
 *     For each packet i from 0 to N - 1:
 *       wt = i + 1, price = cost[i].
 *       If price == -1: continue (packet unavailable).
 *       
 *       Traverse w FORWARD from wt to W:
 *         If dp[w - wt] != INT_MAX:
 *           dp[w] = min(dp[w], dp[w - wt] + price)
 *   
 *   Why traverse FORWARD?
 *     Forward traversal allows reusing the current packet multiple times from newly computed 
 *     states in the same iteration (unbounded supply property).
 */

class Solution {
public:
    int minimumCost(int cost[], int N, int W) {
        vector<int> dp(W + 1, INT_MAX);

        // Base case
        dp[0] = 0;

        for (int i = 0; i < N; i++) {
            int wt = i + 1;
            int price = cost[i];

            // Skip unavailable packet sizes
            if (price == -1) continue;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Forward traversal enables unbounded multiple purchases of the same packet
            for (int w = wt; w <= W; w++) {
                if (dp[w - wt] != INT_MAX) {
                    // *** CRUCIAL LINE: Minimize cost to attain exact weight w ***
                    dp[w] = min(dp[w], dp[w - wt] + price);
                }
            }
        }

        return (dp[W] == INT_MAX) ? -1 : dp[W];
    }
};

int main() {
    Solution sol;
    int cost1[] = {20, 10, 4, 50, 100};
    int N1 = 5, W1 = 5;
    cout << "Min Cost 1: " << sol.minimumCost(cost1, N1, W1) << "\n";
    // Packets: wt 1=20, wt 2=10, wt 3=4, wt 4=50, wt 5=100.
    // Buy one wt 3 (cost 4) + one wt 2 (cost 10) = 14. Expected: 14.

    int cost2[] = {-1, -1, 4, 5, -1};
    int N2 = 5, W2 = 5;
    cout << "Min Cost 2: " << sol.minimumCost(cost2, N2, W2) << "\n";
    // Buy one wt 4 (cost 5) + wt 1 (-1 unavailable) -> impossible?
    // Wait: available: wt 3 (cost 4), wt 4 (cost 5). 
    // Can we form 5 using multiples of 3 and 4? 3+3=6, 4+4=8. Impossible! Expected: -1.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N * W). Nested loops iterating over all N packets and weight budget W.
 * - Space Complexity: O(W) auxiliary space using a single 1D DP table.
 */
