/**
 * ============================================================================
 * Problem: The Double Helix (SPOJ ANARC05B / Maximum Sum Path in Two Arrays)
 * Category: Searching and Sorting / Two Pointers
 * 
 * Problem Statement:
 * Two sorted arrays of distinct integers are given: A and B.
 * You are walking down the arrays, accumulating the values of the elements visited.
 * You may start at the beginning of either array.
 * 
 * If you encounter an element that appears in BOTH arrays (called a "bridge" or 
 * "intersection point"), you have the option to switch to the other array or 
 * stay on the same array.
 * 
 * Find the maximum possible sum of elements you can collect from the start 
 * of your walk to the end of either array.
 * 
 * Constraints:
 * 1 <= N, M <= 10,000
 * Each array is strictly sorted in ascending order.
 * Array values are between -10,000 and 10,000.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Bridge/Intersection Decoupling:
 *    - In standard merge operations, we combine two sorted arrays into one.
 *    - Here, the problem decomposes into independent sub-problems divided by
 *      intersection points (bridges).
 *    - Between any two consecutive intersection points X and Y, any valid path
 *      must travel exclusively along array A or array B.
 * 2. Optimal Substructure (Greedy Property):
 *    - Because both paths converge at the exact same value at an intersection,
 *      the decision of which segment to take between two bridges is completely
 *      independent of all previous or future segments.
 *    - Thus, taking max(segmentSumA, segmentSumB) at each bridge guarantees
 *      the globally optimal path sum.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * 1. Two-Pointer Merging O(N + M):
 *    - Maintain pointers i for array A, j for array B.
 *    - Maintain running segment sums `sumA` and `sumB`.
 *    - If A[i] < B[j]: add A[i] to sumA, i++.
 *    - If B[j] < A[i]: add B[j] to sumB, j++.
 *    - If A[i] == B[j]: (Bridge found!)
 *        totalSum += max(sumA, sumB) + A[i];
 *        sumA = 0; sumB = 0;
 *        i++; j++;
 *    - After one or both arrays are exhausted, add remaining elements to sumA/sumB.
 *    - Finally, add max(remaining sumA, remaining sumB) to totalSum.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    /**
     * Calculates the maximum path sum across two sorted arrays with switching points.
     * @param A Strictly sorted vector of integers.
     * @param B Strictly sorted vector of integers.
     * @return Maximum attainable sum.
     */
    long long maxPathSum(const vector<int>& A, const vector<int>& B) {
        int n = A.size();
        int m = B.size();

        int i = 0, j = 0;
        long long sumA = 0;
        long long sumB = 0;
        long long totalSum = 0;

        while (i < n && j < m) {
            if (A[i] < B[j]) {
                sumA += A[i];
                i++;
            } else if (B[j] < A[i]) {
                sumB += B[j];
                j++;
            } else {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Bridge / Intersection point found: A[i] == B[j].
                // The segments traversed since the last bridge converge here.
                // We greedily commit max(sumA, sumB) + bridge value and reset segment sums.
                totalSum += max(sumA, sumB) + A[i];
                sumA = 0;
                sumB = 0;
                i++;
                j++;
            }
        }

        // Add remaining elements of array A
        while (i < n) {
            sumA += A[i++];
        }

        // Add remaining elements of array B
        while (j < m) {
            sumB += B[j++];
        }

        // Add the maximum of the final trailing segments
        totalSum += max(sumA, sumB);

        return totalSum;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case 1: Standard SPOJ example
    // A: 3, 5, 7, 9, 20, 25, 30, 40, 55, 56, 57, 60, 62
    // B: 1, 4, 7, 11, 14, 25, 44, 47, 55, 57, 100
    // Bridges: 7, 25, 55, 57
    // Segment 1 (before 7): A(3+5=8) vs B(1+4=5) -> pick A: 8 + 7 = 15
    // Segment 2 (7 to 25): A(9+20=29) vs B(11+14=25) -> pick A: 29 + 25 = 54
    // Segment 3 (25 to 55): A(30+40=70) vs B(44+47=91) -> pick B: 91 + 55 = 146
    // Segment 4 (55 to 57): A(56) vs B() -> pick A: 56 + 57 = 113
    // Segment 5 (after 57): A(60+62=122) vs B(100) -> pick A: 122
    // Total = 15 + 54 + 146 + 113 + 122 = 450!
    vector<int> A1 = {3, 5, 7, 9, 20, 25, 30, 40, 55, 56, 57, 60, 62};
    vector<int> B1 = {1, 4, 7, 11, 14, 25, 44, 47, 55, 57, 100};
    cout << "Test 1: Max Path Sum = " << solver.maxPathSum(A1, B1) << " (Expected: 450)\n";

    // Test Case 2: No common elements
    // A: {2, 3, 7, 10, 12} = 34
    // B: {1, 5, 78} = 84
    // Expected: max(34, 84) = 84
    vector<int> A2 = {2, 3, 7, 10, 12};
    vector<int> B2 = {1, 5, 78};
    cout << "Test 2: Max Path Sum = " << solver.maxPathSum(A2, B2) << " (Expected: 84)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Each element of array A is visited at most once: O(N).
 *   - Each element of array B is visited at most once: O(M).
 *   - Total Time Complexity: O(N + M).
 *   - Optimal linear time; any algorithm must read both arrays.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1). No auxiliary arrays, vectors, or recursion stack.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Common elements serve as decision synchronization barriers.
 * 2. Whenever an optimization problem can be split into independent intervals
 *    at fixed synchronization points, a greedy locally-optimal decision at each
 *    interval yields the globally optimal outcome.
 */
