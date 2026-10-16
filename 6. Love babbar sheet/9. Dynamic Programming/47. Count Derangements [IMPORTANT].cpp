#include <iostream>
#include <vector>

using namespace std;

/**
 * Problem: Count Derangements (Permutations with no fixed points)
 * 
 * A Derangement is a permutation of N elements such that no element appears 
 * in its original position (i.e. p[i] != i for all 1 <= i <= N).
 * Find the total number of derangements of a set of N elements modulo 10^9 + 7.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "14. Print all permutations", we generated all N! permutations.
 * - Here, we count the subset of permutations with ZERO fixed points: D_n = !n (subfactorial).
 * - While Friends Pairing was f(n) = f(n-1) + (n-1)*f(n-2),
 *   Derangements have the multiplier (n-1) applied to BOTH terms:
 *   D(n) = (n - 1) * (D(n - 1) + D(n - 2)).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Derivation of the Derangement Recurrence:
 *   Consider element 1:
 *   Element 1 CANNOT be placed at position 1.
 *   It can be placed at any of the remaining (n - 1) positions.
 *   Suppose element 1 is placed at position i (2 <= i <= n).
 *   
 *   Now look at element i:
 *   Case A: Element i is placed at position 1 (Element 1 and Element i SWAP).
 *     Both elements 1 and i are now settled in non-original positions.
 *     The remaining (n - 2) elements must be deranged among themselves: D(n - 2) ways.
 *   
 *   Case B: Element i is NOT placed at position 1.
 *     Element i has 1 forbidden position (position 1), and every other remaining element 
 *     has its own 1 forbidden position.
 *     This is structurally identical to deranging (n - 1) elements: D(n - 1) ways.
 *   
 *   Combining both cases for all (n - 1) choices of i:
 *     D(n) = (n - 1) * (D(n - 1) + D(n - 2))  (modulo 10^9 + 7)
 *   
 *   Base Cases:
 *     D(1) = 0 (1 element cannot be deranged).
 *     D(2) = 1 (swap [1, 2] -> [2, 1]).
 *   
 *   Space Optimization:
 *     Using two rolling variables, space is strictly O(1)!
 */

class Solution {
    const int MOD = 1e9 + 7;
public:
    long long int countDerangements(int n) {
        if (n <= 1) return 0;
        if (n == 2) return 1;

        long long prev2 = 0; // D(1) = 0
        long long prev1 = 1; // D(2) = 1
        long long curr = 0;

        for (int i = 3; i <= n; i++) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // D(i) = (i - 1) * (D(i - 1) + D(i - 2)) % MOD
            curr = ((1LL * (i - 1)) * (prev1 + prev2)) % MOD;

            // Rolling state update for O(1) space
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};

int main() {
    Solution sol;
    cout << "Derangements for N = 1: " << sol.countDerangements(1) << "\n"; // Expected: 0
    cout << "Derangements for N = 2: " << sol.countDerangements(2) << "\n"; // Expected: 1 ([2, 1])
    cout << "Derangements for N = 3: " << sol.countDerangements(3) << "\n"; // Expected: 2 ([2, 3, 1], [3, 1, 2])
    cout << "Derangements for N = 4: " << sol.countDerangements(4) << "\n"; // Expected: 9
    cout << "Derangements for N = 5: " << sol.countDerangements(5) << "\n"; // Expected: 44

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N) single loop from 3 up to N.
 * - Space Complexity: O(1) auxiliary space (using only rolling variables prev1 and prev2).
 */
