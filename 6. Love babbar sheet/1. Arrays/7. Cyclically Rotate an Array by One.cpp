// Problem: Cyclically Rotate an Array by One (and by K positions)
// Link (Article): https://www.geeksforgeeks.org/dsa/c-program-cyclically-rotate-array-one/
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/cyclically-rotate-an-array-by-one2614/1
// Link (LeetCode 189 Rotate Array by K): https://leetcode.com/problems/rotate-array/
// Difficulty: Basic / Easy
// Topic: Array, Two Pointers, Reversal Algorithm

/*
Problem Statement:
Given an array `arr`, rotate the array cyclically in clockwise direction by one:
The last element moves to the 0th index, and all other elements shift right by one index.

Also generalize for rotation by `k` positions clockwise (LeetCode 189).

Example 1:
Input: arr = [1, 2, 3, 4, 5]
Output: [5, 1, 2, 3, 4]

Example 2:
Input: arr = [9, 8, 7, 6, 4, 2, 1, 3]
Output: [3, 9, 8, 7, 6, 4, 2, 1]

Constraints:
- 1 <= arr.size() <= 10^5
- 0 <= arr[i] <= 10^9
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 1 (Reverse Array): Mirror reflection of the entire array.
// - In Problem 7 (Cyclic Rotation):
//   * A circular translation of elements where indices shift by +1 (or +k) modulo N.
//   * If we overwrite elements naively from index 0 forward, we destroy `arr[1]` before moving it!
//   * Hence, traversal direction (right-to-left) or block reversal is required to prevent data loss.

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Rotation by 1:
//   - Save the last element `last = arr[n - 1]`.
//   - Shift elements rightwards starting from the back: `for (int i = n - 1; i > 0; i--) arr[i] = arr[i - 1];`
//   - Place `arr[0] = last;`
//   - Complexity: O(N) time, O(1) space.
//
// Generalization: Rotation by K positions (Reversal Algorithm - OPTIMAL)
//   - Rotate by k is equivalent to:
//     1. Reverse entire array: `reverse(0, n - 1)`.
//     2. Reverse first k elements: `reverse(0, k - 1)`.
//     3. Reverse remaining n - k elements: `reverse(k, n - 1)`.
//   - Complexity: Exactly O(N) time and O(1) extra space!
//   - Why this over extra buffer: Zero heap allocation, pure in-place cache-friendly swaps.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // -------------------------------------------------------------------------
    // Method 1: Rotate by One (GFG Standard - O(N) Time, O(1) Space)
    // -------------------------------------------------------------------------
    void rotate(vector<int>& arr) {
        int n = arr.size();
        if (n <= 1) return;

        // Store the last element which will wrap around to index 0
        int last = arr[n - 1];

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Must iterate BACKWARDS from (n - 1) down to 1.
        // If we iterate forward (0 to n - 2), arr[1] is overwritten by arr[0],
        // then arr[2] is overwritten by the new arr[1], cascading arr[0] across the entire array!
        for (int i = n - 1; i > 0; i--) {
            arr[i] = arr[i - 1];
        }

        arr[0] = last;
    }

    // -------------------------------------------------------------------------
    // Method 2: Generalized Rotate by K (LeetCode 189 - 3-Step Reversal Algorithm)
    // -------------------------------------------------------------------------
    void rotateByK(vector<int>& arr, int k) {
        int n = arr.size();
        if (n <= 1) return;

        // Effective rotations needed
        k = k % n;
        if (k == 0) return;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // 3-step reversal rotates any array in-place without auxiliary memory:
        // Step 1: Reverse the whole array
        reverse(arr.begin(), arr.end());
        // Step 2: Reverse first k elements to restore their original relative order
        reverse(arr.begin(), arr.begin() + k);
        // Step 3: Reverse the remaining n - k elements to restore their order
        reverse(arr.begin() + k, arr.end());
    }
};

/*
Time Complexity:
- Rotate by 1: O(N) — shifts N - 1 elements.
- Rotate by K (Reversal Algorithm): O(N) — N swaps + k swaps + (N - k) swaps = 2N operations = O(N).

Space Complexity: O(1) Auxiliary Space
- Pure in-place manipulation.

Key Insights:
1. Backwards vs. Forwards Traversal:
   - When shifting values rightwards in an array, shifting from RIGHT to LEFT is mandatory 
     to prevent overwriting pending values.
2. The Reversal Algorithm Elegance:
   - The 3-reversal trick is one of the most famous array interview patterns because it achieves
     O(1) auxiliary space where cyclic group / juggling algorithms are tricky to code.
*/
