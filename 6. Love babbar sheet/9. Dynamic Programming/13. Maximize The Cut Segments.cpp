#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Problem: Maximize The Cut Segments
 * 
 * Given an integer N denoting the length of a line segment.
 * You need to cut this segment into the MAXIMUM possible number of pieces 
 * such that the length of each piece is strictly either x, y, or z.
 * If it is impossible to cut the segment into lengths of only x, y, and z, return 0.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Coin Change", we minimized coins or counted ways.
 * - Here, we want to MAXIMIZE the number of cuts (pieces) subject to the segment being 
 *   EXACTLY exhausted by choices from {x, y, z}.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - 1D Unbounded Knapsack (Max Count Variant):
 *   Let dp[i] be the maximum number of cuts possible for a rod of length i.
 *   
 *   Base Case:
 *     dp[0] = 0 (a rod of length 0 needs 0 cuts).
 *     dp[i] = -1 for i > 0 (initialized to -1 to denote currently unreachable lengths).
 *   
 *   Transitions for length i from 1 to N:
 *     For each candidate cut c in {x, y, z}:
 *       If i >= c and dp[i - c] != -1:
 *         dp[i] = max(dp[i], dp[i - c] + 1)
 *   
 *   Why initialize to -1 rather than 0?
 *     Lengths that cannot be formed by any combination of {x, y, z} must NOT contribute 
 *     false positive cuts to subsequent transitions!
 *     Checking `dp[i - c] != -1` strictly guarantees that only valid sub-lengths are built upon.
 */

class Solution {
public:
    int maximizeTheCuts(int n, int x, int y, int z) {
        vector<int> dp(n + 1, -1);

        // Base case: 0 length has 0 cuts
        dp[0] = 0;

        for (int i = 1; i <= n; i++) {
            // Option 1: Cut piece of length x
            if (i >= x && dp[i - x] != -1) {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                dp[i] = max(dp[i], dp[i - x] + 1);
            }

            // Option 2: Cut piece of length y
            if (i >= y && dp[i - y] != -1) {
                dp[i] = max(dp[i], dp[i - y] + 1);
            }

            // Option 3: Cut piece of length z
            if (i >= z && dp[i - z] != -1) {
                dp[i] = max(dp[i], dp[i - z] + 1);
            }
        }

        // If length n was never reachable, return 0
        return (dp[n] == -1) ? 0 : dp[n];
    }
};

int main() {
    Solution sol;
    cout << "Max cuts (N=4, x=2, y=1, z=1): " << sol.maximizeTheCuts(4, 2, 1, 1) << "\n"; // Expected: 4 (cuts of 1, 1, 1, 1)
    cout << "Max cuts (N=5, x=5, y=3, z=2): " << sol.maximizeTheCuts(5, 5, 3, 2) << "\n"; // Expected: 2 (cuts of 3, 2)
    cout << "Max cuts (N=7, x=5, y=5, z=5): " << sol.maximizeTheCuts(7, 5, 5, 5) << "\n"; // Expected: 0 (impossible)

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N) single loop evaluating at most 3 choices at each length.
 * - Space Complexity: O(N) auxiliary space for the 1D dp table.
 */
