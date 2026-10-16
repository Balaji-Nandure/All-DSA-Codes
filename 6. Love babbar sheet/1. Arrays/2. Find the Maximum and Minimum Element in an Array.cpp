// Problem: Find the Maximum and Minimum Element in an Array
// Link (GFG): https://www.geeksforgeeks.org/problems/find-minimum-and-maximum-element-in-an-array4428/1
// Article: https://www.geeksforgeeks.org/dsa/maximum-and-minimum-in-an-array/
// Difficulty: Basic / Easy
// Topic: Array, Divide and Conquer, Optimization

/*
Problem Statement:
Given an array `arr` of size `n`, find the minimum and maximum elements in the array. 
Return your answer as a pair: `{min_element, max_element}`.

Example 1:
Input: arr = [3, 2, 1, 56, 10000, 167]
Output: min = 1, max = 10000
Explanation: Minimum element is 1 and maximum element is 10000.

Example 2:
Input: arr = [1, 345, 234, 21, 56789]
Output: min = 1, max = 56789
Explanation: Minimum element is 1 and maximum element is 56789.

Example 3:
Input: arr = [5]
Output: min = 5, max = 5
Explanation: Only one element, so it is both minimum and maximum.

Constraints:
- 1 <= arr.size() <= 10^5
- 1 <= arr[i] <= 10^12 (Values can exceed 32-bit signed int, use long long)
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 1 (Reverse an Array):
//   * Goal was in-place structural mutation (swapping elements from boundaries inwards).
//   * Number of comparisons was just the pointer condition `left < right` (N / 2 iterations).
// - In Problem 2 (Find Min and Max):
//   * Array remains strictly READ-ONLY (no mutations/swaps).
//   * The key interview challenge is NOT just finding min & max (which is trivial in 2N comparisons),
//     but MINIMIZING THE TOTAL NUMBER OF ELEMENT COMPARISONS below 2N!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Sorting (`std::sort`)
//   - Complexity: O(N log N) time, O(N log N) comparisons.
//   - Why NOT: Complete overkill. Sorting re-arranges all N elements just to read two values.
//
// Approach 2: Standard Linear Scan (One by One)
//   - Maintain `minVal` and `maxVal`. For each element:
//     * Compare with minVal (1 comparison).
//     * Compare with maxVal (1 comparison).
//   - Total Comparisons: 2 * (N - 1) comparisons.
//   - Why Suboptimal: We compare every element twice against candidates independently.
//
// Approach 3: Compare in Pairs (Tournament / Pairwise Method) - OPTIMAL & CHOSEN
//   - Intuition: If we take two elements at a time (A and B):
//     * 1st Comparison: Compare A and B with each other (determines local min & local max).
//     * 2nd Comparison: Compare local max with global max.
//     * 3rd Comparison: Compare local min with global min.
//   - That is 3 comparisons for every 2 elements!
//   - Total Comparisons: ~ 3 * (N / 2) = 1.5 * N comparisons!
//   - Reduction: Saves 25% of total comparisons compared to standard linear scan (1.5N vs 2N).
//   - Why this: It matches the theoretical minimum number of comparisons to find both min and max!

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // -------------------------------------------------------------------------
    // Method 1: Optimal Pairwise Comparison (Minimizes Comparisons to ~ 1.5 * N)
    // -------------------------------------------------------------------------
    pair<long long, long long> getMinMax(vector<long long> arr) {
        int n = arr.size();
        long long minVal, maxVal;
        int i = 0;

        // Base Step 1: Initialize minVal and maxVal based on whether N is odd or even
        if (n % 2 != 0) {
            // Odd length: initialize min and max to the very first element
            minVal = arr[0];
            maxVal = arr[0];
            i = 1; // Start pairing from index 1 (0 comparisons so far)
        } else {
            // Even length: compare the first two elements directly (1 comparison)
            if (arr[0] > arr[1]) {
                maxVal = arr[0];
                minVal = arr[1];
            } else {
                maxVal = arr[1];
                minVal = arr[0];
            }
            i = 2; // Start pairing from index 2
        }

        // Process remaining elements in PAIRS of two (arr[i] and arr[i + 1])
        while (i < n - 1) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Instead of comparing arr[i] with both minVal and maxVal (2 comparisons),
            // and arr[i+1] with both (another 2 comparisons = 4 comparisons total),
            // we FIRST compare arr[i] and arr[i+1] with each other (1 comparison).
            // Then the larger only fights maxVal, and the smaller only fights minVal!
            // This reduces 4 comparisons per pair down to 3 comparisons per pair!
            if (arr[i] > arr[i + 1]) {
                // arr[i] is candidate for maxVal, arr[i + 1] is candidate for minVal
                if (arr[i] > maxVal) maxVal = arr[i];         // Comparison 2
                if (arr[i + 1] < minVal) minVal = arr[i + 1]; // Comparison 3
            } else {
                // arr[i + 1] is candidate for maxVal, arr[i] is candidate for minVal
                if (arr[i + 1] > maxVal) maxVal = arr[i + 1]; // Comparison 2
                if (arr[i] < minVal) minVal = arr[i];         // Comparison 3
            }

            // Move pointer forward by 2 to grab the next pair
            i += 2;
        }

        return {minVal, maxVal};
    }

    // -------------------------------------------------------------------------
    // Method 2: Standard Linear Scan (Simple & Idiomatic, 2 * (N - 1) comparisons)
    // -------------------------------------------------------------------------
    pair<long long, long long> getMinMaxStandard(const vector<long long>& arr) {
        long long minVal = arr[0];
        long long maxVal = arr[0];

        for (int i = 1; i < (int)arr.size(); i++) {
            if (arr[i] < minVal) {
                minVal = arr[i];
            } else if (arr[i] > maxVal) {
                maxVal = arr[i];
            }
        }

        return {minVal, maxVal};
    }
};

/*
Comparison Count Analysis:
1. If N is Odd:
   - Initial comparison: 0 (first element set as both min and max).
   - Remaining elements: (N - 1) elements grouped into (N - 1) / 2 pairs.
   - Comparisons per pair: 3.
   - Total Comparisons = 3 * (N - 1) / 2 = 1.5 * (N - 1).
   - Example for N = 5: 3 * (4) / 2 = 6 comparisons (vs 8 comparisons in standard scan).

2. If N is Even:
   - Initial comparison: 1 (compare arr[0] and arr[1]).
   - Remaining elements: (N - 2) elements grouped into (N - 2) / 2 pairs.
   - Comparisons per pair: 3.
   - Total Comparisons = 1 + 3 * (N - 2) / 2.
   - Example for N = 6: 1 + 3 * (4) / 2 = 7 comparisons (vs 10 comparisons in standard scan).

Time Complexity: O(N)
- Exactly one linear pass through the array.
- Performs ~ 1.5 * N comparisons (25% fewer than standard 2 * N scan).

Space Complexity: O(1) Auxiliary Space
- Uses only two variable accumulators `minVal` and `maxVal`. No extra buffers.

Key Insights:
1. Why 1.5N is the Theoretical Optimum:
   - Information theory dictates that finding the minimum of N elements requires at least N - 1 comparisons.
   - Finding both min and max simultaneously cannot be done in fewer than ceil(3N / 2) - 2 comparisons.
   - Pairwise processing achieves this exact lower bound.
2. 64-bit Integer Safety:
   - Since array elements can be up to 10^12, `long long` must be used to avoid overflow.
*/
