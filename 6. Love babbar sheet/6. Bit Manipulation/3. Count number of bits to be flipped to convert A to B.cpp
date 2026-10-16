/**
 * ============================================================================
 * Problem: Bit Difference (Count Bits to Flip to Convert A to B / Hamming Distance)
 * Category: Bit Manipulation
 * 
 * Problem Statement:
 * You are given two numbers A and B. Write a program to count the number of bits
 * needed to be flipped to convert A to B.
 * 
 * Example 1:
 * Input:  A = 10, B = 20
 * Binary: A = 01010, B = 10100
 * Output: 4
 * Explanation: Bits at 4 positions differ (0th, 1st, 3rd, 4th bit).
 * 
 * Example 2:
 * Input:  A = 20, B = 25
 * Binary: A = 10100, B = 11001
 * Output: 3
 * 
 * Constraints:
 * 1 <= A, B <= 10^9
 * Must run in O(number of flipped bits) time and O(1) space.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Differential Bit Mapping:
 *    - In Problem 1, we counted set bits in a single standalone integer.
 *    - Here, we measure the "distance" (Hamming Distance) between TWO numbers.
 *    - The XOR operation fundamentally computes difference: (A ^ B) yields 1
 *      if and only if the corresponding bits in A and B are different.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * XOR Difference + Brian Kernighan's Algorithm:
 *   - Step 1: Compute `diff = A ^ B`.
 *       Each bit that needs to be flipped will be a 1 in `diff`.
 *   - Step 2: Count set bits in `diff` using Brian Kernighan's method:
 *       `while (diff > 0) { diff = diff & (diff - 1); count++; }`
 *   - Time: O(number of differing bits) <= 32 steps.
 *   - Space: O(1).
 * ============================================================================
 */

#include <iostream>

using namespace std;

class Solution {
public:
    /**
     * Counts the number of bits to flip to convert A to B.
     * @param a First integer.
     * @param b Second integer.
     * @return Number of bits to flip.
     */
    int countBitsFlip(int a, int b) {
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Bitwise XOR produces a 1 strictly at positions where 'a' and 'b' differ,
        // reducing the problem of bit difference directly to counting set bits in (a ^ b).
        int diff = a ^ b;
        int count = 0;

        // Apply Brian Kernighan's algorithm on the XOR result
        while (diff > 0) {
            diff = diff & (diff - 1);
            count++;
        }

        return count;
    }

    /**
     * Built-in hardware POPCNT version.
     */
    int countBitsFlipBuiltin(int a, int b) {
        return __builtin_popcount(a ^ b);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case 1: A = 10, B = 20 -> 4 bits to flip
    cout << "Test 1 (10 -> 20): Bits to flip = " << solver.countBitsFlip(10, 20) 
         << " (Expected: 4)\n";

    // Test Case 2: A = 20, B = 25 -> 3 bits to flip
    cout << "Test 2 (20 -> 25): Bits to flip = " << solver.countBitsFlip(20, 25) 
         << " (Expected: 3)\n";

    // Test Case 3: A = 7, B = 7 -> 0 bits to flip
    cout << "Test 3 (7 -> 7):   Bits to flip = " << solver.countBitsFlip(7, 7) 
         << " (Expected: 0)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Proportional to the number of differing bits: at most 32 operations for 32-bit int.
 *   - Total Time: O(1) constant time.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) strictly.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Hamming Distance between two integers is always `popcount(a ^ b)`.
 */
