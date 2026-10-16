/**
 * ============================================================================
 * Problem: Count Set Bits in an Integer (Hamming Weight)
 * Category: Bit Manipulation
 * 
 * Problem Statement:
 * Given a positive integer N, count the total number of set bits (1s) in its
 * binary representation.
 * 
 * Example 1:
 * Input: N = 6 (binary 110)
 * Output: 2
 * 
 * Example 2:
 * Input: N = 13 (binary 1101)
 * Output: 3
 * 
 * Constraints:
 * 1 <= N <= 10^9
 * Must run in O(number of set bits) or O(1) time.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Bitwise Invariant Manipulation:
 *    - In previous categories (LinkedList, Arrays), operations were executed on
 *      nodes, pointers, and memory blocks.
 *    - Bit manipulation operates directly at the register level on the binary
 *      representation of numbers inside the ALU.
 * 2. Skipping Zero Bits (Brian Kernighan's Insight):
 *    - A naive loop shifts all 32 bits one by one: `n >>= 1` taking exactly 32 steps.
 *    - Brian Kernighan’s Algorithm jumps directly from set bit to set bit, executing
 *      in O(K) time where K is the number of 1s (e.g. For N = 1024, exactly 1 step!).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Brian Kernighan's Algorithm:
 *   - Mathematical Property:
 *       Subtracting 1 from an integer flips the lowest (rightmost) set bit and
 *       all trailing zeros to 1s.
 *       Example:
 *         N     = 12 (binary 1100)
 *         N - 1 = 11 (binary 1011)
 *         N & (N - 1) = 1000 (binary 8) -> The rightmost set bit is CLEARED!
 *   - By repeatedly evaluating `N = N & (N - 1)`, each iteration clears exactly
 *     one set bit until N becomes 0.
 *   - Total loop iterations equal the exact count of set bits.
 * ============================================================================
 */

#include <iostream>

using namespace std;

class Solution {
public:
    /**
     * Method 1: Brian Kernighan's Algorithm (O(Number of Set Bits) Time, O(1) Space)
     */
    int setBits(int n) {
        int count = 0;

        while (n > 0) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Bitwise AND of 'n' with '(n - 1)' unsets the lowest set bit in O(1) ALU time,
            // bypassing all intervening zero bits entirely.
            n = n & (n - 1);
            count++;
        }

        return count;
    }

    /**
     * Method 2: Hardware Intrinsics (POPCNT instruction, O(1) single cycle)
     */
    int setBitsBuiltin(int n) {
        return __builtin_popcount(n);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case 1: N = 6 (110 in binary -> 2 set bits)
    cout << "Test 1 (N = 6):  Set Bits = " << solver.setBits(6) << " (Expected: 2)\n";

    // Test Case 2: N = 13 (1101 in binary -> 3 set bits)
    cout << "Test 2 (N = 13): Set Bits = " << solver.setBits(13) << " (Expected: 3)\n";

    // Test Case 3: N = 1024 (10000000000 in binary -> 1 set bit)
    // Brian Kernighan executes in exactly 1 iteration!
    cout << "Test 3 (N = 1024): Set Bits = " << solver.setBits(1024) << " (Expected: 1)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Loop runs K times where K is the number of set bits (1 <= K <= 32).
 *   - Worst Case: O(32) = O(1) when all bits are 1 (e.g. 2^31 - 1).
 *   - Best Case: O(1) single iteration.
 *   - Hardware popcount: Exactly 1 CPU clock cycle via POPCNT instruction.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) strictly.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. The operation `n & (n - 1)` drops the lowest set bit.
 * 2. The operation `n & (-n)` isolates the lowest set bit.
 */
