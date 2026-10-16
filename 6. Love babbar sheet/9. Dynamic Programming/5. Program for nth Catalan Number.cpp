#include <iostream>
#include <vector>

using namespace std;

/**
 * Problem: Program for nth Catalan Number
 * 
 * Given an integer N, calculate the N-th Catalan Number modulo 10^9 + 7.
 * The Catalan sequence: 1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, ...
 * 
 * APPLICATIONS OF CATALAN NUMBERS IN DSA:
 * 1. Count of structurally unique Binary Search Trees (BSTs) with N keys.
 * 2. Count of valid parenthesizations with N pairs of brackets.
 * 3. Count of mountain ranges with N upstrokes and N downstrokes (Dyck paths).
 * 4. Count of full binary trees with N + 1 leaves.
 * 5. Number of ways to triangulate a convex polygon with N + 2 vertices.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Unlike simple linear recurrences (Fibonacci: dp[i] = dp[i-1] + dp[i-2]),
 *   Catalan numbers follow a CONVOLUTION product recurrence:
 *   C_n = sum_{i=0}^{n-1} (C_i * C_{n - 1 - i}).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Dynamic Programming Convolution:
 *   Base Cases: C[0] = 1, C[1] = 1.
 *   For each n from 2 up to N:
 *     C[n] = sum_{i=0}^{n-1} (C[i] * C[n - 1 - i]) % MOD.
 *   
 *   Why this convolution holds:
 *   Consider constructing all unique BSTs with n nodes:
 *   Pick root as node (i + 1) where i nodes fall into the left subtree,
 *   and (n - 1 - i) nodes fall into the right subtree.
 *   By product rule, the number of trees with root (i + 1) is: C[i] * C[n - 1 - i].
 *   Summing over all possible roots i in [0 ... n-1] yields the universal Catalan recurrence.
 */

class Solution {
    const int MOD = 1e9 + 7;
public:
    // O(N^2) Standard Dynamic Programming Convolution
    int findCatalan(int n) {
        vector<long long> catalan(n + 1, 0);

        // Base cases
        catalan[0] = 1;
        catalan[1] = 1;

        for (int i = 2; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Convolution step: Left subtree combinations * Right subtree combinations
                long long term = (catalan[j] * catalan[i - 1 - j]) % MOD;
                catalan[i] = (catalan[i] + term) % MOD;
            }
        }

        return catalan[n];
    }
};

int main() {
    Solution sol;
    cout << "Catalan(0): " << sol.findCatalan(0) << "\n"; // Expected: 1
    cout << "Catalan(1): " << sol.findCatalan(1) << "\n"; // Expected: 1
    cout << "Catalan(2): " << sol.findCatalan(2) << "\n"; // Expected: 2
    cout << "Catalan(3): " << sol.findCatalan(3) << "\n"; // Expected: 5
    cout << "Catalan(4): " << sol.findCatalan(4) << "\n"; // Expected: 14
    cout << "Catalan(5): " << sol.findCatalan(5) << "\n"; // Expected: 42
    cout << "Catalan(6): " << sol.findCatalan(6) << "\n"; // Expected: 132

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N^2). Outer loop runs N times, inner loop runs i times: sum(i) = N*(N-1)/2.
 * - Space Complexity: O(N) auxiliary table to store Catalan numbers from 0 to N.
 */
