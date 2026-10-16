// Problem: Move All Negative Elements to One Side of the Array
// Link (Article): https://www.geeksforgeeks.org/dsa/move-negative-numbers-beginning-positive-end-constant-extra-space/
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/move-all-negative-elements-to-end1813/1
// Difficulty: Easy
// Topic: Array, Two Pointers, Partitioning

/*
Problem Statement:
Given an unsorted array of integers containing both positive and negative numbers. 
Rearrange the array elements such that all negative numbers appear on one side (either at the beginning 
or at the end) and all positive numbers appear on the other side.

Note:
There are two common variations in interview settings:
1. In-place with O(1) space where relative order of elements does NOT matter (Partitioning).
2. Stable rearrangement where the relative order of positive and negative numbers MUST be preserved.

Example 1 (Unordered in-place):
Input: arr = [-12, 11, -13, -5, 6, -7, 5, -3, -6]
Output: [-12, -13, -5, -7, -3, -6, 11, 6, 5] (all negatives grouped before positives)

Example 2 (Stable move negatives to end):
Input: arr = [1, -1, 3, 2, -7, -5, 11, 6]
Output: [1, 3, 2, 11, 6, -1, -7, -5] (order of positives 1, 3, 2, 11, 6 preserved)

Constraints:
- 1 <= arr.size() <= 10^5
- -10^5 <= arr[i] <= 10^5
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 1 (Reverse Array): Two pointers swapped symmetrically from both boundaries.
// - In Problem 4 (Sort 0s, 1s, 2s): 3-way partition using DNF for 3 distinct values (0, 1, 2).
// - In Problem 5 (Segregate Negatives & Positives):
//   * This is a 2-WAY PARTITION (binary predicate: < 0 vs >= 0).
//   * The key decision is whether STABILITY (order preservation) is required.
//   * If order doesn't matter: 2-pointer Lomuto/Hoare partition achieves O(1) space.
//   * If order matters: O(N) auxiliary buffer is required to preserve linear order.

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Sorting
//   - Complexity: O(N log N) time, O(1) space.
//   - Why NOT: Changes numerical order of elements and takes O(N log N) when O(N) is possible.
//
// Approach 2: Two-Pointer Partition (In-Place O(1) Space, Order Not Preserved)
//   - Initialize `left = 0`, `right = n - 1`.
//   - If arr[left] < 0 and arr[right] < 0: left++ (left is already in correct place).
//   - If arr[left] >= 0 and arr[right] < 0: swap(arr[left], arr[right]), left++, right--.
//   - If arr[left] >= 0 and arr[right] >= 0: right-- (right is already in correct place).
//   - If arr[left] < 0 and arr[right] >= 0: left++, right--.
//   - Complexity: O(N) time, O(1) space.
//
// Approach 3: Auxiliary Buffer (Stable O(N) Space, Preserves Order - GFG Practice)
//   - Create temporary vector: first copy all positives in order, then all negatives in order.
//   - Copy back to original array.
//   - Complexity: O(N) time, O(N) space.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // -------------------------------------------------------------------------
    // Method 1: Two Pointers In-Place (O(N) Time, O(1) Space - Order Not Preserved)
    // Moves all negative numbers to the BEGINNING
    // -------------------------------------------------------------------------
    void segregateNegativesInPlace(vector<int>& arr) {
        int left = 0;
        int right = arr.size() - 1;

        while (left <= right) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Both conditions checked simultaneously:
            // When left is positive and right is negative, they are BOTH in the wrong zone!
            // Swapping them fixes both in a single operation.
            if (arr[left] < 0 && arr[right] < 0) {
                left++; // Left element is already negative, advance left
            }
            else if (arr[left] >= 0 && arr[right] < 0) {
                swap(arr[left], arr[right]); // Swap positive to right and negative to left
                left++;
                right--;
            }
            else if (arr[left] >= 0 && arr[right] >= 0) {
                right--; // Right element is already positive, decrement right
            }
            else {
                left++;
                right--;
            }
        }
    }

    // -------------------------------------------------------------------------
    // Method 2: Stable Rearrangement (O(N) Time, O(N) Space - Preserves Order)
    // Moves all negative numbers to the END (GFG Practice format)
    // -------------------------------------------------------------------------
    void segregateElementsStable(vector<int>& arr) {
        int n = arr.size();
        vector<int> temp;
        temp.reserve(n);

        // Pass 1: Collect all non-negative numbers in their original order
        for (int i = 0; i < n; i++) {
            if (arr[i] >= 0) {
                temp.push_back(arr[i]);
            }
        }

        // Pass 2: Collect all negative numbers in their original order
        for (int i = 0; i < n; i++) {
            if (arr[i] < 0) {
                temp.push_back(arr[i]);
            }
        }

        // Copy back to original array
        arr = move(temp);
    }
};

/*
Time Complexity:
- Method 1 (Two Pointers): O(N) — single pass where left and right pointers converge.
- Method 2 (Stable Extra Space): O(N) — two linear scans through array of size N.

Space Complexity:
- Method 1: O(1) Auxiliary Space (pure in-place).
- Method 2: O(N) Auxiliary Space (buffer array to maintain relative ordering).

Key Insights:
1. Stability Trade-off:
   - In-place partitioning (Hoare's/Lomuto's style) inherently disrupts original relative ordering.
   - If relative order must be preserved with O(1) space, the best known time complexity is O(N log N)
     using a modified merge sort (in-place block swap), which is rarely practical compared to O(N) extra space.
*/
