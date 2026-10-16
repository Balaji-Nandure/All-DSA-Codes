#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

/**
 * Problem: Subset Sum Problem (Partition into Equal Subsets)
 * 
 * Given an array of positive integers, determine if there exists a subset whose sum 
 * is equal to a target value (or if the array can be partitioned into two subsets with equal sum).
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "32. Subset Sums (Meet-in-the-Middle)", we generated all 2^(N/2) sums for N up to 40.
 * - Here, each element can either be INCLUDED or EXCLUDED.
 * - By sorting descending, backtracking can prune enormous subtrees as soon as the rolling sum 
 *   exceeds target, or when the maximum possible remaining sum is insufficient.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Backtracking with Dual Pruning + DP Verification:
 *   1. Early Rejection:
 *      If total_sum is odd, it's impossible to divide into two equal integer halves.
 *      Target = total_sum / 2.
 *   2. Dual Branching Pruning:
 *      - Pruning 1 (Over-sum): If current_sum + arr[i] > target, skip candidate.
 *      - Pruning 2 (Under-sum): If current_sum + remaining_sum < target, prune entire subtree!
 *      - Pruning 3 (Descending Sort): Sorting descending ensures we pick larger elements first,
 *        triggering over-sum pruning at shallow recursion depths.
 *   3. 1D Dynamic Programming:
 *      Can also be solved in pseudo-polynomial O(N * Target) time using a 1D bitset or boolean table.
 */

class Solution {
    bool backtrack(int idx, int n, int current_sum, int target, int remaining_sum, vector<int>& arr) {
        // Target achieved!
        if (current_sum == target) {
            return true;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Pruning: If even adding all remaining numbers cannot reach target, prune branch
        if (idx == n || current_sum + remaining_sum < target) {
            return false;
        }

        // Try including arr[idx] if it doesn't exceed target
        if (current_sum + arr[idx] <= target) {
            if (backtrack(idx + 1, n, current_sum + arr[idx], target, remaining_sum - arr[idx], arr)) {
                return true;
            }
        }

        // Try excluding arr[idx]
        return backtrack(idx + 1, n, current_sum, target, remaining_sum - arr[idx], arr);
    }

public:
    bool equalPartition(int N, vector<int>& arr) {
        long long total_sum = 0;
        for (int x : arr) total_sum += x;

        // If total sum is odd, cannot be partitioned into two equal integer halves
        if (total_sum % 2 != 0) return false;

        int target = total_sum / 2;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Sort descending to test large elements first and hit pruning bounds immediately
        sort(arr.begin(), arr.end(), greater<int>());

        return backtrack(0, N, 0, target, total_sum, arr);
    }

    // DP approach for O(N * Target) comparison
    bool equalPartitionDP(int N, vector<int>& arr) {
        int total_sum = accumulate(arr.begin(), arr.end(), 0);
        if (total_sum % 2 != 0) return false;

        int target = total_sum / 2;
        vector<bool> dp(target + 1, false);
        dp[0] = true;

        for (int x : arr) {
            for (int j = target; j >= x; j--) {
                dp[j] = dp[j] || dp[j - x];
            }
        }

        return dp[target];
    }
};

int main() {
    Solution sol;
    vector<int> arr1 = {1, 5, 11, 5};
    int N1 = arr1.size();
    cout << "Can partition 1: " << (sol.equalPartition(N1, arr1) ? "YES" : "NO") << "\n";
    // Total sum = 22. Target = 11. Subsets: {11} and {1, 5, 5}. Expected: YES.

    vector<int> arr2 = {1, 3, 5};
    int N2 = arr2.size();
    cout << "Can partition 2: " << (sol.equalPartition(N2, arr2) ? "YES" : "NO") << "\n";
    // Total sum = 9 (odd). Expected: NO.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Backtracking Time Complexity: O(2^N) worst-case, but effectively pruned via remaining sum lookahead.
 * - DP Time Complexity: O(N * Target) pseudo-polynomial.
 * - Space Complexity: O(N) recursion stack for backtracking; O(Target) for 1D DP table.
 */
