// Problem: Merge Two Sorted Arrays Without Extra Space
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/merge-two-sorted-arrays-1587115620/1
// Article: https://www.geeksforgeeks.org/dsa/merge-two-sorted-arrays/
// Link (LeetCode 88): https://leetcode.com/problems/merge-sorted-array/
// Difficulty: Hard / Medium
// Topic: Array, Two Pointers, Shell Sort, Gap Method

/*
Problem Statement:
Given two sorted arrays `a[]` of size `n` and `b[]` of size `m`.
Merge the two arrays in-place such that:
- `a[]` contains the first `n` smallest elements in sorted order.
- `b[]` contains the remaining `m` elements in sorted order.
You are NOT allowed to use any extra space (must be O(1) auxiliary space).

Example 1:
Input: a = [2, 4, 7, 10], b = [2, 3]
Output: 
a = [2, 2, 3, 4]
b = [7, 10]

Example 2:
Input: a = [1, 5, 9, 10, 15, 20], b = [2, 3, 8, 13]
Output:
a = [1, 2, 3, 5, 8, 9]
b = [10, 13, 15, 20]

Constraints:
- 1 <= n, m <= 10^5
- 0 <= a[i], b[i] <= 10^9
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 6 (Union/Intersection): Output was written to a NEW third array.
// - In Problem 12:
//   * Merging MUST happen in-place across TWO FIXED-SIZE ARRAYS simultaneously.
//   * Standard merge sort requires an O(N + M) temporary buffer.
//   * We must find an in-place comparison pattern that gradually places smaller elements into `a`
//     and larger elements into `b`.

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Swap from Boundaries and Sort (Practical & Clean)
//   - Pointer `i = n - 1` (largest in a), `j = 0` (smallest in b).
//   - While `i >= 0` and `j < m`:
//     * If `a[i] > b[j]`: swap(a[i], b[j]), i--, j++.
//     * Else: break (since both arrays are sorted, no further element in `a` can exceed `b[j]`).
//   - Finally, sort `a` and sort `b`.
//   - Complexity: O(min(n, m) + n log n + m log m) time, O(1) space.
//
// Approach 2: The Gap Method (Derived from Shell Sort) - THEORETICALLY OPTIMAL
//   - Treat `a` and `b` as one continuous virtual array of length `n + m`.
//   - Start with `gap = ceil((n + m) / 2)`.
//   - Compare and swap elements at index `k` and `k + gap`:
//     * Case 1: Both elements in `a`
//     * Case 2: One in `a`, one in `b`
//     * Case 3: Both elements in `b`
//   - In each pass, reduce `gap = ceil(gap / 2)` until `gap < 1`.
//   - Complexity: O((N + M) * log(N + M)) time, O(1) strict space!

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // Helper function to swap elements across the two arrays if left > right
    void swapIfGreater(vector<long long>& a, vector<long long>& b, int idx1, int idx2) {
        int n = a.size();
        if (idx1 < n && idx2 < n) {
            // Both elements in array `a`
            if (a[idx1] > a[idx2]) swap(a[idx1], a[idx2]);
        }
        else if (idx1 < n && idx2 >= n) {
            // idx1 in array `a`, idx2 in array `b`
            if (a[idx1] > b[idx2 - n]) swap(a[idx1], b[idx2 - n]);
        }
        else {
            // Both elements in array `b`
            if (b[idx1 - n] > b[idx2 - n]) swap(b[idx1 - n], b[idx2 - n]);
        }
    }

public:
    // -------------------------------------------------------------------------
    // Method 1: The Gap Method (Shell Sort Intuition - O((N + M) log(N + M)), O(1) Space)
    // -------------------------------------------------------------------------
    void mergeGapMethod(vector<long long>& a, vector<long long>& b) {
        int n = a.size(), m = b.size();
        int len = n + m;

        // Initial gap: ceil(len / 2)
        int gap = (len / 2) + (len % 2);

        while (gap > 0) {
            int left = 0;
            int right = left + gap;

            while (right < len) {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Compares elements at distance `gap` across the virtual joint array [a ... b].
                // If the left element is larger than the right element, swap them!
                // As gap decreases (log len passes), elements settle into their exact sorted slots.
                swapIfGreater(a, b, left, right);
                left++;
                right++;
            }

            if (gap == 1) break; // Finished final 1-gap pass
            gap = (gap / 2) + (gap % 2); // Halve the gap
        }
    }

    // -------------------------------------------------------------------------
    // Method 2: Boundary Swap + Individual Sort (O(min(N,M) + N log N + M log M))
    // -------------------------------------------------------------------------
    void mergeSwapAndSort(vector<long long>& a, vector<long long>& b) {
        int n = a.size(), m = b.size();
        int left = n - 1; // Largest candidate in a
        int right = 0;   // Smallest candidate in b

        // Swap out-of-order elements across boundaries
        while (left >= 0 && right < m) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Since `a` and `b` are individually sorted, if a[left] > b[right],
            // then a[left] definitively belongs in `b` and b[right] belongs in `a`!
            if (a[left] > b[right]) {
                swap(a[left], b[right]);
                left--;
                right++;
            } else {
                break; // If a[left] <= b[right], all remaining elements are already in correct sets
            }
        }

        // Sort both arrays independently to restore local sorted order
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
    }
};

/*
Time Complexity:
- Method 1 (Gap Method): O((N + M) * log(N + M))
  * Number of gap reductions: O(log(N + M)).
  * In each gap pass, we iterate through (N + M) elements: O(N + M).
- Method 2 (Swap & Sort): O(min(N, M) + N log N + M log M).

Space Complexity: O(1) Auxiliary Space
- Pure in-place swaps between the two vectors. Zero auxiliary arrays created.

Key Insights:
1. Why Gap Method Avoids External Buffering:
   - Gap method acts like Shell sort on the combined array. By comparing distant elements first,
     inversions are resolved in large jumps rather than single-step shifts.
2. The Boundary Swap Intuition:
   - Any element in `a` that is larger than the smallest in `b` MUST belong in `b`.
   - By swapping from the back of `a` and front of `b`, we ensure the `n` smallest elements
     end up in `a` and the `m` largest end up in `b`, after which standard sorting finalizes their order.
*/
