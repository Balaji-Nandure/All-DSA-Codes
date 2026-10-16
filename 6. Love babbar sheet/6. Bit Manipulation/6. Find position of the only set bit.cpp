/**
 * ============================================================================
 * Problem: Find Position of the Only Set Bit
 * Category: Bit Manipulation
 * 
 * Problem Statement:
 * Given a number N. If the number contains exactly one set bit in its binary
 * representation, find the 1-based position of that set bit (counted from the 
 * rightmost / least significant bit).
 * If the number does not have exactly one set bit (i.e., has 0 set bits, or has
 * 2 or more set bits), return -1.
 * 
 * Example 1:
 * Input: N = 2 (binary 10)
 * Output: 2
 * 
 * Example 2:
 * Input: N = 5 (binary 101)
 * Output: -1 (contains two set bits)
 * 
 * Example 3:
 * Input: N = 16 (binary 10000)
 * Output: 5
 * 
 * Constraints:
 * 0 <= N <= 10^9
 * Must run in O(1) time and O(1) auxiliary space.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Validation + Extraction:
 *    - In Problem 5, we only verified if N is a power of 2 (boolean `true`/`false`).
 *    - Here, we must first validate that N is indeed a power of 2, AND THEN
 *      extract the exact 1-indexed bit position (i.e. 2^k -> position k + 1).
 * 2. Logarithmic Bit Indexing:
 *    - The position of a lone set bit in N = 2^k is simply `k + 1 = log2(N) + 1`.
 *    - Can also be directly computed using trailing zero counting `ctz(N) + 1`.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * 2-Step Verification and Position Extraction O(1) Time:
 *   - Step 1: Validation
 *       If `N <= 0` or `(N & (N - 1)) != 0`:
 *         The number does not contain exactly one set bit -> return -1.
 *   - Step 2: Position Calculation
 *       Since N is verified to be of the form 2^k:
 *         `position = log2(N) + 1;` (or count trailing zeros + 1).
 *   - Total Time: O(1) strictly.
 * ============================================================================
 */

#include <iostream>
#include <cmath>

using namespace std;

class Solution {
public:
    /**
     * Finds the 1-based position of the only set bit in N, or -1 if invalid.
     * @param n Input integer.
     * @return 1-based position or -1.
     */
    int findPosition(int n) {
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Guard condition: Validate that N has EXACTLY ONE set bit.
        // If n <= 0 or clearing the lowest bit doesn't yield 0, N is invalid.
        if (n <= 0 || (n & (n - 1)) != 0) {
            return -1;
        }

        // Method A: Logarithmic extraction
        // If n = 2^k, log2(n) = k, so 1-based position = k + 1
        return log2(n) + 1;
    }

    /**
     * Method B: Bit shifting iteration without floating point math
     */
    int findPositionShift(int n) {
        if (n <= 0 || (n & (n - 1)) != 0) return -1;

        int pos = 0;
        while (n > 0) {
            pos++;
            n >>= 1;
        }
        return pos;
    }

    /**
     * Method C: Hardware Count Trailing Zeros (CTZ)
     */
    int findPositionHardware(int n) {
        if (n <= 0 || (n & (n - 1)) != 0) return -1;
        return __builtin_ctz(n) + 1;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case 1: N = 2 (10) -> pos = 2
    cout << "Test 1 (N = 2):  Pos = " << solver.findPosition(2) << " (Expected: 2)\n";

    // Test Case 2: N = 5 (101) -> invalid (two set bits) -> -1
    cout << "Test 2 (N = 5):  Pos = " << solver.findPosition(5) << " (Expected: -1)\n";

    // Test Case 3: N = 16 (10000) -> pos = 5
    cout << "Test 3 (N = 16): Pos = " << solver.findPosition(16) << " (Expected: 5)\n";

    // Test Case 4: N = 0 -> -1
    cout << "Test 4 (N = 0):  Pos = " << solver.findPosition(0) << " (Expected: -1)\n";

    // Test Case 5: N = 1 (1) -> pos = 1
    cout << "Test 5 (N = 1):  Pos = " << solver.findPosition(1) << " (Expected: 1)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Bitwise check `n & (n - 1)`: O(1).
 *   - Position extraction via `log2` or `__builtin_ctz`: O(1) hardware instructions.
 *   - Total Time: O(1) constant time.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) strictly.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Always validate single-bit cardinality before performing log2 or trailing zero extraction.
 * 2. 1-based bit index for power of two 2^k is simply `ctz(2^k) + 1 = k + 1`.
 */
