/**
 * ============================================================================
 * Problem: Calculate Square of a Number Without Using *, / and pow()
 * Category: Bit Manipulation
 * 
 * Problem Statement:
 * Given an integer N, calculate the square of N (i.e. N^2) without using the 
 * multiplication operator (*), division operator (/), or `pow()` library function.
 * 
 * Example 1:
 * Input: N = 5
 * Output: 25
 * 
 * Example 2:
 * Input: N = -7
 * Output: 49
 * 
 * Example 3:
 * Input: N = 10
 * Output: 100
 * 
 * Constraints:
 * -10^6 <= N <= 10^6
 * Must run in O(log N) time and O(1) auxiliary space (no O(N) repeated additions).
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Multiplication Simulation via Binary Expansion:
 *    - In Problem 8, we simulated division via shift-and-subtract.
 *    - Here, we simulate squaring via shift-and-add:
 *        Any number N can be expanded as a sum of powers of 2:
 *          N = sum_{i} (b_i * 2^i), where b_i in {0, 1}
 *        Therefore:
 *          N^2 = N * N = sum_{i, where b_i = 1} (N << i)
 * 2. Avoiding O(N) Naive Addition:
 *    - Adding N to itself N times takes O(N) time (e.g. 10^6 additions).
 *    - Bitwise expansion evaluates N^2 in at most 32 operations (O(log N)).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Method 1: Bitwise Expansion (The Gold Standard O(log N) Time, O(1) Space)
 *   - Note: (-N)^2 = N^2, so `n = abs(n)`.
 *   - Initialize: `result = 0`, `temp = n`, `power = 0`.
 *   - While `temp > 0`:
 *       - If `temp & 1`:
 *           `result += (n << power);`
 *       - `power++;`
 *       - `temp >>= 1;`
 *   - Return `result`.
 * 
 * Method 2: Recursive Identity
 *   - If N is even: (2k)^2 = 4k^2 = (k^2 << 2)
 *   - If N is odd:  (2k + 1)^2 = 4k^2 + 4k + 1 = (k^2 << 2) + (k << 2) + 1
 * ============================================================================
 */

#include <iostream>
#include <cmath>

using namespace std;

class Solution {
public:
    /**
     * Method 1: Bitwise Expansion (Shift-and-Add) in O(log N) Time, O(1) Space.
     * @param n Input integer.
     * @return n * n.
     */
    long long calculateSquareBitwise(long long n) {
        if (n == 0) return 0;

        // Square of negative number is positive
        n = abs(n);

        long long result = 0;
        long long temp = n;
        int shift = 0;

        while (temp > 0) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Binary Expansion: If the shift-th bit of N is 1, add (N << shift) to result.
            // This computes N * 2^shift in a single ALU shift operation.
            if (temp & 1) {
                result += (n << shift);
            }
            shift++;
            temp >>= 1;
        }

        return result;
    }

    /**
     * Method 2: Recursive Divide and Conquer in O(log N) Time
     */
    long long calculateSquareRecursive(long long n) {
        if (n == 0) return 0;
        n = abs(n);

        // Base case
        if (n == 1) return 1;

        long long k = n >> 1; // k = floor(n / 2)

        // If n is even: (2k)^2 = 4 * k^2 = (k^2 << 2)
        if ((n & 1) == 0) {
            return calculateSquareRecursive(k) << 2;
        }
        // If n is odd: (2k + 1)^2 = 4k^2 + 4k + 1 = (k^2 << 2) + (k << 2) + 1
        else {
            return (calculateSquareRecursive(k) << 2) + (k << 2) + 1;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case 1: N = 5 -> 25
    cout << "Test 1: 5^2  = " << solver.calculateSquareBitwise(5) << " (Expected: 25)\n";

    // Test Case 2: N = -7 -> 49
    cout << "Test 2: -7^2 = " << solver.calculateSquareBitwise(-7) << " (Expected: 49)\n";

    // Test Case 3: N = 10 -> 100
    // 10 in binary is 1010 (2^3 + 2^1) -> (10 << 3) + (10 << 1) = 80 + 20 = 100!
    cout << "Test 3: 10^2 = " << solver.calculateSquareBitwise(10) << " (Expected: 100)\n";

    // Test Case 4: N = 12 (Recursive method)
    cout << "Test 4: 12^2 = " << solver.calculateSquareRecursive(12) << " (Expected: 144)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - The while loop runs for the number of bits in N (at most log2(N) <= 32 iterations).
 *   - Total Time: O(log N).
 *   - For N = 10^6, ~20 iterations (sub-microsecond execution).
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) strictly.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Bitwise shifting replaces multiplication by powers of 2: `(x << k) == x * 2^k`.
 * 2. Any polynomial or scalar multiplication can be rewritten as shift-and-add over binary digits.
 */
