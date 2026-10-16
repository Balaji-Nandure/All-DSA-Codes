// Problem: Three Way Partitioning of an Array Around a Given Range
// Link (Article): https://www.geeksforgeeks.org/dsa/three-way-partitioning-of-an-array-around-a-given-range/
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/three-way-partitioning/1
// Difficulty: Easy / Medium
// Topic: Array, Two Pointers, Dutch National Flag Algorithm

/*
Problem Statement:
Given an array `arr[]` and a range `[a, b]`. Partition the array such that:
1. All elements strictly smaller than `a` come first.
2. All elements in range `[a, b]` (inclusive) come next.
3. All elements strictly greater than `b` appear at the end.
The individual elements in each of the three partitions can appear in any order.
Must be done in a single pass with O(1) extra space.

Example 1:
Input: arr = [1, 14, 5, 20, 4, 2, 54, 20, 87, 98, 3, 1, 32], a = 14, b = 20
Output: [1, 5, 4, 2, 1, 3, 14, 20, 20, 98, 87, 32, 54]
Explanation: 
- Elements < 14: [1, 5, 4, 2, 1, 3]
- Elements in [14, 20]: [14, 20, 20]
- Elements > 20: [98, 87, 32, 54]

Example 2:
Input: arr = [1, 2, 3, 3, 4], a = 1, b = 2
Output: [1, 2, 3, 3, 4]

Constraints:
- 1 <= arr.size() <= 10^5
- 1 <= arr[i] <= 10^6
- 1 <= a <= b <= 10^6
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 4 (Sort 0s, 1s, 2s): Partitioned into 3 fixed scalar values {0, 1, 2}.
// - In Problem 32 (Three Way Partitioning):
//   * This is the GENERALIZED FORM OF THE DUTCH NATIONAL FLAG ALGORITHM.
//   * The 3 buckets are now arbitrary RANGES: `< a`, `[a ... b]`, and `> b`.
//   * The structural invariant and pointer mechanics remain identical!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Dutch National Flag (DNF) Algorithm with Dynamic Range Check (OPTIMAL & CHOSEN)
//   - Three pointers: `low = 0`, `mid = 0`, `high = n - 1`.
//   - Array is partitioned into 4 zones:
//     1. [0 ... low - 1]     : Elements < a
//     2. [low ... mid - 1]   : Elements in [a, b]
//     3. [mid ... high]      : Unexplored elements
//     4. [high + 1 ... n - 1]: Elements > b
//   - While `mid <= high`:
//     * If `arr[mid] < a`: swap(arr[low], arr[mid]), low++, mid++
//     * If `arr[mid] >= a && arr[mid] <= b`: mid++
//     * If `arr[mid] > b`: swap(arr[mid], arr[high]), high-- (do NOT increment mid!)
//   - Complexity: Exactly O(N) time in a single pass, O(1) space!

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void threeWayPartition(vector<int>& arr, int a, int b) {
        int low = 0;
        int mid = 0;
        int high = arr.size() - 1;

        while (mid <= high) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Category 1: Element is strictly smaller than 'a'
            if (arr[mid] < a) {
                // Swapped element from arr[low] is guaranteed to be in range [a, b],
                // so it is safe to increment both low and mid!
                swap(arr[low], arr[mid]);
                low++;
                mid++;
            }
            // Category 2: Element is within the range [a, b]
            else if (arr[mid] >= a && arr[mid] <= b) {
                mid++;
            }
            // Category 3: Element is strictly greater than 'b'
            else { // arr[mid] > b
                // Swapped element from arr[high] is UNEXPLORED.
                // We MUST re-examine arr[mid] in the next iteration, so do NOT increment mid!
                swap(arr[mid], arr[high]);
                high--;
            }
        }
    }
};

/*
Time Complexity: O(N)
- In each step of the loop, either `mid` increases by 1 or `high` decreases by 1.
- Loop runs at most N times: strictly 1 pass O(N).

Space Complexity: O(1) Auxiliary Space
- Pure in-place swaps with 3 index pointers.

Key Insights:
1. Universal 3-Way Partitioning Template:
   - Comparing with Problem 4:
     `0` mapped to `< a`
     `1` mapped to `[a, b]`
     `2` mapped to `> b`
   - Understanding this abstraction allows you to apply DNF to any 3-way predicate problem effortlessly!
*/
