#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Problem: Unbounded Knapsack (Repetition of items allowed)
 * 
 * Given N items, each with a weight wt[i] and a value val[i].
 * A knapsack has maximum capacity W.
 * Find the maximum value that can be put in the knapsack, where 
 * each item can be selected an UNLIMITED number of times.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "2. 0-1 Knapsack", items could be selected at most once, which FORCED 
 *   the capacity loop to traverse BACKWARD (from W down to wt[i]).
 * - Here, each item can be used multiple times.
 * - Therefore, the capacity loop MUST traverse FORWARD (from wt[i] up to W).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - 1D Unbounded Knapsack DP:
 *   Let dp[w] be the maximum value achievable with weight capacity w.
 *   
 *   Base Case:
 *     dp[0] = 0 (0 capacity holds 0 value).
 *   
 *   Transitions for each item i:
 *     For w from wt[i] up to W:
 *       dp[w] = max(dp[w], val[i] + dp[w - wt[i]])
 *   
 *   Why FORWARD Traversal?
 *     When evaluating dp[w], it references `dp[w - wt[i]]`.
 *     Because we traversed forward, `dp[w - wt[i]]` has ALREADY been updated to include item i 
 *     (possibly multiple times).
 *     Adding another val[i] allows chaining multiple copies of item i into the knapsack!
 */

class Solution {
public:
    int knapSack(int N, int W, int val[], int wt[]) {
        vector<int> dp(W + 1, 0);

        for (int i = 0; i < N; i++) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Forward traversal from wt[i] to W enables unbounded reuse of item i
            for (int w = wt[i]; w <= W; w++) {
                // *** CRUCIAL LINE: Item i can build upon previous usages of itself in the same iteration ***
                dp[w] = max(dp[w], val[i] + dp[w - wt[i]]);
            }
        }

        return dp[W];
    }
};

int main() {
    Solution sol;
    int N1 = 2, W1 = 3;
    int val1[] = {1, 1};
    int wt1[]  = {2, 1};
    cout << "Max value 1: " << sol.knapSack(N1, W1, val1, wt1) << "\n";
    // Can take 3 items of wt 1 (cost 3*1 = 3) -> value 3. Expected: 3.

    int N2 = 4, W2 = 8;
    int val2[] = {10, 40, 50, 70};
    int wt2[]  = {1, 3, 4, 5};
    cout << "Max value 2: " << sol.knapSack(N2, W2, val2, wt2) << "\n";
    // Item 1 (val 40, wt 3) and Item 3 (val 70, wt 5) gives wt 8, value 110. Expected: 110.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N * W). Double loop over all N items and capacity W.
 * - Space Complexity: O(W) auxiliary space using a single 1D rolling array.
 */
