#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

/**
 * Problem: Smallest sum contiguous subarray
 * 
 * Given an array of integers, find the contiguous subarray that has the MINIMUM sum.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - This is the exact dual of "35. Largest Sum Contiguous Subarray (Kadane's Algorithm)".
 * - Instead of maximizing sum, we minimize sum.
 * - Whenever the running sum exceeds the current element alone, we drop the positive prefix 
 *   and start fresh at the current element.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Inverted Kadane's Algorithm (O(N) Time, O(1) Space):
 *   Let dp[i] be the minimum sum of a contiguous subarray ending EXACTLY at index i.
 *   
 *   Recurrence:
 *     dp[i] = min(arr[i], dp[i - 1] + arr[i])
 *   
 *   Global Minimum:
 *     min_so_far = min_{0 <= i < N} dp[i]
 *   
 *   Mathematical Invariance:
 *     Can also be viewed as negating all elements: arr'[i] = -arr[i],
 *     running standard max-Kadane to find max_sum, and returning -max_sum.
 *     Direct min-Kadane achieves this natively without modifying the array.
 */

class Solution {
public:
    int smallestSumSubarray(vector<int>& a) {
        int n = a.size();
        int min_so_far = a[0];
        int current_sum = a[0];

        for (int i = 1; i < n; i++) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Inverted Kadane: Either extend the minimum subarray or start fresh at index i
            current_sum = min(a[i], current_sum + a[i]);

            // *** CRUCIAL LINE: Update global minimum contiguous sum ***
            min_so_far = min(min_so_far, current_sum);
        }

        return min_so_far;
    }
};

int main() {
    Solution sol;
    vector<int> a1 = {3, -4, 2, -3, -1, 7, -5};
    cout << "Smallest Sum 1: " << sol.smallestSumSubarray(a1) << "\n";
    // Subarray [-4, 2, -3, -1] has sum -6. Expected: -6.

    vector<int> a2 = {2, 6, 8, 1, 4};
    cout << "Smallest Sum 2: " << sol.smallestSumSubarray(a2) << "\n";
    // All positive: min single element is 1. Expected: 1.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N) single linear scan.
 * - Space Complexity: O(1) auxiliary space using rolling scalar variables.
 */
