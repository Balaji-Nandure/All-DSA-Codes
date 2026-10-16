// Problem: Minimum Swaps Required to Bring Elements Less Than or Equal to K Together
// Link (Article): https://www.geeksforgeeks.org/dsa/minimum-swaps-required-bring-elements-less-equal-k-together/
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/minimum-swaps-required-to-bring-all-elements-less-than-or-equal-to-k-together4847/1
// Difficulty: Medium
// Topic: Array, Sliding Window, Two Pointers

/*
Problem Statement:
Given an array `arr[]` of `n` positive integers and a number `k`. 
Find the minimum number of swaps required to bring all elements less than or equal to `k` together 
into a single contiguous subarray.

Example 1:
Input: arr = [2, 1, 5, 6, 3], k = 3
Output: 1
Explanation: Elements <= 3 are {2, 1, 3}. Total count = 3.
If we swap 5 with 3, array becomes [2, 1, 3, 6, 5], where {2, 1, 3} are together. Swaps = 1.

Example 2:
Input: arr = [2, 7, 9, 5, 8, 7, 4], k = 6
Output: 2
Explanation: Elements <= 6 are {2, 5, 4}. Total count = 3.
Window [2, 7, 9] requires 2 swaps to replace 7 and 9 with 5 and 4.

Constraints:
- 1 <= arr.size() <= 10^5
- 1 <= arr[i] <= 10^5
- 1 <= k <= 10^5
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 5: We segregated negatives and positives to two ends.
// - In Problem 33:
//   * All elements <= k must be clustered CONTIGUOUSLY anywhere in the array.
//   * The key is to realize: If there are `C` elements <= k in total, they MUST ultimately
//     occupy a window of size `C`!
//   * A swap merely trades an undesirable element (> k) inside the window with a desirable element (<= k) outside!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Fixed-Size Sliding Window of Size C (OPTIMAL & CHOSEN)
//   - Step 1: Count total elements <= k in the entire array. Let this be `targetWindowSize = C`.
//     * If C <= 1: Elements are already trivially together. Return 0.
//   - Step 2: In the first window of size `C` [0 ... C - 1], count how many elements are > k (unwanted elements, called `bad`).
//     * These `bad` elements MUST be swapped out of the window.
//     * Hence, initial swaps needed for this window = `bad`.
//   - Step 3: Slide the window of size C across the array:
//     * Outgoing element `arr[i - C]`: If it was > k, decrement `bad--`.
//     * Incoming element `arr[i]`: If it is > k, increment `bad++`.
//     * Update `minSwaps = min(minSwaps, bad)`.
//   - Complexity: Exactly O(N) time in a single pass, O(1) space!

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minSwap(vector<int>& arr, int k) {
        int n = arr.size();

        // Step 1: Count total elements <= k (this defines our target window size)
        int targetWindowSize = 0;
        for (int x : arr) {
            if (x <= k) targetWindowSize++;
        }

        // If 0 or 1 such element, they are already together
        if (targetWindowSize <= 1) return 0;

        // Step 2: Count 'bad' elements (> k) in the first window of size targetWindowSize
        int bad = 0;
        for (int i = 0; i < targetWindowSize; i++) {
            if (arr[i] > k) bad++;
        }

        int minSwaps = bad;

        // Step 3: Slide the window of size targetWindowSize from index targetWindowSize to n - 1
        for (int i = targetWindowSize; i < n; i++) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // The number of swaps needed to cluster all elements <= k into the current window
            // is EXACTLY EQUAL to the count of 'bad' elements (> k) currently residing in this window!
            // We maintain 'bad' in O(1) time as the window slides:

            // Remove effect of outgoing element
            if (arr[i - targetWindowSize] > k) {
                bad--;
            }
            // Add effect of incoming element
            if (arr[i] > k) {
                bad++;
            }

            minSwaps = min(minSwaps, bad);
        }

        return minSwaps;
    }
};

/*
Time Complexity: O(N)
- First pass to count total elements <= k: O(N).
- First window initialization: O(C) <= O(N).
- Sliding the window across the remaining elements: O(N - C).
- Overall Time Complexity: O(N) linear time.

Space Complexity: O(1) Auxiliary Space
- Pure scalar variables (`targetWindowSize`, `bad`, `minSwaps`).

Key Insights:
1. Transforming "Swaps" into "Window Density":
   - Directly simulating swaps would be an exponential or greedy nightmare.
   - Recognizing that any group of C elements forms a window, and that each element > k in that window
     requires exactly 1 swap to fix, reduces the problem to finding the window with MINIMUM unwanted elements!
*/
