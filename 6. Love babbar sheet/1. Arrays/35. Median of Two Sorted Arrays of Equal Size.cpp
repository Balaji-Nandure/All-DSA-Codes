// Problem: Median of Two Sorted Arrays of Equal Size
// Link (Article): https://www.geeksforgeeks.org/dsa/median-of-two-sorted-arrays/
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/find-the-median0527/1
// Difficulty: Hard / Medium
// Topic: Array, Binary Search, Divide and Conquer

/*
Problem Statement:
Given two sorted arrays `arr1[]` and `arr2[]` of the SAME size `n`. 
Find the median of the combined array of size `2n` obtained after merging the two sorted arrays.
Since the total number of elements `2n` is always even, the median is defined as:
    `median = (element_n + element_{n+1}) / 2` (or integer division).

Example 1:
Input: arr1 = [1, 12, 15, 26, 38], arr2 = [2, 13, 17, 30, 45], n = 5
Output: 16
Explanation: Merged sorted array = [1, 2, 12, 13, 15, 17, 26, 30, 38, 45].
Middle elements are 15 and 17. Median = (15 + 17) / 2 = 16.

Example 2:
Input: arr1 = [1, 2, 5, 6, 8], arr2 = [13, 17, 30, 45, 50], n = 5
Output: 10
Explanation: Middle elements are 8 and 13. Median = (8 + 13) / 2 = 10.

Constraints:
- 1 <= n <= 10^5
- 1 <= arr1[i], arr2[i] <= 10^9
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 12: We merged two sorted arrays into two physical arrays.
// - In Problem 35:
//   * We do NOT need to merge or sort the arrays!
//   * We only need to find the TWO MIDDLE VALUES in the virtual merged stream.
//   * Because both arrays are sorted and equal in size, we can use BINARY SEARCH to discard
//     half of both arrays simultaneously, achieving O(log N) time!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Merge Counter (Linear O(N) Time, O(1) Space)
//   - Keep pointers `i` and `j`. Advance until reaching index `n - 1` and `n`.
//   - Complexity: O(N) time, O(1) space.
//
// Approach 2: Binary Search Divide & Conquer (O(log N) Time, O(1) Space - OPTIMAL)
//   - Find medians `m1` of `arr1` and `m2` of `arr2`:
//     * If `m1 == m2`: Both halves balance out perfectly. Median is `m1`!
//     * If `m1 < m2`: The median of the merged array cannot lie in `arr1[0 ... m1 - 1]`
//       nor in `arr2[m2 + 1 ... n - 1]`.
//       Discard first half of `arr1` and second half of `arr2`, and recurse on remaining halves!
//     * If `m1 > m2`: Discard second half of `arr1` and first half of `arr2`!
//   - In every step, the search range is halved: O(log N) time!

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // -------------------------------------------------------------------------
    // Method 1: Binary Search Partition (O(log N) Time, O(1) Space - Optimal)
    // -------------------------------------------------------------------------
    int getMedianBinarySearch(vector<int>& arr1, vector<int>& arr2) {
        int n = arr1.size();
        int low = 0, high = n;

        // Partition arr1 such that left partition has elements from arr1 and arr2
        while (low <= high) {
            int cut1 = low + (high - low) / 2;
            int cut2 = n - cut1; // Because left half of combined array needs exactly n elements

            // Boundary values around the cut
            int l1 = (cut1 == 0) ? INT_MIN : arr1[cut1 - 1];
            int l2 = (cut2 == 0) ? INT_MIN : arr2[cut2 - 1];
            int r1 = (cut1 == n) ? INT_MAX : arr1[cut1];
            int r2 = (cut2 == n) ? INT_MAX : arr2[cut2];

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Valid partition condition: Every element in left half must be <= every element in right half!
            // That is: l1 <= r2 and l2 <= r1.
            // When this holds, max(l1, l2) is the n-th element, and min(r1, r2) is the (n+1)-th element!
            if (l1 <= r2 && l2 <= r1) {
                return (max(l1, l2) + min(r1, r2)) / 2;
            }
            else if (l1 > r2) {
                // Too many large elements taken from arr1 -> shift cut left
                high = cut1 - 1;
            }
            else {
                // Too few elements taken from arr1 -> shift cut right
                low = cut1 + 1;
            }
        }

        return 0;
    }

    // -------------------------------------------------------------------------
    // Method 2: Two-Pointer Merge Step (O(N) Time, O(1) Space - Simple & Robust)
    // -------------------------------------------------------------------------
    int getMedianLinear(const vector<int>& arr1, const vector<int>& arr2) {
        int n = arr1.size();
        int i = 0, j = 0;
        int m1 = -1, m2 = -1;

        // March until we identify the n-th and (n+1)-th elements
        for (int count = 0; count <= n; count++) {
            m2 = m1; // m2 will store element (n) and m1 will store element (n + 1)
            if (i < n && j < n) {
                if (arr1[i] <= arr2[j]) {
                    m1 = arr1[i++];
                } else {
                    m1 = arr2[j++];
                }
            } else if (i < n) {
                m1 = arr1[i++];
            } else {
                m1 = arr2[j++];
            }
        }

        return (m1 + m2) / 2;
    }
};

/*
Time Complexity:
- Method 1 (Binary Search): O(log N) — standard binary search over the partition cut range [0 ... N].
- Method 2 (Linear Count): O(N) — marches up to N + 1 elements.

Space Complexity: O(1) Auxiliary Space
- Pure mathematical partition indices with zero array copies.

Key Insights:
1. The Partition Invariant:
   - Partitioning `arr1` at `cut1` forces `arr2` to be partitioned at `n - cut1` so the total elements
     in the left partition is always exactly `n`.
   - Once `l1 <= r2` and `l2 <= r1`, the median is simply the average of `max(l1, l2)` and `min(r1, r2)`.
*/
