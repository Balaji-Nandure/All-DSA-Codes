/**
 * ============================================================================
 * Problem: The Painter's Partition Problem
 * Category: Searching and Sorting
 * 
 * Problem Statement:
 * Dilpreet wants to paint his fence of N consecutive boards of varying lengths:
 * arr[0], arr[1], ..., arr[N-1].
 * He hires K painters for this work.
 * 
 * Each painter takes 1 unit of time to paint 1 unit of length.
 * Constraints on painting:
 *   1. Any painter paints only a contiguous (continuous) section of the fence.
 *   2. No two painters can share a single board.
 *   3. All boards must be painted.
 * 
 * Find the minimum time required to paint all boards under the condition that
 * all K painters work simultaneously in parallel. (i.e. minimize the maximum
 * sum of board lengths assigned to any single painter).
 * 
 * Constraints:
 * 1 <= N <= 10^5
 * 1 <= K <= 10^5
 * 1 <= arr[i] <= 10^6
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Isomorphic to Book Allocation and Split Array Largest Sum:
 *    - In Book Allocation (Problem 24), we allocated contiguous pages to M students.
 *    - Here, contiguous boards are assigned to K painters.
 *    - Notice: K can be greater than N. If K >= N, each painter paints at most 1 board,
 *      so the answer is simply max(arr).
 * 2. Minimax Optimization (Minimize the Maximum):
 *    - Objective: min_{partitions} ( max_{painter} (boards painted by painter) ).
 *    - The decision version ("Can we paint all boards such that no painter paints
 *      more than X units of length?") is monotonic with respect to X.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * 1. Search Space:
 *    - Lower Bound (`low`): max(arr[i]). No painter can paint less than the
 *      largest individual board.
 *    - Upper Bound (`high`): sum(arr[i]). A single painter paints the whole fence.
 * 2. Feasibility Test `isFeasible(arr, k, maxLimit)`:
 *    - Greedily assign boards to the current painter until adding the next board
 *      would exceed `maxLimit`.
 *    - Once it exceeds, assign a new painter.
 *    - If total painters needed <= K, then `maxLimit` is feasible.
 * 3. Binary Search:
 *    - If feasible: record candidate `ans = mid` and search for an even smaller
 *      maximum workload: `high = mid - 1`.
 *    - If not feasible: workload limit too tight, increase: `low = mid + 1`.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
private:
    /**
     * Greedy predicate: Checks if all boards can be painted by at most K painters
     * such that no painter paints more than 'maxLimit' total length.
     */
    bool isFeasible(const vector<long long>& arr, int k, long long maxLimit) {
        int paintersUsed = 1;
        long long currentLength = 0;

        for (long long board : arr) {
            // A single board larger than maxLimit cannot be painted by anyone
            if (board > maxLimit) return false;

            if (currentLength + board <= maxLimit) {
                currentLength += board;
            } else {
                paintersUsed++;
                currentLength = board;
                if (paintersUsed > k) return false;
            }
        }

        return paintersUsed <= k;
    }

public:
    /**
     * Computes the minimum time needed to paint all boards using at most K painters.
     * @param arr Lengths of contiguous fence boards.
     * @param k Number of available painters.
     * @return Minimum possible maximum time allocated to any painter.
     */
    long long minTimeToPaint(const vector<long long>& arr, int k) {
        int n = arr.size();
        if (n == 0) return 0;

        long long low = 0;
        long long high = 0;

        for (long long board : arr) {
            low = max(low, board);
            high += board;
        }

        long long ans = high;

        while (low <= high) {
            long long mid = low + (high - low) / 2;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Monotonic property: If K painters can paint within limit 'mid',
            // then any limit > mid is also feasible. We record 'mid' and greedily
            // squeeze the limit downwards: [low, mid - 1].
            if (isFeasible(arr, k, mid)) {
                ans = mid;
                high = mid - 1; // Squeeze search space to find a smaller maximum
            } else {
                low = mid + 1;  // Limit is too restrictive, more painters needed than K
            }
        }

        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case 1: arr = {5, 10, 30, 20, 15}, k = 3
    // Partition: {5, 10, 30} = 45, {20} = 20, {15} = 15 -> max is 45?
    // Better: {5, 10} = 15, {30} = 30, {20, 15} = 35 -> max is 35!
    vector<long long> arr1 = {5, 10, 30, 20, 15};
    int k1 = 3;
    cout << "Test 1: Min Time = " << solver.minTimeToPaint(arr1, k1) << " (Expected: 35)\n";

    // Test Case 2: arr = {10, 20, 30, 40}, k = 2
    // Partition: {10, 20, 30} = 60, {40} = 40 -> max is 60!
    vector<long long> arr2 = {10, 20, 30, 40};
    int k2 = 2;
    cout << "Test 2: Min Time = " << solver.minTimeToPaint(arr2, k2) << " (Expected: 60)\n";

    // Test Case 3: arr = {10, 10, 10, 10}, k = 2
    // Partition: {10, 10} = 20, {10, 10} = 20 -> max is 20!
    vector<long long> arr3 = {10, 10, 10, 10};
    int k3 = 2;
    cout << "Test 3: Min Time = " << solver.minTimeToPaint(arr3, k3) << " (Expected: 20)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Search space size: sum(arr) - max(arr).
 *   - Number of binary search iterations: log2(sum(arr)).
 *   - Feasibility check: O(N) per iteration.
 *   - Total Time Complexity: O(N * log(sum(arr))).
 *   - For N = 10^5 and sum = 10^11: ~37 * 10^5 ≈ 3.7 * 10^6 ops -> < 0.05 seconds.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1). Only a few variables for binary search.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. "Minimize the maximum workload across contiguous partitions" is the hallmark
 *    signature of Binary Search on Answer.
 * 2. The monotonic function is monotonic in terms of feasibility:
 *    False, False, ..., False, True, True, ..., True.
 */
