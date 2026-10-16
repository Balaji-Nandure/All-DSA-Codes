/**
 * ============================================================================
 * Problem: Missing Number in Arithmetic Progression (AP) / Arithmetic Number
 * Category: Searching and Sorting / Mathematics
 * 
 * Problem Statement:
 * This classic problem has two ubiquitous variations in competitive programming
 * and technical interviews:
 * 
 * Variation 1 (Arithmetic Number - GFG):
 * Given three integers A (first term), B (target value), and C (common difference).
 * Determine whether B is present in the infinite sequence defined by:
 *   Term(n) = A + (n - 1) * C, for n >= 1 (where n is a positive integer).
 * 
 * Variation 2 (Find Missing Element in a Given AP Array):
 * Given an array of size N-1 representing an Arithmetic Progression with exactly
 * one missing element. The first and last elements are never missing. Find the 
 * missing element in O(log N) time.
 * 
 * Constraints:
 * Variation 1: -10^9 <= A, B, C <= 10^9
 * Variation 2: 3 <= N <= 10^5, Elements within [-10^9, 10^9]
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Dealing with Sign and Zero Division Edge Cases:
 *    - In Variation 1, C can be negative, zero, or positive.
 *    - Direct division `(B - A) / C` when C == 0 triggers runtime division by zero!
 *    - If C != 0, `(B - A)` must be cleanly divisible by C AND have the same sign
 *      (since n - 1 >= 0).
 * 2. Monotonic Binary Search on Index vs Value:
 *    - In Variation 2, for any index `i`, expected value is `arr[0] + i * d`.
 *    - If `arr[mid] == arr[0] + mid * d`, the left half [0...mid] is completely
 *      intact and flawless; the missing element MUST lie in the right half [mid+1...high].
 *    - If `arr[mid] != arr[0] + mid * d`, the missing element is at or to the left of `mid`.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Variation 1: O(1) Mathematical Formula
 *   - Case 1: C == 0. Then the sequence is purely constant {A, A, A...}.
 *     B exists if and only if B == A.
 *   - Case 2: C != 0.
 *     We need an integer n >= 1 such that B = A + (n - 1) * C.
 *     Rearranging: (n - 1) = (B - A) / C.
 *     Thus: (B - A) % C == 0 AND (B - A) / C >= 0.
 * 
 * Variation 2: O(log N) Binary Search
 *   - Compute common difference `d = (arr[n-1] - arr[0]) / n` where n is original length.
 *   - Binary search on array indices [0, n - 2]:
 *     Compare `arr[mid]` with expected `arr[0] + mid * d`.
 *     This achieves O(log N) time instead of O(N) linear scan.
 * ============================================================================
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * Variation 1: Checks if number B belongs to the AP starting at A with difference C.
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    int inSequence(long long A, long long B, long long C) {
        // Edge Case 1: Common difference is zero -> Sequence is {A, A, A, ...}
        if (C == 0) {
            return (A == B) ? 1 : 0;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Both conditions must hold:
        // 1. (B - A) must be a multiple of C: (B - A) % C == 0
        // 2. (B - A) and C must have identical signs: (B - A) / C >= 0 (since n >= 1)
        if ((B - A) % C == 0 && (B - A) / C >= 0) {
            return 1;
        }

        return 0;
    }

    /**
     * Variation 2: Finds the missing element in a sorted AP array of size (N - 1).
     * Time Complexity: O(log N)
     * Space Complexity: O(1)
     */
    long long findMissingInAPArray(const vector<long long>& arr) {
        int m = arr.size(); // Current size is N - 1
        int n = m + 1;      // Original total size N

        // Common difference of the original complete AP
        long long d = (arr[m - 1] - arr[0]) / m;

        // If common difference is 0, all elements are identical
        if (d == 0) return arr[0];

        int low = 0, high = m - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            // Check if the missing element is immediately after mid
            if (mid < m - 1 && arr[mid + 1] - arr[mid] != d) {
                return arr[mid] + d;
            }

            // Check if the missing element is immediately before mid
            if (mid > 0 && arr[mid] - arr[mid - 1] != d) {
                return arr[mid - 1] + d;
            }

            // Expected value at mid in an undisturbed AP
            long long expected = arr[0] + (long long)mid * d;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // If arr[mid] matches expected, the perturbation (missing number)
            // hasn't happened yet in the prefix [0...mid], so it must be on the right.
            if (arr[mid] == expected) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return -1; // Fallback
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // --- Variation 1 Tests ---
    // A = 1, B = 7, C = 2 -> AP: 1, 3, 5, 7, ... -> Found!
    cout << "Var 1 Test 1: " << solver.inSequence(1, 7, 2) << " (Expected: 1)\n";

    // A = 1, B = 7, C = 3 -> AP: 1, 4, 7, ... -> Found!
    cout << "Var 1 Test 2: " << solver.inSequence(1, 7, 3) << " (Expected: 1)\n";

    // A = 1, B = 7, C = 0 -> AP: 1, 1, 1... -> Not found!
    cout << "Var 1 Test 3: " << solver.inSequence(1, 7, 0) << " (Expected: 0)\n";

    // A = 7, B = 1, C = -2 -> AP: 7, 5, 3, 1... -> Found!
    cout << "Var 1 Test 4: " << solver.inSequence(7, 1, -2) << " (Expected: 1)\n";

    // --- Variation 2 Tests ---
    // Array: {2, 4, 8, 10} -> Missing 6
    vector<long long> arr1 = {2, 4, 8, 10};
    cout << "Var 2 Test 1: Missing = " << solver.findMissingInAPArray(arr1) << " (Expected: 6)\n";

    // Array: {1, 6, 11, 16, 21, 31} -> Missing 26
    vector<long long> arr2 = {1, 6, 11, 16, 21, 31};
    cout << "Var 2 Test 2: Missing = " << solver.findMissingInAPArray(arr2) << " (Expected: 26)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Variation 1 (Arithmetic Number):
 *   - Time Complexity: O(1) - Constant arithmetic checks and modulo operations.
 *   - Space Complexity: O(1) - Zero extra space.
 * 
 * Variation 2 (Missing Element in AP):
 *   - Time Complexity: O(log N) - Standard binary search halving the interval each step.
 *   - Space Complexity: O(1) - In-place index traversal.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Always check for divisor == 0 before performing any modulo or division.
 * 2. In binary search over arithmetic sequences, compare `arr[mid]` directly
 *    with theoretical value `arr[0] + mid * d` to identify which side is corrupted.
 */
