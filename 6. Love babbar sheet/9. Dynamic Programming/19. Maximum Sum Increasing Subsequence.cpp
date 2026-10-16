#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Problem: Maximum Sum Increasing Subsequence (MSIS)
 * 
 * Given an array of N positive integers, find the maximum sum of a subsequence 
 * such that all elements of the subsequence are sorted in strictly increasing order.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "16. Longest Increasing Subsequence (LIS)", we maximized the COUNT of elements.
 * - Here, we maximize the SUM of elements in the increasing subsequence.
 * - Critical Pitfall: Patience Sorting with binary search FAILS for MSIS!
 *   Why? Because a shorter subsequence with large elements (e.g., [100, 200] sum = 300) 
 *   can be vastly superior in sum to a longer subsequence with tiny elements (e.g., [1, 2, 3, 4, 5] sum = 15).
 *   Subsequence length and sum are not monotonic, so Dynamic Programming is required.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Dynamic Programming:
 *   Let dp[i] be the maximum sum of an increasing subsequence that ends strictly at index i.
 *   
 *   Base Case:
 *     dp[i] = arr[i] (a subsequence containing just arr[i] itself has sum arr[i]).
 *   
 *   Transitions for 0 <= j < i:
 *     If arr[j] < arr[i]:
 *       dp[i] = max(dp[i], dp[j] + arr[i])
 *   
 *   Result:
 *     max_{0 <= i < N} dp[i]
 */

class Solution {
public:
    int maxSumIS(int arr[], int n) {
        vector<int> dp(n);

        // Base case: Each element alone forms an increasing subsequence of sum arr[i]
        for (int i = 0; i < n; i++) {
            dp[i] = arr[i];
        }

        int max_sum = arr[0];

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                // Strictly increasing condition
                if (arr[j] < arr[i]) {
                    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                    // Maximize cumulative value sum rather than sequence length count
                    dp[i] = max(dp[i], dp[j] + arr[i]);
                }
            }
            max_sum = max(max_sum, dp[i]);
        }

        return max_sum;
    }
};

int main() {
    Solution sol;
    int arr1[] = {1, 101, 2, 3, 100};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    cout << "MSIS 1: " << sol.maxSumIS(arr1, n1) << "\n";
    // Subsequence {1, 2, 3, 100} has sum 106. (Notice {1, 101} has sum 102). Expected: 106.

    int arr2[] = {10, 5, 4, 3};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    cout << "MSIS 2: " << sol.maxSumIS(arr2, n2) << "\n";
    // Strictly decreasing: max single element is 10. Expected: 10.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N^2). Two nested loops comparing all pairs (j, i).
 *   (Can be optimized to O(N log N) using a Coordinate Compression + Fenwick/Segment Tree).
 * - Space Complexity: O(N) auxiliary array for dp table.
 */
