/**
 * ============================================================================
 * Problem: Divide Two Integers Without Using *, / and % Operators (LeetCode 29)
 * Category: Bit Manipulation
 * 
 * Problem Statement:
 * Given two integers `dividend` and `divisor`, divide the two integers without 
 * using multiplication (*), division (/), or modulo (%) operators.
 * 
 * Return the integer quotient after truncating toward zero.
 * Assume the environment operates on 32-bit signed integers: [-2^31, 2^31 - 1].
 * If the quotient exceeds 2^31 - 1, return 2^31 - 1 (INT_MAX).
 * If the quotient is less than -2^31, return -2^31 (INT_MIN).
 * 
 * Example 1:
 * Input:  dividend = 10, divisor = 3
 * Output: 3
 * 
 * Example 2:
 * Input:  dividend = 7, divisor = -3
 * Output: -2
 * 
 * Constraints:
 * -2^31 <= dividend, divisor <= 2^31 - 1
 * divisor != 0
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Simulating Division at the Hardware ALU Level:
 *    - Division in microprocessors is physically implemented via shift-and-subtract
 *      registers (restoring or non-restoring division).
 *    - Naive repeated subtraction `dividend -= divisor` takes O(dividend) time:
 *      for dividend = 2 * 10^9 and divisor = 1, it requires 2 billion operations (TLE).
 * 2. Exponential Shifting (Powers of 2 Acceleration):
 *    - Any integer quotient Q can be uniquely written in binary:
 *        Q = c_0 * 2^0 + c_1 * 2^1 + ... + c_31 * 2^31
 *    - By finding the largest i such that `(divisor << i) <= dividend`, we can
 *      subtract 2^i copies of the divisor in a single operation!
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Binary Long Division (Bit Shifting):
 *   - Step 1: Handle overflow edge case:
 *       `dividend == INT_MIN && divisor == -1` -> results in +2^31 which overflows INT_MAX.
 *   - Step 2: Determine sign of result using XOR:
 *       `isNegative = (dividend < 0) ^ (divisor < 0);`
 *   - Step 3: Work with 64-bit absolute values:
 *       `a = abs((long long)dividend);`
 *       `b = abs((long long)divisor);`
 *   - Step 4: Iterate from i = 31 down to 0:
 *       - If `(b << i) <= a`:
 *           `a -= (b << i);`
 *           `quotient += (1LL << i);`
 *   - Step 5: Apply sign and clamp to [INT_MIN, INT_MAX].
 * ============================================================================
 */

#include <iostream>
#include <climits>
#include <cmath>

using namespace std;

class Solution {
public:
    /**
     * Divides dividend by divisor without *, /, or % using bit shifts.
     * @param dividend Numerator integer.
     * @param divisor Denominator integer.
     * @return Truncated integer quotient.
     */
    int divide(int dividend, int divisor) {
        // Overflow corner case: -2^31 / -1 = +2^31 (overflows 32-bit signed int)
        if (dividend == INT_MIN && divisor == -1) {
            return INT_MAX;
        }

        // Determine sign of final quotient
        bool isNegative = (dividend < 0) ^ (divisor < 0);

        // Convert to 64-bit positive values to prevent absolute value overflow on INT_MIN
        long long a = abs((long long)dividend);
        long long b = abs((long long)divisor);

        long long quotient = 0;

        // Iterate from most significant bit (31) down to 0
        for (int i = 31; i >= 0; --i) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Binary Long Division: If (b * 2^i) fits inside remaining 'a',
            // subtract it and add 2^i to quotient, replacing linear subtraction with exponential steps.
            if ((b << i) <= a) {
                a -= (b << i);
                quotient += (1LL << i);
            }
        }

        long long result = isNegative ? -quotient : quotient;

        // Clamp within 32-bit signed integer limits
        if (result > INT_MAX) return INT_MAX;
        if (result < INT_MIN) return INT_MIN;

        return (int)result;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case 1: 10 / 3 = 3
    cout << "Test 1: 10 / 3 = " << solver.divide(10, 3) << " (Expected: 3)\n";

    // Test Case 2: 7 / -3 = -2
    cout << "Test 2: 7 / -3 = " << solver.divide(7, -3) << " (Expected: -2)\n";

    // Test Case 3: INT_MIN / -1 -> Clamped to INT_MAX
    cout << "Test 3: INT_MIN / -1 = " << solver.divide(INT_MIN, -1) 
         << " (Expected: " << INT_MAX << ")\n";

    // Test Case 4: 43 / 8 = 5
    cout << "Test 4: 43 / 8 = " << solver.divide(43, 8) << " (Expected: 5)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - The loop runs exactly 32 times for 32-bit integer dividend.
 *   - Total Time: O(32) = O(1) constant time.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) strictly.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Shifting by `(b << i)` simulates binary long division in hardware ALU.
 * 2. Always handle `INT_MIN` using `long long` cast before applying `abs()`.
 */
