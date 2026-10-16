#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

/**
 * Problem: Chocolate Distribution Problem
 * 
 * Given an array A of N chocolate packets where A[i] is the number of chocolates in packet i.
 * There are M students. Distribute exactly one packet to each student such that 
 * the difference between the maximum and minimum number of chocolates given is minimized.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Unlike "10. Candy Shop" where we used coupons to get extremes for free,
 *   here we need to select M elements out of N such that (max(subset) - min(subset)) is minimized.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Greedy Sorting + Fixed Size Sliding Window:
 *   1. Sort array in ascending order: A[0] <= A[1] <= ... <= A[N-1].
 *   2. Lemma: In a sorted array, the subset of M elements that minimizes (max - min) 
 *      MUST be a CONTIGUOUS subarray of length M.
 *      Proof: If a selected subset of M elements is not contiguous, contracting the boundary 
 *      to contiguous elements can only decrease or maintain the spread (max - min).
 *   3. Therefore, we only need to test all contiguous windows of size M:
 *      Window from index i to (i + M - 1).
 *      Spread = A[i + M - 1] - A[i].
 *   4. Minimize this spread over all 0 <= i <= N - M.
 */

class Solution {
public:
    long long findMinDiff(vector<long long>& a, long long n, long long m) {
        if (m == 0 || n == 0) return 0;
        if (n < m) return -1; // Not enough packets for all students

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Sorting clusters close numbers together, guaranteeing the optimal subset is contiguous
        sort(a.begin(), a.end());

        long long min_diff = LLONG_MAX;

        // Slide window of size m
        for (long long i = 0; i + m - 1 < n; i++) {
            // *** CRUCIAL LINE: Difference between maximum and minimum in the contiguous window of size m ***
            long long current_diff = a[i + m - 1] - a[i];
            min_diff = min(min_diff, current_diff);
        }

        return min_diff;
    }
};

int main() {
    Solution sol;
    vector<long long> a = {3, 4, 1, 9, 56, 7, 9, 12};
    long long n = a.size();
    long long m = 5;

    cout << "Minimum difference: " << sol.findMinDiff(a, n, m) << "\n";
    // Sorted: 1, 3, 4, 7, 9, 9, 12, 56
    // Windows of size 5:
    // [1, 3, 4, 7, 9] -> diff = 9 - 1 = 8
    // [3, 4, 7, 9, 9] -> diff = 9 - 3 = 6  <-- MINIMUM
    // [4, 7, 9, 9, 12] -> diff = 12 - 4 = 8
    // [7, 9, 9, 12, 56] -> diff = 56 - 7 = 49

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N log N) for sorting the packets. The sliding window takes O(N).
 * - Space Complexity: O(1) auxiliary memory.
 */
