/**
 * ============================================================================
 * Problem: Copy Set Bits in a Range
 * Category: Bit Manipulation
 * 
 * Problem Statement:
 * Given two integers X and Y, and a range [L, R] (1-indexed, counted from the 
 * rightmost / least significant bit).
 * Copy the set bits of Y in the range [L, R] to X.
 * (i.e. If a bit in Y at any position from L to R is 1, set the corresponding 
 * bit in X to 1. If it is 0 in Y, leave the bit in X unchanged).
 * Return the modified value of X.
 * 
 * Example 1:
 * Input:  X = 10, Y = 13, L = 2, R = 3
 * Binary: X = 01010, Y = 01101
 * Range [2, 3]: In Y, bit 2 is 0, bit 3 is 1.
 * Modified X = 01110 = 14
 * Output: 14
 * 
 * Example 2:
 * Input:  X = 8, Y = 7, L = 1, R = 2
 * Binary: X = 1000, Y = 0111
 * Range [1, 2]: In Y, bit 1 is 1, bit 2 is 1.
 * Modified X = 1011 = 11
 * Output: 11
 * 
 * Constraints:
 * 1 <= X, Y <= 10^9
 * 1 <= L <= R <= 32
 * Must run in O(1) time and O(1) auxiliary space.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Targeted Sub-Register Range Masking:
 *    - In previous problems, bit operations affected the entire integer or isolated
 *      individual bits.
 *    - Here, we construct a contiguous windowed bitmask spanning exactly [L, R].
 * 2. Non-Destructive Bit Splicing:
 *    - Bits in X outside [L, R] must remain untouched.
 *    - Bits in X inside [L, R] that are already 1 must not be turned off (OR operation).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Clean O(1) Bitmask Generation:
 *   - Step 1: Calculate the length of the range:
 *       `len = R - L + 1`
 *   - Step 2: Create a mask containing exactly `len` ones:
 *       `rawMask = (1LL << len) - 1`
 *       (e.g., len = 3 -> (1 << 3) - 1 = 8 - 1 = 7 = binary 111).
 *   - Step 3: Shift the mask so it aligns with position L:
 *       `mask = rawMask << (L - 1)`
 *   - Step 4: Extract the relevant set bits from Y:
 *       `ySetBits = Y & mask`
 *   - Step 5: Transfer the set bits into X using bitwise OR:
 *       `result = X | ySetBits`
 *   - Total Time: O(1) single-cycle ALU operations.
 * ============================================================================
 */

#include <iostream>

using namespace std;

class Solution {
public:
    /**
     * Copies set bits of Y in range [L, R] to X.
     * @param x Target integer to modify.
     * @param y Source integer containing bits to copy.
     * @param l Left boundary of range (1-indexed from right).
     * @param r Right boundary of range (1-indexed from right).
     * @return Updated value of X.
     */
    int setSetBit(int x, int y, int l, int r) {
        // Boundary validation
        if (l < 1 || r > 32 || l > r) {
            return x;
        }

        // Calculate length of the target bit range
        int len = r - l + 1;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Construct a continuous bitmask of 1s in the exact range [L, R]:
        // ((1LL << len) - 1) creates 'len' consecutive 1s, shifted left by (L - 1).
        long long mask = ((1LL << len) - 1) << (l - 1);

        // Extract set bits from Y within the mask, and merge into X via bitwise OR
        return x | (y & mask);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case 1: X = 10, Y = 13, L = 2, R = 3 -> Expected 14
    cout << "Test 1: Result = " << solver.setSetBit(10, 13, 2, 3) << " (Expected: 14)\n";

    // Test Case 2: X = 8, Y = 7, L = 1, R = 2 -> Expected 11
    cout << "Test 2: Result = " << solver.setSetBit(8, 7, 1, 2) << " (Expected: 11)\n";

    // Test Case 3: X = 44, Y = 3, L = 1, R = 5
    // X = 101100, Y = 000011 -> X | (Y & 011111) = 101111 = 47
    cout << "Test 3: Result = " << solver.setSetBit(44, 3, 1, 5) << " (Expected: 47)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Generation of mask and bitwise operations execute in O(1) single CPU cycle.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) strictly.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Generating a contiguous mask of K ones: `(1 << K) - 1`.
 * 2. Use `1LL` to avoid undefined behavior when shifting by 32 or more bits.
 */
