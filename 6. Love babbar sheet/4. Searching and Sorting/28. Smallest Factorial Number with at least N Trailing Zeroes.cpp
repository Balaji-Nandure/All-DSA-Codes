/**
 * ============================================================================
 * Problem: Smallest Factorial Number with at least N Trailing Zeroes
 * Category: Searching and Sorting / Number Theory
 * 
 * Problem Statement:
 * Given a number N. The task is to find the smallest number whose factorial
 * contains at least N trailing zeroes.
 * 
 * Example 1:
 * Input: N = 1
 * Output: 5
 * Explanation: 5! = 120 which has 1 trailing zero.
 * 
 * Example 2:
 * Input: N = 6
 * Output: 25
 * Explanation: 25! has 6 trailing zeroes (5, 10, 15, 20 contribute one 5 each,
 * and 25 contributes two 5s: 1 + 1 + 1 + 1 + 2 = 6).
 * 
 * Constraints:
 * 1 <= N <= 10^5 (often up to 10^9 in advanced variants)
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Number Theory (Legendre's Formula):
 *    - Trailing zeroes in X! are created by pairs of prime factors (2, 5).
 *    - In any factorial X!, powers of 2 vastly outnumber powers of 5.
 *    - Therefore, the number of trailing zeroes is strictly equal to the highest
 *      exponent of 5 dividing X!, calculated via Legendre's formula:
 *        Count(X) = floor(X/5) + floor(X/25) + floor(X/125) + ...
 * 2. Monotonic Function:
 *    - As X grows, Count(X) never decreases.
 *    - This monotonicity enables Binary Search over the integer range [0, 5 * N].
 *    - Note that some counts of trailing zeroes can NEVER appear (e.g., 5 zeroes:
 *      24! has 4 zeroes, 25! jumps to 6 zeroes). The problem specifically asks for
 *      the smallest number with AT LEAST N trailing zeroes.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * 1. Range Bounds:
 *    - Since every multiple of 5 contributes at least one 5, 5 * N is guaranteed
 *      to have at least N trailing zeroes.
 *    - Lower bound: 0.
 *    - Upper bound: 5 * N.
 * 2. Binary Search:
 *    - Set low = 1, high = 5 * N.
 *    - Mid is candidate number X.
 *    - Compute trailing zeroes of mid! using Legendre's Formula in O(log5(mid)).
 *    - If count >= N: mid satisfies condition. Record mid and search left (high = mid - 1).
 *    - If count < N: insufficient zeroes, search right (low = mid + 1).
 * ============================================================================
 */

#include <iostream>

using namespace std;

class Solution {
private:
    /**
     * Helper to compute the number of trailing zeroes in x! using Legendre's Formula:
     * Count = floor(x / 5) + floor(x / 25) + floor(x / 125) + ...
     * Time Complexity: O(log5(x))
     */
    long long countTrailingZeroes(long long x) {
        long long count = 0;
        long long p = 5;
        while (x / p > 0) {
            count += (x / p);
            // Protect against potential overflow if p * 5 exceeds standard range
            if (p > x / 5) break;
            p *= 5;
        }
        return count;
    }

public:
    /**
     * Finds the smallest number whose factorial has at least N trailing zeroes.
     * @param n Required minimum number of trailing zeroes.
     * @return Smallest integer whose factorial has >= n trailing zeroes.
     */
    long long findNum(long long n) {
        if (n == 0) return 0;

        long long low = 1;
        long long high = 5 * n; // Upper bound: 5 * n always contains >= n factors of 5
        long long ans = high;

        while (low <= high) {
            long long mid = low + (high - low) / 2;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Monotonic predicate: countTrailingZeroes(mid) >= n
            // Since we seek the SMALLEST number, whenever valid we store mid
            // and contract the right boundary to search for an even smaller candidate.
            if (countTrailingZeroes(mid) >= n) {
                ans = mid;
                high = mid - 1; // Try smaller values
            } else {
                low = mid + 1;  // Not enough trailing zeroes, increase candidate
            }
        }

        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case 1: n = 1 -> 5! = 120 (1 zero)
    cout << "Test 1 (n = 1): Smallest number = " << solver.findNum(1) << " (Expected: 5)\n";

    // Test Case 2: n = 6 -> 25! has 6 zeroes (24! has 4, 25! has 6)
    cout << "Test 2 (n = 6): Smallest number = " << solver.findNum(6) << " (Expected: 25)\n";

    // Test Case 3: n = 5 -> Smallest number with AT LEAST 5 zeroes is also 25
    cout << "Test 3 (n = 5): Smallest number = " << solver.findNum(5) << " (Expected: 25)\n";

    // Test Case 4: n = 100
    cout << "Test 4 (n = 100): Smallest number = " << solver.findNum(100) << " (Expected: 405)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Search range: [1, 5 * N].
 *   - Number of binary search iterations: log2(5 * N).
 *   - In each iteration, Legendre's formula takes: log5(mid) ≈ log5(5 * N) steps.
 *   - Total Time: O(log(5 * N) * log5(5 * N)) ≈ O(log^2(N)).
 *   - For N = 10^9, iterations ≈ 33 * 13 ≈ 430 operations. Extremely fast (< 1 ms)!
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) auxiliary variables.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Counting trailing zeroes of X! only requires counting prime factor 5.
 * 2. Beware of gaps: Some trailing zero counts are impossible (like 5, 11, etc.),
 *    which is why the problem asks for "at least" N trailing zeroes.
 */
