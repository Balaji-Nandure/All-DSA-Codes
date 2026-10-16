#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Problem: Binomial Coefficient Problem (nCr)
 * 
 * Given two integers n and r, calculate the value of nCr % (10^9 + 7).
 * C(n, r) represents the number of ways to choose r items from a set of n distinct items.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Direct factorial calculation n! / (r! * (n - r)!) overflows primitive 64-bit integers 
 *   even for moderate n (e.g. 21! > 2^64).
 * - Under modulo arithmetic, division is NOT closed (we cannot simply do (n! % MOD) / (r! % MOD)).
 * - DP leverages Pascal's Triangle using solely modular ADDITIONS.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Pascal's Identity DP (Additive State Transition):
 *     C(n, r) = C(n - 1, r - 1) + C(n - 1, r)
 *   Base cases:
 *     C(n, 0) = 1 for all n.
 *     C(n, n) = 1.
 *     C(n, r) = 0 if r > n.
 * 
 * - 1D Space Optimization:
 *   Symmetry: C(n, r) == C(n, n - r). If r > n - r, set r = n - r.
 *   Maintain an array dp[0 ... r] initialized with dp[0] = 1.
 *   For each row i from 1 to n:
 *     Traverse j BACKWARD from min(i, r) down to 1:
 *     dp[j] = (dp[j] + dp[j - 1]) % MOD
 *   Traversing backward prevents overwriting dp[j - 1] before computing dp[j]!
 */

class Solution {
    const int MOD = 1e9 + 7;
public:
    int nCr(int n, int r) {
        if (r > n) return 0;
        if (r == 0 || r == n) return 1;

        // Symmetry optimization: C(n, r) == C(n, n - r)
        if (r > n - r) {
            r = n - r;
        }

        // dp[j] stores C(i, j)
        vector<int> dp(r + 1, 0);
        dp[0] = 1;

        for (int i = 1; i <= n; i++) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Backward traversal ensures dp[j - 1] is from row (i - 1), implementing Pascal's identity in 1D space
            for (int j = min(i, r); j > 0; j--) {
                // *** CRUCIAL LINE: Pascal's Recurrence C(i, j) = C(i - 1, j) + C(i - 1, j - 1) ***
                dp[j] = (dp[j] + dp[j - 1]) % MOD;
            }
        }

        return dp[r];
    }
};

int main() {
    Solution sol;
    cout << "C(3, 2):   " << sol.nCr(3, 2) << "\n";   // Expected: 3
    cout << "C(4, 2):   " << sol.nCr(4, 2) << "\n";   // Expected: 6
    cout << "C(5, 3):   " << sol.nCr(5, 3) << "\n";   // Expected: 10
    cout << "C(10, 4):  " << sol.nCr(10, 4) << "\n";  // Expected: 210

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N * R). Double loop computing each cell of Pascal's triangle.
 * - Space Complexity: O(R) auxiliary space with 1D backward array.
 */
