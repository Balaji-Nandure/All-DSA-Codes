/**
 * ============================================================================
 * Problem: Two Numbers with Odd Occurrences (Single Number III / Two Non-Repeating)
 * Category: Bit Manipulation
 * 
 * Problem Statement:
 * Given an array of integers in which every element appears twice, except for 
 * TWO elements which appear only once.
 * Find the two non-repeating elements and return them in ascending order.
 * 
 * Example 1:
 * Input:  arr = [1, 2, 3, 2, 1, 4]
 * Output: [3, 4]
 * 
 * Example 2:
 * Input:  arr = [2, 1, 3, 2]
 * Output: [1, 3]
 * 
 * Constraints:
 * 2 <= N <= 10^5
 * -10^9 <= arr[i] <= 10^9
 * Must run in O(N) time and O(1) auxiliary space (no hash map or sorting).
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Single vs Dual Non-Repeating Recovery:
 *    - In single non-repeating element (Single Number I), XORing all elements yields
 *      the unique element directly: X ^ (duplicates ^ duplicates) = X ^ 0 = X.
 *    - When TWO distinct elements X and Y are unique, XORing the array yields (X ^ Y).
 *      We cannot separate X and Y directly from a single scalar XOR sum.
 * 2. Differentiating via Lowest Set Bit Partitioning:
 *    - Since X != Y, (X ^ Y) must have at least one set bit (value 1).
 *    - A set bit at position 'k' means X and Y differ at bit 'k' (one has 1, the other has 0).
 *    - This bit serves as a binary hash classifier, partitioning the array into
 *      two disjoint equivalence classes where X and Y are completely separated.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * 3-Step Bit Partitioning O(N) Time, O(1) Space:
 *   - Step 1: Compute cumulative XOR of all elements:
 *       `xorSum = arr[0] ^ arr[1] ^ ... ^ arr[N-1] = X ^ Y`.
 *   - Step 2: Isolate the rightmost set bit:
 *       `diffBit = xorSum & (-xorSum);` (or `xorSum & ~(xorSum - 1)`).
 *       (Note: cast to `unsigned int` or `long long` to prevent signed overflow
 *        when xorSum is INT_MIN).
 *   - Step 3: Divide and conquer into two XOR accumulators:
 *       - If `num & diffBit != 0`: `num1 ^= num`
 *       - If `num & diffBit == 0`: `num2 ^= num`
 *   - Because identical pairs fall into the same group and cancel each other out,
 *     `num1` isolates X and `num2` isolates Y!
 *   - Return in sorted order `{min(num1, num2), max(num1, num2)}`.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    /**
     * Finds the two non-repeating elements using XOR partitioning in O(N) time, O(1) space.
     * @param nums Array of integers.
     * @return Vector containing the two unique numbers in ascending order.
     */
    vector<long long> singleNumber(vector<long long>& nums) {
        long long xorSum = 0;

        // Step 1: XOR all elements to obtain (X ^ Y)
        for (long long num : nums) {
            xorSum ^= num;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Isolating the rightmost set bit of (X ^ Y).
        // This bit is guaranteed to be 1 in X and 0 in Y (or vice versa),
        // providing an orthogonal classifier to partition the entire array.
        long long diffBit = xorSum & (-xorSum);

        long long num1 = 0;
        long long num2 = 0;

        // Step 3: Partition array based on diffBit and XOR each partition independently
        for (long long num : nums) {
            if (num & diffBit) {
                num1 ^= num; // Group with diffBit set (contains X and its matching pairs)
            } else {
                num2 ^= num; // Group with diffBit unset (contains Y and its matching pairs)
            }
        }

        // Return in sorted order
        if (num1 > num2) {
            swap(num1, num2);
        }

        return {num1, num2};
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case 1: [1, 2, 3, 2, 1, 4] -> Unique: 3, 4
    vector<long long> nums1 = {1, 2, 3, 2, 1, 4};
    vector<long long> res1 = solver.singleNumber(nums1);
    cout << "Test 1: [" << res1[0] << ", " << res1[1] << "] (Expected: [3, 4])\n";

    // Test Case 2: [2, 1, 3, 2] -> Unique: 1, 3
    vector<long long> nums2 = {2, 1, 3, 2};
    vector<long long> res2 = solver.singleNumber(nums2);
    cout << "Test 2: [" << res2[0] << ", " << res2[1] << "] (Expected: [1, 3])\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Pass 1 (XOR sum): O(N).
 *   - Bit isolation: O(1).
 *   - Pass 2 (Partition XOR): O(N).
 *   - Total Time: O(N) linear time.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) strictly (only `xorSum`, `diffBit`, `num1`, `num2`).
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. The operation `diffBit = x & (-x)` extracts the lowest set bit using 2's complement.
 * 2. Using this bit as a partition filter decouples two intertwined XOR results cleanly.
 */
