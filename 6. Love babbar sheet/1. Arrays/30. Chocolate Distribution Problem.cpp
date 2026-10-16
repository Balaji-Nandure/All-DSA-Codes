// Problem: Chocolate Distribution Problem
// Link (Article): https://www.geeksforgeeks.org/dsa/chocolate-distribution-problem/
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/chocolate-distribution-problem3825/1
// Difficulty: Easy
// Topic: Array, Sorting, Sliding Window

/*
Problem Statement:
Given an array `arr[]` of positive integers where `arr[i]` represents the number of chocolates in 
the `i`-th packet. There are `m` students.
Distribute the packets among `m` students such that:
1. Each student gets exactly one packet.
2. The difference between the maximum number of chocolates given to a student and the minimum 
   number of chocolates given to a student is MINIMIZED.
Return the minimum possible difference.

Example 1:
Input: arr = [7, 3, 2, 4, 9, 12, 56], m = 3
Output: 2
Explanation: Pick packets [2, 3, 4]. Min = 2, Max = 4. Difference = 4 - 2 = 2.

Example 2:
Input: arr = [3, 4, 1, 9, 56, 7, 9, 12], m = 5
Output: 6
Explanation: Pick packets [3, 4, 7, 9, 9]. Min = 3, Max = 9. Difference = 9 - 3 = 6.

Constraints:
- 1 <= arr.size() <= 10^5
- 1 <= m <= arr.size()
- 1 <= arr[i] <= 10^9
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 9 (Minimize Heights): We modified elements by +k / -k.
// - In Problem 30 (Chocolate Distribution):
//   * Elements are FIXED; we must CHOOSE A SUBSET of size `m` from `n`.
//   * Sorting clusters numerically close elements together.
//   * In a sorted array, the difference between the extremes of ANY subset of size m is minimized
//     when the subset is a CONTIGUOUS SLICE of size m!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Sorting + Fixed-Size Sliding Window (OPTIMAL & CHOSEN)
//   - Step 1: Sort the array in ascending order: O(N log N).
//   - Step 2: Now, for any chosen window of size `m` starting at index `i`:
//     * Smallest packet = `arr[i]` (at the window's left edge).
//     * Largest packet = `arr[i + m - 1]` (at the window's right edge).
//     * Difference = `arr[i + m - 1] - arr[i]`.
//   - Step 3: Slide the window from `i = 0` to `n - m`, tracking the minimum difference.
//   - Complexity: O(N log N) time, O(1) space.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long findMinDiff(vector<long long>& arr, int m) {
        int n = arr.size();

        // Edge cases
        if (m == 0 || n == 0) return 0;
        if (m > n) return -1; // Not enough packets for all students

        // Step 1: Sort to place numerically adjacent packets next to each other
        sort(arr.begin(), arr.end());

        long long minDiff = LLONG_MAX;

        // Step 2: Slide a window of size m across the sorted array
        for (int i = 0; i + m - 1 < n; i++) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // In a sorted array, for any window [i ... i + m - 1], the elements are sorted:
            // arr[i] is guaranteed to be the minimum, and arr[i + m - 1] is guaranteed to be maximum.
            // The difference between the max and min for this group is simply arr[i + m - 1] - arr[i]!
            long long currentDiff = arr[i + m - 1] - arr[i];
            minDiff = min(minDiff, currentDiff);
        }

        return minDiff;
    }
};

/*
Time Complexity: O(N log N)
- Sorting the array of size N takes O(N log N).
- Sliding the window of size m takes (N - m + 1) iterations = O(N).
- Overall Time Complexity: O(N log N).

Space Complexity: O(1) Auxiliary Space
- In-place sorting with zero auxiliary memory allocated.

Key Insights:
1. Why Contiguous Windows are Guaranteed Optimal:
   - Suppose an optimal subset of size m was NOT contiguous in the sorted array (e.g. skipped an element).
   - Swapping out the extreme elements for any skipped intermediate elements could only DECREASE
     or maintain the gap `max - min`, never increase it!
   - Hence, the globally optimal subset must be a contiguous subarray in the sorted array.
*/
