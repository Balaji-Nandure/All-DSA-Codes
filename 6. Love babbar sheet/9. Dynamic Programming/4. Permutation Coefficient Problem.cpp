#include <iostream>
#include <vector>

using namespace std;

/**
 * Problem: Permutation Coefficient Problem
 * 
 * Given two integers n and k, compute the Permutation Coefficient P(n, k) % (10^9 + 7).
 * P(n, k) represents the number of ordered arrangements of k elements chosen from a set of n elements:
 * P(n, k) = n! / (n - k)! = n * (n - 1) * (n - 2) * ... * (n - k + 1).
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "3. Binomial Coefficient (nCr)", order did not matter (combinations), so we divided by r!.
 * - In Permutation Coefficient P(n, k), order MATTERS.
 * - While nCr satisfies C(n, r) = C(n-1, r) + C(n-1, r-1),
 *   P(n, k) satisfies: P(n, k) = P(n - 1, k) + k * P(n - 1, k - 1).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Method 1: Direct Single-Pass Multiplication in O(K) Time & O(1) Space:
 *   Notice:
 *     P(n, k) = n * (n - 1) * (n - 2) * ... * (n - k + 1).
 *   This is simply the product of k terms starting from n down to (n - k + 1).
 *   Unlike division which is difficult under modular arithmetic, multiplication is directly 
 *   closed under modulo!
 *   Therefore, we can simply maintain `ans = (ans * (n - i)) % MOD` for i from 0 to k - 1.
 * 
 * - Method 2: Dynamic Programming Recurrence:
 *   P(n, k) = P(n - 1, k) + k * P(n - 1, k - 1).
 *   Both methods are provided below for full algorithmic completeness.
 */

class Solution {
    const int MOD = 1e9 + 7;
public:
    // Optimal O(K) Time and O(1) Space Direct Evaluation
    long long permutationCoeff(int n, int k) {
        if (k > n) return 0;
        if (k == 0) return 1;

        long long result = 1;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Multiply k consecutive integers: n * (n - 1) * ... * (n - k + 1) % MOD
        for (int i = 0; i < k; i++) {
            result = (result * (n - i)) % MOD;
        }

        return result;
    }

    // DP Recurrence Approach (O(N * K) time, O(K) space)
    long long permutationCoeffDP(int n, int k) {
        if (k > n) return 0;

        vector<long long> dp(k + 1, 0);
        dp[0] = 1;

        for (int i = 1; i <= n; i++) {
            // Traverse backward to update in-place in 1D space
            for (int j = min(i, k); j > 0; j--) {
                // *** CRUCIAL LINE: Recurrence P(n, k) = P(n - 1, k) + k * P(n - 1, k - 1) ***
                dp[j] = (dp[j] + 1LL * j * dp[j - 1]) % MOD;
            }
        }

        return dp[k];
    }
};

int main() {
    Solution sol;
    cout << "P(10, 2):    " << sol.permutationCoeff(10, 2) << "\n";     // 10 * 9 = 90
    cout << "P(10, 3):    " << sol.permutationCoeff(10, 3) << "\n";     // 10 * 9 * 8 = 720
    cout << "P(10, 2) DP: " << sol.permutationCoeffDP(10, 2) << "\n";   // 90
    cout << "P(10, 3) DP: " << sol.permutationCoeffDP(10, 3) << "\n";   // 720

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Direct Method: Time Complexity O(K), Space Complexity O(1).
 * - DP Recurrence Method: Time Complexity O(N * K), Space Complexity O(K).
 */
