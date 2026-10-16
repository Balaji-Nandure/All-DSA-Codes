#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Problem: 0-1 Knapsack Problem
 * 
 * Given N items, each with a weight wt[i] and a value val[i].
 * A knapsack has maximum weight capacity W.
 * Determine the maximum value subset of items that fits within capacity W.
 * Each item can be picked AT MOST ONCE (0-1 decision).
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Fractional Knapsack" (Category 7, problem 5), items could be split, so Greedy by value/weight was optimal.
 * - In "1. Coin Change", items (coins) had UNBOUNDED supply, so inner loop ran FORWARD.
 * - Here, each item can be chosen at most once. To achieve O(W) space without a 2D table, 
 *   the capacity loop MUST traverse BACKWARD.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Space-Optimized 1D 0-1 Knapsack DP:
 *   Let dp[w] be the maximum value achievable with weight capacity w.
 *   
 *   Recurrence:
 *     dp[w] = max(dp[w], val[i] + dp[w - wt[i]])
 *   
 *   Why BACKWARD Traversal (from W down to wt[i])?
 *   - When computing dp[w], it references `dp[w - wt[i]]`.
 *   - If we traverse forward, `dp[w - wt[i]]` would have already been updated by item i, 
 *     meaning item i could be included again (unbounded reuse).
 *   - By traversing backward from W down to wt[i], `dp[w - wt[i]]` still holds the value from the 
 *     PREVIOUS item (i - 1), strictly enforcing the 0-1 constraint with only O(W) memory!
 */

class Solution {
public:
    int knapSack(int W, vector<int>& wt, vector<int>& val) {
        int n = wt.size();
        vector<int> dp(W + 1, 0);

        for (int i = 0; i < n; i++) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Backward traversal ensures each item is included at most once (0-1 property)
            for (int w = W; w >= wt[i]; w--) {
                // *** CRUCIAL LINE: State transition taking previous item's value from left ***
                dp[w] = max(dp[w], val[i] + dp[w - wt[i]]);
            }
        }

        return dp[W];
    }
};

int main() {
    Solution sol;
    vector<int> val = {60, 100, 120};
    vector<int> wt  = {10, 20, 30};
    int W = 50;

    cout << "Max Knapsack Value: " << sol.knapSack(W, wt, val) << "\n";
    // Capacity 50: items 20 and 30 give total value 100 + 120 = 220.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N * W). We examine each of the N items against capacity W.
 * - Space Complexity: O(W) auxiliary space using a 1D backward-traversing array.
 */
