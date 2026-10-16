#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/**
 * Problem: Minimum sum of absolute difference of pairs of two arrays
 * 
 * Given two arrays A and B of equal length N, pair each element of A with an element 
 * of B such that the sum of absolute differences between paired elements is minimized:
 * Minimize: sum(|A[i] - B[pi(i)]|) over all permutations pi.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "18. Maximum sum of absolute difference" and "19. Swap and Maximize", we wanted to MAXIMIZE 
 *   adjacent differences within one array by pairing extremes (high with low).
 * - Here, we have TWO distinct arrays and we want to MINIMIZE the pairwise absolute differences.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Greedy by Dual Sorting:
 *   Sort both arrays A and B in ascending order:
 *     A[0] <= A[1] <= ... <= A[N-1]
 *     B[0] <= B[1] <= ... <= B[N-1]
 *   Pair A[i] with B[i].
 * 
 * - Mathematical Proof (Monotonicity / Triangle Inequality):
 *   Consider 2 elements from each array: a1 <= a2 and b1 <= b2.
 *   There are two possible pairings:
 *     Case 1 (Ordered): |a1 - b1| + |a2 - b2|
 *     Case 2 (Crossed): |a1 - b2| + |a2 - b1|
 *   By checking all relative orderings of the 4 values on the number line,
 *   Case 1 is ALWAYS <= Case 2.
 *   Any inversion in pairing can be uncrossed without increasing the total sum.
 *   Hence, the sorted order yields the global minimum.
 */

class Solution {
public:
    long long findMinSum(vector<int>& A, vector<int>& B, int N) {
        // Step 1: Sort both arrays in ascending order
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        sort(A.begin(), A.end());
        sort(B.begin(), B.end());

        long long min_diff_sum = 0;

        // Step 2: Pair corresponding elements
        for (int i = 0; i < N; i++) {
            // *** CRUCIAL LINE: Matching i-th smallest with i-th smallest eliminates crossed distances ***
            min_diff_sum += abs((long long)A[i] - B[i]);
        }

        return min_diff_sum;
    }
};

int main() {
    Solution sol;
    vector<int> A = {4, 1, 8, 7};
    vector<int> B = {2, 3, 6, 5};
    int N = A.size();

    cout << "Min sum of abs diffs: " << sol.findMinSum(A, B, N) << "\n";
    // Sorted A: 1, 4, 7, 8
    // Sorted B: 2, 3, 5, 6
    // Pairs: |1-2| + |4-3| + |7-5| + |8-6| = 1 + 1 + 2 + 2 = 6

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N log N) dominated by sorting arrays A and B.
 * - Space Complexity: O(1) auxiliary space beyond input vectors.
 */
