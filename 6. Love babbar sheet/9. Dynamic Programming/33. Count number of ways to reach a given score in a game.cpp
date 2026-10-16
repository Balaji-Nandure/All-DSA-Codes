#include <iostream>
#include <vector>

using namespace std;

/**
 * Problem: Count number of ways to reach a given score in a game
 * 
 * Consider a game where a player can score 3, 5, or 10 points in a single move.
 * Given a total score N, find the total number of distinct COMBINATIONS to reach score N.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - This is an instantiation of "1. Coin Change" with fixed denominations {3, 5, 10}.
 * - The crucial requirement is COMBINATIONS (order of moves does NOT matter, e.g. {3, 5} == {5, 3}).
 * - Therefore, we must process all moves of score 3 first, then all moves of score 5, 
 *   then all moves of score 10 in separate outer passes!
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - 1D Combinatoric DP (Three Sequential Passes):
 *   Initialize an array dp[N + 1] = 0 with dp[0] = 1 (1 way to reach score 0).
 *   
 *   Pass 1: Consider only moves with score 3:
 *     For i from 3 to N:
 *       dp[i] += dp[i - 3]
 *   
 *   Pass 2: Consider adding moves with score 5:
 *     For i from 5 to N:
 *       dp[i] += dp[i - 5]
 *   
 *   Pass 3: Consider adding moves with score 10:
 *     For i from 10 to N:
 *       dp[i] += dp[i - 10]
 *   
 *   Why three independent passes rather than a single loop over scores?
 *     Running three independent passes strictly enforces the canonical sorted order:
 *     all 3s come first, then all 5s, then all 10s. This prevents permutations from 
 *     being double-counted.
 */

class Solution {
public:
    long long count(long long n) {
        vector<long long> dp(n + 1, 0);
        dp[0] = 1;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Step 1: Incorporate all 3-point moves
        for (long long i = 3; i <= n; i++) {
            dp[i] += dp[i - 3];
        }

        // Step 2: Incorporate all 5-point moves
        for (long long i = 5; i <= n; i++) {
            dp[i] += dp[i - 5];
        }

        // Step 3: Incorporate all 10-point moves
        for (long long i = 10; i <= n; i++) {
            dp[i] += dp[i - 10];
        }

        return dp[n];
    }
};

int main() {
    Solution sol;
    long long n1 = 20;
    cout << "Ways to reach score " << n1 << ": " << sol.count(n1) << "\n";
    // Combinations for 20:
    // 1. {10, 10}
    // 2. {5, 5, 10}
    // 3. {5, 5, 5, 5}
    // 4. {3, 3, 3, 3, 3, 5}
    // Total = 4 ways. Expected: 4.

    long long n2 = 13;
    cout << "Ways to reach score " << n2 << ": " << sol.count(n2) << "\n";
    // Combinations for 13: {3, 5, 5} and {3, 10} -> 2 ways. Expected: 2.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N) three sequential linear scans.
 * - Space Complexity: O(N) for the 1D dp array.
 */
