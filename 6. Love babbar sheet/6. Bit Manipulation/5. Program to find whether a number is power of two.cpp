/**
 * ============================================================================
 * Problem: Power of 2 (Check If a Number is a Power of Two)
 * Category: Bit Manipulation
 * 
 * Problem Statement:
 * Given a non-negative integer N. The task is to check if N is a power of 2.
 * 
 * Example 1:
 * Input: N = 1
 * Output: true (2^0 = 1)
 * 
 * Example 2:
 * Input: N = 16
 * Output: true (2^4 = 16)
 * 
 * Example 3:
 * Input: N = 6
 * Output: false
 * 
 * Constraints:
 * 0 <= N <= 10^18
 * Must run in O(1) time and O(1) auxiliary space.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Single Bit Cardinality:
 *    - In Problem 1, we counted all set bits in O(K).
 *    - Here, a number is a power of 2 if and only if its popcount is EXACTLY 1.
 * 2. Arithmetic Loops vs Instant Algebraic Identity:
 *    - A naive loop repeatedly divides by 2: `while (n % 2 == 0) n /= 2; return n == 1;`
 *      which takes O(log N) iterations.
 *    - The bitwise expression `(n & (n - 1)) == 0` evaluates the condition in a 
 *      single CPU cycle (O(1) time).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Brian Kernighan's Property O(1) Time, O(1) Space:
 *   - Case 1: N <= 0. Powers of 2 (2^k for integer k >= 0) are strictly positive.
 *     Hence, non-positive numbers (0, negatives) are never powers of 2.
 *   - Case 2: N > 0.
 *     If N is a power of 2, its binary representation is a single leading '1'
 *     followed exclusively by '0's (e.g. 16 = 10000).
 *     Subtracting 1 flips the leading '1' to '0' and all subsequent '0's to '1's
 *     (e.g. 15 = 01111).
 *     Therefore, `N & (N - 1) == 0`.
 *   - If N is not a power of 2, it contains multiple set bits, so `N & (N - 1) > 0`.
 *   - Invariant: `return (n > 0) && ((n & (n - 1)) == 0);`.
 * ============================================================================
 */

#include <iostream>

using namespace std;

class Solution {
public:
    /**
     * Checks whether integer N is a power of two in O(1) time.
     * @param n Input integer (long long to handle large constraints).
     * @return true if N is a power of 2, false otherwise.
     */
    bool isPowerOfTwo(long long n) {
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // A power of 2 has exactly one set bit. Clearing its lowest set bit via 'n & (n - 1)'
        // must result in exactly 0, provided n > 0.
        return (n > 0) && ((n & (n - 1)) == 0);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case 1: N = 1 (2^0) -> true
    cout << "Test 1 (N = 1):  " << (solver.isPowerOfTwo(1) ? "YES" : "NO") 
         << " (Expected: YES)\n";

    // Test Case 2: N = 16 (2^4) -> true
    cout << "Test 2 (N = 16): " << (solver.isPowerOfTwo(16) ? "YES" : "NO") 
         << " (Expected: YES)\n";

    // Test Case 3: N = 6 -> false
    cout << "Test 3 (N = 6):  " << (solver.isPowerOfTwo(6) ? "YES" : "NO") 
         << " (Expected: NO)\n";

    // Test Case 4: N = 0 -> false
    cout << "Test 4 (N = 0):  " << (solver.isPowerOfTwo(0) ? "YES" : "NO") 
         << " (Expected: NO)\n";

    // Test Case 5: N = 1073741824 (2^30) -> true
    cout << "Test 5 (2^30):   " << (solver.isPowerOfTwo(1073741824) ? "YES" : "NO") 
         << " (Expected: YES)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Exactly one subtraction and one bitwise AND operation: O(1) single CPU cycle.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) strictly.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. The condition `(n > 0) && ((n & (n - 1)) == 0)` is the canonical test for powers of 2.
 * 2. Don't omit operator precedence parentheses: `&` has lower precedence than `==`!
 */
