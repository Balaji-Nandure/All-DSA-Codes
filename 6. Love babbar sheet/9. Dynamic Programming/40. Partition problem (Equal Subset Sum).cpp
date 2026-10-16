#include <iostream>
#include <vector>
#include <numeric>
#include <bitset>

using namespace std;

/**
 * Problem: Partition problem (Equal Subset Sum)
 * 
 * Given an array arr[] of size N, check if it can be partitioned into two subsets 
 * such that the sum of elements in both subsets is equal.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - This is the decision version of "8. Subset Sum" applied to bisecting an array.
 * - Total sum must be even; if odd, division into two equal integer halves is strictly impossible.
 * - Target to search for is exactly total_sum / 2.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - 0-1 Knapsack Subset Sum Reduction:
 *   1. Calculate total_sum.
 *      If total_sum % 2 != 0: return false (parity impossibility).
 *      Let target = total_sum / 2.
 *   
 *   2. 1D Boolean Dynamic Programming:
 *      Maintain dp[target + 1] = false with dp[0] = true.
 *      For each number x in arr:
 *        Traverse j BACKWARD from target down to x:
 *        dp[j] = dp[j] || dp[j - x]
 *   
 *   3. Hardware Bitset Acceleration:
 *      bitset<MAX_TARGET> bits;
 *      bits[0] = 1;
 *      For each x in arr:
 *        bits |= (bits << x);
 *      Return bits[target].
 *      Provides 64x bitwise parallelism!
 */

class Solution {
public:
    int equalPartition(int N, int arr[]) {
        int total_sum = 0;
        for (int i = 0; i < N; i++) {
            total_sum += arr[i];
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Odd sum cannot be partitioned into two equal integer halves
        if (total_sum % 2 != 0) {
            return 0;
        }

        int target = total_sum / 2;
        vector<bool> dp(target + 1, false);
        dp[0] = true;

        for (int i = 0; i < N; i++) {
            int x = arr[i];
            // Backward traversal enforces 0-1 single-use of each element
            // *** CRUCIAL LINE: 1D backward traversal to prevent element reuse ***
            for (int j = target; j >= x; j--) {
                dp[j] = dp[j] || dp[j - x];
            }
        }

        return dp[target] ? 1 : 0;
    }

    // Ultrafast Bitset implementation
    bool equalPartitionBitset(int N, int arr[]) {
        int total_sum = 0;
        for (int i = 0; i < N; i++) total_sum += arr[i];
        if (total_sum % 2 != 0) return false;

        int target = total_sum / 2;
        bitset<50005> bits;
        bits[0] = 1;

        for (int i = 0; i < N; i++) {
            bits |= (bits << arr[i]);
        }

        return bits[target];
    }
};

int main() {
    Solution sol;
    int arr1[] = {1, 5, 11, 5};
    int N1 = sizeof(arr1) / sizeof(arr1[0]);
    cout << "Can partition 1: " << sol.equalPartition(N1, arr1) << "\n";
    // Sum = 22. Target = 11. Subsets: {11} and {1, 5, 5}. Expected: 1.

    int arr2[] = {1, 3, 5};
    int N2 = sizeof(arr2) / sizeof(arr2[0]);
    cout << "Can partition 2: " << sol.equalPartition(N2, arr2) << "\n";
    // Sum = 9 (odd). Expected: 0.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N * (total_sum / 2)) using standard 1D DP.
 *   With Bitset: O(N * (total_sum / 2) / 64) with 64x speedup.
 * - Space Complexity: O(total_sum / 2) 1D boolean array.
 */
