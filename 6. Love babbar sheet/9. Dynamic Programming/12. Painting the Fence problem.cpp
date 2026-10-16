#include <iostream>
#include <vector>

using namespace std;

/**
 * Problem: Painting the Fence problem
 * 
 * Given a fence with N posts and K colors, find out the total number of ways of 
 * painting the fence such that AT MOST TWO consecutive posts have the same color.
 * Return the result modulo 10^9 + 7.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - This is a state-constrained coloring problem where the constraint is on run-length 
 *   (maximum run-length of identical color is 2).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Linear Dynamic Programming with State Decomposition:
 *   For post `i`, let:
 *   - same(i): Number of ways where post i has the SAME color as post (i - 1).
 *   - diff(i): Number of ways where post i has a DIFFERENT color from post (i - 1).
 *   - total(i) = same(i) + diff(i).
 *   
 *   Analysis:
 *   1. If post i has the SAME color as post (i - 1):
 *      By the problem constraint (at most 2 consecutive), post (i - 1) and post (i - 2) 
 *      MUST have had DIFFERENT colors!
 *      Therefore: same(i) = diff(i - 1).
 *   
 *   2. If post i has a DIFFERENT color from post (i - 1):
 *      Post i can be painted in any of the remaining (K - 1) colors.
 *      Post (i - 1) could have had either the same or different color as (i - 2).
 *      Therefore: diff(i) = total(i - 1) * (K - 1).
 *   
 *   3. Combining:
 *      total(i) = same(i) + diff(i)
 *               = diff(i - 1) + total(i - 1) * (K - 1)
 *               = total(i - 2) * (K - 1) + total(i - 1) * (K - 1)
 *               = (K - 1) * (total(i - 1) + total(i - 2))
 *   
 *   Base Cases:
 *     total(1) = K
 *     total(2) = K + K * (K - 1) = K^2
 *   
 *   Space Optimization:
 *     Only the previous two totals are needed, giving an O(1) space algorithm!
 */

class Solution {
    const int MOD = 1e9 + 7;
public:
    long long countWays(int n, int k) {
        if (n == 0) return 0;
        if (n == 1) return k;
        if (k == 1) return (n <= 2) ? 1 : 0; // If only 1 color, > 2 posts is impossible

        long long prev2 = k;                            // total(1)
        long long prev1 = (1LL * k * k) % MOD;          // total(2)

        for (int i = 3; i <= n; i++) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // total(i) = (k - 1) * (total(i - 1) + total(i - 2)) % MOD
            long long curr = ((k - 1) * (prev1 + prev2)) % MOD;

            // Rolling state update
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};

int main() {
    Solution sol;
    cout << "Ways for N = 3, K = 2: " << sol.countWays(3, 2) << "\n"; // Expected: 6
    cout << "Ways for N = 2, K = 4: " << sol.countWays(2, 4) << "\n"; // Expected: 16
    cout << "Ways for N = 4, K = 3: " << sol.countWays(4, 3) << "\n"; // Expected: 66

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N) single loop from 3 up to N.
 * - Space Complexity: O(1) auxiliary space (using only prev1 and prev2).
 */
