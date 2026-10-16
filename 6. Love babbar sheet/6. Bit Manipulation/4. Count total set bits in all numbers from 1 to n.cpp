/**
 * ============================================================================
 * Problem: Count Total Set Bits in All Numbers from 1 to N
 * Category: Bit Manipulation / Mathematics
 * 
 * Problem Statement:
 * Given a positive integer N. Count the total number of set bits in the binary
 * representations of all integers from 1 to N (inclusive).
 * 
 * Example 1:
 * Input: N = 4
 * Binary: 1 (001), 2 (010), 3 (011), 4 (100)
 * Output: 1 + 1 + 2 + 1 = 5
 * 
 * Example 2:
 * Input: N = 17
 * Output: 35
 * 
 * Constraints:
 * 1 <= N <= 10^9
 * Must run in O(log N) time and O(log N) space (naive O(N) will TLE).
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Range Summation vs Single Value Query:
 *    - In Problem 1, we queried set bits for a single number in O(1) time.
 *    - Iterating from 1 to N would require O(N) operations, which times out
 *      completely when N = 10^9.
 * 2. Power-of-2 Mathematical Symmetry:
 *    - Across all binary numbers from 0 to (2^x - 1), every bit column has
 *      an identical number of 0s and 1s.
 *    - Total set bits in [0, 2^x - 1] = x * 2^(x - 1).
 *    - This closed-form combinatorial property allows breaking N down into
 *      log2(N) recursive subproblems!
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Recursive Power-of-Two Decomposition O(log N) Time:
 *   - Base Case: If N <= 0, return 0.
 *   - Step 1: Find the largest power of 2 such that 2^x <= N:
 *       `x = floor(log2(N))`
 *   - Step 2: Split the range [0, N] into three components:
 *       Component A: Numbers from 0 to (2^x - 1):
 *         Contains x * 2^(x - 1) set bits.
 *       Component B: The MSB (x-th bit) for all numbers from 2^x to N:
 *         Every number from 2^x to N has its x-th bit set to 1.
 *         Total bits contributed: (N - 2^x + 1).
 *       Component C: The remaining lower bits for numbers from 2^x to N:
 *         Stripping the MSB leaves the numbers 0 to (N - 2^x).
 *         Recursive call: `countSetBits(N - 2^x)`.
 *   - Recurrence:
 *       `f(N) = (x * 2^(x - 1)) + (N - 2^x + 1) + f(N - 2^x)`
 *   - Total Time: O(log N) iterations. For N = 10^9, requires only ~30 steps!
 * ============================================================================
 */

#include <iostream>

using namespace std;

class Solution {
private:
    /**
     * Finds largest x such that 2^x <= n.
     */
    int findLargestPowerOf2(int n) {
        int x = 0;
        while ((1 << (x + 1)) <= n) {
            x++;
        }
        return x;
    }

public:
    /**
     * Computes the total number of set bits from 1 to N in O(log N) time.
     * @param n Upper limit integer.
     * @return Total count of set bits across all numbers [1...n].
     */
    int countSetBits(int n) {
        if (n <= 0) return 0;

        // Step 1: Find largest x such that 2^x <= n
        int x = findLargestPowerOf2(n);

        // Component 1: Bits in range [0, 2^x - 1] = x * 2^(x - 1)
        int bitsUpTo2PowX = x * (1 << (x - 1));

        // Component 2: MSB bits in range [2^x, n] = (n - 2^x + 1)
        int msbBitsFrom2PowXToN = n - (1 << x) + 1;

        // Component 3: Lower bits in range [2^x, n] (stripping MSB leaves [0, n - 2^x])
        int remaining = n - (1 << x);

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Exploiting binary symmetry: combining closed-form (x * 2^(x-1)) with MSBs
        // and recursing on the remainder reduces an O(N) brute force loop to O(log N).
        return bitsUpTo2PowX + msbBitsFrom2PowXToN + countSetBits(remaining);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case 1: N = 4 -> 5 set bits
    cout << "Test 1 (N = 4):  Total Set Bits = " << solver.countSetBits(4) 
         << " (Expected: 5)\n";

    // Test Case 2: N = 17 -> 35 set bits
    cout << "Test 2 (N = 17): Total Set Bits = " << solver.countSetBits(17) 
         << " (Expected: 35)\n";

    // Test Case 3: N = 1000
    cout << "Test 3 (N = 1000): Total Set Bits = " << solver.countSetBits(1000) 
         << " (Expected: 4938)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Each recursive step decreases n by at least 2^x.
 *   - The maximum depth of the recursion tree is log2(N).
 *   - At each step, computing x takes O(log N) or O(1) via __builtin_clz.
 *   - Total Time: O(log N).
 *   - For N = 10^9: at most ~30 recursive calls (executes in < 0.001 ms).
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(log N) call stack frames.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. The formula for total set bits from 0 to 2^x - 1 is: `x * 2^(x - 1)`.
 * 2. Any interval query [1, N] over bit positions can be decomposed around
 *    the most significant set bit of N.
 */
